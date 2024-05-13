#pragma once

#include <QAbstractListModel>
#include "DataModel/Resource.h"

class ResourceVM : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ResourceVMRoles
    {
        ResourceIdRole = Qt::UserRole + 1,
        ResourceNameRole,
    };

    ResourceVM(ResourceRepository& resourceRepository);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE int getIdByIndex(int index) const;
    Q_INVOKABLE int getIndexById(int id) const;
    Q_INVOKABLE QString getNameById(int id) const;
    Q_INVOKABLE int addResource(const QString& resourceName);

signals:
    void updated();

private:
    ResourceRepository& resourceRepository;
};
