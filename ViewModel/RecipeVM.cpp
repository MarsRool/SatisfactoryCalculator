#include "RecipeVM.h"

RecipeVM::RecipeVM(std::vector<Item> &items)
    : items(items)
{
    updateEmptyRecipes();
}

int RecipeVM::rowCount(const QModelIndex&) const
{
    return items.size();
}

QVariant RecipeVM::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        qWarning() << __FUNCTION__ << "incorrect index=" << index.row();
        return {};
    }

    const int rowIndex(index.row());

    if (!(rowIndex < items.size()))
    {
        qWarning() << __FUNCTION__ << "out of bounds index=" << rowIndex << "items count=" << items.size();
        return {};
    }

    const auto& item = items[rowIndex];

    switch (role)
    {
    case RecipeVMRoles::RecipeResourceIdRole:
        return QVariant::fromValue(item.resourceId);
    case RecipeVMRoles::RecipeCountRole:
        return QVariant::fromValue(item.count);
    }

    qWarning() << __FUNCTION__ << "undefined role=" << role;
    return {};
}

bool RecipeVM::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        qWarning() << __FUNCTION__ << "incorrect index=" << index.row();
        return false;
    }

    const int rowIndex(index.row());

    if (!(rowIndex < items.size()))
    {
        qWarning() << __FUNCTION__ << "out of bounds index=" << rowIndex << "items count=" << items.size();
        return false;
    }

    auto& item = items.at(rowIndex);

    bool success = false;
    bool edited = false;

    switch (role)
    {
    case RecipeVMRoles::RecipeResourceIdRole:
        if (auto typedValue = value.toInt(&success); success)
        {
            if (typedValue != item.resourceId)
            {
                item.resourceId = typedValue;
                edited = true;
            }
        }
        break;
    case RecipeVMRoles::RecipeCountRole:
        if (auto typedValue = value.toDouble(&success); success)
        {
            if (typedValue != item.count)
            {
                item.count = typedValue;
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

    updateEmptyRecipes();

    if (!success)
    {
        qWarning() << __FUNCTION__ << "failed to set data by role=" << role << "value=" << value;
    }

    return success;
}

QHash<int, QByteArray> RecipeVM::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RecipeResourceIdRole] = "r_recipe_resource_id";
    roles[RecipeCountRole] = "r_recipe_count";
    return roles;
}

void RecipeVM::updateEmptyRecipes()
{
    std::vector<int> emptyIndices;
    for (int index = 0; index < items.size(); ++index)
    {
        if (!items[index].isValid())
        {
            emptyIndices.push_back(index);
        }
    }

    if (emptyIndices.size() > 1)
    {
        for (auto emptyIndexiterator = emptyIndices.rbegin(); emptyIndexiterator != emptyIndices.rend(); ++emptyIndexiterator)
        {
            int index = *emptyIndexiterator;
            beginRemoveRows(QModelIndex(), index, index);

            auto iterator = items.begin();
            std::advance(iterator, index);
            items.erase(iterator);

            endRemoveRows();
        }
        emptyIndices.clear();
    }

    if (emptyIndices.empty())
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        items.push_back({-1, 0});
        endInsertRows();
    }

    qDebug() << __FUNCTION__;
}
