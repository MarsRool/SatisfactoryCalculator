#include "ResourceVM.h"

ResourceVM::ResourceVM(ResourceRepository& resourceRepository)
    : resourceRepository(resourceRepository)
{
    qDebug() << __FUNCTION__;
}

int ResourceVM::rowCount(const QModelIndex&) const
{
    return resourceRepository.resources.size();
}

QVariant ResourceVM::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        qWarning() << __FUNCTION__ << "incorrect index=" << index.row();
        return {};
    }

    const int rowIndex(index.row());

    if (!(rowIndex < resourceRepository.resources.size()))
    {
        qWarning() << __FUNCTION__ << "out of bounds index=" << rowIndex << "resources count=" << resourceRepository.resources.size();
        return {};
    }

    const auto& resource = resourceRepository.resources[rowIndex];

    switch (role)
    {
    case ResourceVMRoles::ResourceIdRole:
        return QVariant::fromValue(resource.id);
    case ResourceVMRoles::ResourceNameRole:
        return QString::fromStdString(resource.name);
    }

    qWarning() << __FUNCTION__ << "undefined role=" << role;
    return {};
}

QHash<int, QByteArray> ResourceVM::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ResourceIdRole] = "r_resource_id";
    roles[ResourceNameRole] = "r_resource_name";
    return roles;
}

int ResourceVM::getIdByIndex(int index) const
{
    if (0 <= index && index < resourceRepository.resources.size())
    {
        return resourceRepository.resources[index].id;
    }

    qWarning() << __FUNCTION__ << "incorrect index=" << index;
    return -1;
}

int ResourceVM::getIndexById(int id) const
{
    auto iterator = std::find_if(resourceRepository.resources.begin(), resourceRepository.resources.end(), [id](const Resource& resource)
    {
        return resource.id == id;
    });

    if (iterator != resourceRepository.resources.end())
    {
        return std::distance(resourceRepository.resources.begin(), iterator);
    }

    qWarning() << __FUNCTION__ << "incorrect id=" << id;
    return -1;
}

QString ResourceVM::getNameById(int id) const
{
    auto iterator = std::find_if(resourceRepository.resources.begin(), resourceRepository.resources.end(), [id](const Resource& resource)
    {
        return resource.id == id;
    });

    if (iterator != resourceRepository.resources.end())
    {
        return QString::fromStdString(iterator->name);
    }

    qWarning() << __FUNCTION__ << "incorrect id=" << id;
    return QString();
}

int ResourceVM::addResource(const QString& resourceName)
{
    if (resourceName.isEmpty())
    {
        qWarning() << __FUNCTION__ << "failed to add resource by empty name";
        return -1;
    }

    auto resourceNameStd = resourceName.toStdString();

    auto iterator = std::find_if(resourceRepository.resources.begin(), resourceRepository.resources.end(), [&resourceNameStd](const Resource& resource)
    {
        return resource.name == resourceNameStd;
    });

    if (iterator == resourceRepository.resources.end())
    {
        int insertIndex = -1;

        for (int index = 0; index < resourceRepository.resources.size(); ++index)
        {
            if (resourceNameStd < resourceRepository.resources[index].name)
            {
                insertIndex = index;
                break;
            }
        }

        insertIndex = insertIndex == -1 ? resourceRepository.resources.size() : insertIndex;
        auto insertIterator = resourceRepository.resources.begin();
        std::advance(insertIterator, insertIndex);

        beginInsertRows(QModelIndex(), insertIndex, insertIndex);

        ++resourceRepository.lastId;
        resourceRepository.resources.insert(insertIterator, Resource{ resourceRepository.lastId, resourceNameStd });
        emit updated();

        endInsertRows();

        return resourceRepository.lastId;
    }
    else
    {
        qDebug() << __FUNCTION__ << "resource already exists by name=" << resourceName;
        return iterator->id;
    }

    qDebug() << __FUNCTION__;
}
