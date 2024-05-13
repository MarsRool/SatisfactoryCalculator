#include "FactoryVM.h"

FactoryVM::FactoryVM(Factory& factory)
    : factory(factory),
    resourceVM(factory.resourceRepository)
{
    createRecipeVMs();

    qDebug() << __FUNCTION__;
}

int FactoryVM::rowCount(const QModelIndex &) const
{
    return factory.productions.size();
}

QVariant FactoryVM::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        qWarning() << __FUNCTION__ << "incorrect index=" << index.row();
        return {};
    }

    const int rowIndex(index.row());

    if (!(rowIndex < factory.productions.size()))
    {
        qWarning() << __FUNCTION__ << "out of bounds index=" << rowIndex << "productions count=" << factory.productions.size();
        return {};
    }

    const auto& production = factory.productions.at(rowIndex);

    switch (role)
    {
    case FactoryVMRoles::CountRole:
        return QVariant::fromValue(production.count);
    case FactoryVMRoles::OverclockingRole:
        return QVariant::fromValue(QString::number(production.overclocking, 'f', 2));
    case FactoryVMRoles::InputsRole:
    {
        return QVariant::fromValue(inputs[rowIndex].get());
    }
    case FactoryVMRoles::OutputsRole:
    {
        return QVariant::fromValue(outputs[rowIndex].get());
    }
    }

    qWarning() << __FUNCTION__ << "undefined role=" << role;
    return {};
}

bool FactoryVM::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        qWarning() << __FUNCTION__ << "incorrect index=" << index.row();
        return false;
    }

    const int rowIndex(index.row());

    if (!(rowIndex < factory.productions.size()))
    {
        qWarning() << __FUNCTION__ << "out of bounds index=" << rowIndex << "productions count=" << factory.productions.size();
        return false;
    }

    auto& production = factory.productions.at(rowIndex);

    bool success = false;
    bool edited = false;

    switch (role)
    {
    case FactoryVMRoles::CountRole:
        if (auto typedValue = value.toInt(&success); success)
        {
            if (typedValue != production.count)
            {
                production.count = typedValue;
                edited = true;
            }
        }
        break;
    case FactoryVMRoles::OverclockingRole:
        if (auto typedValue = value.toDouble(&success); success)
        {
            typedValue = std::round(typedValue * 100.0) / 100.0;
            if (!qFuzzyCompare(typedValue, production.overclocking))
            {
                production.overclocking = typedValue;
                edited = true;
            }
        }
        break;
    }

    if (edited)
    {
        emit dataChanged(index, index);
        emit changed();
    }

    if (!success)
    {
        qWarning() << __FUNCTION__ << "failed to set data by role=" << role << "value=" << value;
    }

    return success;
}

QHash<int, QByteArray> FactoryVM::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CountRole] = "r_count";
    roles[OverclockingRole] = "r_overclocking";
    roles[InputsRole] = "r_inputs";
    roles[OutputsRole] = "r_outputs";
    return roles;
}

ResourceVM *FactoryVM::getResourceModel()
{
    return &resourceVM;
}

void FactoryVM::resetRecipeVMs()
{
    beginResetModel();

    inputs.clear();
    outputs.clear();
    createRecipeVMs();

    emit changed();
    endResetModel();

    qDebug() << __FUNCTION__;
}

void FactoryVM::addProduction()
{
    beginResetModel();

    inputs.clear();
    outputs.clear();

    factory.productions.push_back({});

    createRecipeVMs();

    emit changed();
    endResetModel();

    qDebug() << __FUNCTION__;
}

void FactoryVM::removeProduction(int index)
{
    if (!(0 <= index && index < factory.productions.size()))
    {
        qCritical() << __FUNCTION__ << "trying to remove non-existent production by index=" << index
                   << "productions count=" << factory.productions.size();
        return;
    }

    beginResetModel();

    inputs.clear();
    outputs.clear();

    auto productionsIterator = factory.productions.begin();
    std::advance(productionsIterator, index);
    factory.productions.erase(productionsIterator);

    createRecipeVMs();

    emit changed();
    endResetModel();

    qDebug() << __FUNCTION__;
}

void FactoryVM::removeResource(int resourceId)
{
    if (std::find_if(factory.resourceRepository.resources.begin(),
                     factory.resourceRepository.resources.end(),
                     [&resourceId](const Resource& resource)
                     {
                         return resource.id == resourceId;
                     }) == factory.resourceRepository.resources.end())
    {
        qCritical() << __FUNCTION__ << "trying to remove non-existent resource by id=" << resourceId;
        return;
    }

    beginResetModel();

    inputs.clear();
    outputs.clear();

    for (auto& production : factory.productions)
    {
        auto removeByResourceFunc = [&resourceId](const Item& item)
        {
            return item.resourceId == resourceId;
        };

        auto newInputsEndIterator = std::remove_if(
            production.recipe.inputs.begin(), production.recipe.inputs.end(),
            removeByResourceFunc);
        production.recipe.inputs.erase(newInputsEndIterator, production.recipe.inputs.end());

        auto newOutputsEndIterator = std::remove_if(
            production.recipe.outputs.begin(), production.recipe.outputs.end(),
            removeByResourceFunc);
        production.recipe.outputs.erase(newOutputsEndIterator, production.recipe.outputs.end());
    }

    auto newResourceEndIterator = std::remove_if(
        factory.resourceRepository.resources.begin(), factory.resourceRepository.resources.end(),
        [&resourceId](const Resource& resource)
        {
            return resource.id == resourceId;
        });
    factory.resourceRepository.resources.erase(newResourceEndIterator, factory.resourceRepository.resources.end());

    createRecipeVMs();

    emit changed();
    endResetModel();

    qDebug() << __FUNCTION__;
}

void FactoryVM::createRecipeVMs()
{
    for (auto& production : factory.productions)
    {
        inputs.push_back(std::make_unique<RecipeVM>(production.recipe.inputs));
        outputs.push_back(std::make_unique<RecipeVM>(production.recipe.outputs));

        connect(inputs.back().get(),
                &RecipeVM::changed,
                this,
                &FactoryVM::changed);
        connect(outputs.back().get(),
                &RecipeVM::changed,
                this,
                &FactoryVM::changed);
    }

    qDebug() << __FUNCTION__;
}
