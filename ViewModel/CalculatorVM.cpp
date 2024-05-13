#include "CalculatorVM.h"

#include <QGuiApplication>

const std::vector<QString> CalculatorVM::headerCaptions
{
    tr("Name"),
    tr("Consumption"),
    tr("Production"),
    tr("Result"),
    tr("Efficiency")
};

const QColor CalculatorVM::efficientColor{ 160, 255, 190, 40 };
const QColor CalculatorVM::nonEfficientColor{ 255, 160, 190, 40 };

CalculatorVM::CalculatorVM(Factory &factory)
    : calculator(factory)
{
    qDebug() << __FUNCTION__;
}

int CalculatorVM::rowCount(const QModelIndex &) const
{
    return calculator.factory.productionResults.size();
}

int CalculatorVM::columnCount(const QModelIndex &) const
{
    return headerCaptions.size() + 1;
}

QVariant CalculatorVM::data(const QModelIndex &index, int role) const
{
    if (!(index.isValid() && 0 <= index.row() && index.row() < calculator.factory.productionResults.size()))
    {
        qWarning() << __FUNCTION__ << "incorrect row=" << index.row();
        return {};
    }

    auto itemIterator = calculator.factory.productionResults.cbegin();
    std::advance(itemIterator, index.row());
    const auto& item = itemIterator->second;

    switch (role)
    {
    case CalculatorVMRoles::DataRole:
    {
        switch (index.column())
        {
        case 0:
            return ResourceNameById(item.resourceId);
        case 1:
            return QString::number(item.consumption);
        case 2:
            return QString::number(item.production);
        case 3:
            return QString::number(item.result);
        case 4:
            return QString("%1%").arg(QString::number(item.efficiency * 100));
        }
        break;
    }
    case CalculatorVMRoles::BackgroundColorRole:
    {
        if (qFuzzyCompare(item.efficiency, 1.0))
        {
            return efficientColor;
        }
        return nonEfficientColor;
    }
    }

    qWarning() << __FUNCTION__ << "undefined role" << role;
    return {};
}

QVariant CalculatorVM::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (0 <= section && section < headerCaptions.size())
        {
            return QGuiApplication::translate("CalculatorVM", headerCaptions[section].toStdString().c_str());
        }
        return QString();
    }

    qWarning() << __FUNCTION__ << "incorrect parameters: role=" << role << "orientation=" << orientation;
    return {};
}

QHash<int, QByteArray> CalculatorVM::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[DataRole] = "r_data";
    roles[BackgroundColorRole] = "r_background_color";
    return roles;
}

void CalculatorVM::calculate()
{
    qDebug() << __FUNCTION__;

    beginResetModel();
    calculator.calculate();
    emit updated();
    endResetModel();
}

void CalculatorVM::removeResource(int row)
{
    if (!(0 <= row && row < calculator.factory.productionResults.size()))
    {
        qCritical() << __FUNCTION__ << "trying to remove non-existent resource by row=" << row
                   << "productionResults count=" << calculator.factory.productionResults.size();
        return;
    }

    auto itemIterator = calculator.factory.productionResults.cbegin();
    std::advance(itemIterator, row);
    const auto& item = itemIterator->second;

    emit removeResourceRequested(item.resourceId);

    qDebug() << __FUNCTION__ << "successfully removed resource by id=" << item.resourceId;
}

void CalculatorVM::onLanguageChanged()
{
    emit headerDataChanged(Qt::Horizontal, 0, 5);
}

QString CalculatorVM::ResourceNameById(int resourceId) const
{
    const auto iterator = std::find_if(
        calculator.factory.resourceRepository.resources.begin(),
        calculator.factory.resourceRepository.resources.end(),
        [&resourceId](const Resource& resource)
        {
            return resource.id == resourceId;
        });

    if (iterator != calculator.factory.resourceRepository.resources.end())
    {
        return QString::fromStdString(iterator->name);
    }

    return QString();
}
