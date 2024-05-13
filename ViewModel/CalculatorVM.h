#pragma once

#include <QAbstractTableModel>
#include <QColor>
#include <QEvent>
#include <QQmlApplicationEngine>

#include "Logic/Calculator.h"

class CalculatorVM : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum CalculatorVMRoles
    {
        DataRole = Qt::UserRole + 1,
        BackgroundColorRole
    };

    CalculatorVM(Factory& factory);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

signals:
    void updated();
    void removeResourceRequested(int resourceId);

public slots:
    void calculate();
    void removeResource(int row);
    void onLanguageChanged();

private:
    QString ResourceNameById(int resourceId) const;

    Calculator calculator;

    const static QColor efficientColor;
    const static QColor nonEfficientColor;
    static const std::vector<QString> headerCaptions;
};
