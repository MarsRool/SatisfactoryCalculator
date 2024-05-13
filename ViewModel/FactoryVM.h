#pragma once

#include <QAbstractListModel>
#include "DataModel/Factory.h"
#include "RecipeVM.h"
#include "ResourceVM.h"

class FactoryVM : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ResourceVM* resources READ getResourceModel NOTIFY resourcesChanged)

public:
    enum FactoryVMRoles
    {
        CountRole = Qt::UserRole + 1,
        OverclockingRole,
        InputsRole,
        OutputsRole
    };

    FactoryVM(Factory& factory);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    ResourceVM* getResourceModel();

signals:
    void changed();
    void resourcesChanged();

public slots:
    void resetRecipeVMs();
    void addProduction();
    void removeProduction(int index);
    void removeResource(int resourceId);

private:
    void createRecipeVMs();

    Factory& factory;

    ResourceVM resourceVM;
    std::vector<std::unique_ptr<RecipeVM>> inputs;
    std::vector<std::unique_ptr<RecipeVM>> outputs;
};
