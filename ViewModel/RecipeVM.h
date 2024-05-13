#pragma once

#include <QAbstractListModel>
#include "DataModel/Item.h"

class RecipeVM : public QAbstractListModel
{
    Q_OBJECT

public:
    enum RecipeVMRoles
    {
        RecipeResourceIdRole = Qt::UserRole + 1,
        RecipeCountRole
    };

    RecipeVM(std::vector<Item>& items);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void changed();

private:
    void updateEmptyRecipes();
private slots:
    // void onChanged();

private:
    std::vector<Item>& items;
};
