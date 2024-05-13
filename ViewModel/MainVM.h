#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include "ViewModel/FileVM.h"
#include "ViewModel/OptionsVM.h"
#include "ViewModel/FactoryVM.h"
#include "ViewModel/CalculatorVM.h"

class MainVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(OptionsVM* optionsVM READ getOptionsVM NOTIFY optionsVMChanged)
    Q_PROPERTY(FileVM* fileVM READ getFileVM NOTIFY fileVMChanged)
    Q_PROPERTY(FactoryVM* factoryVM READ getFactoryVM NOTIFY factoryVMChanged)
    Q_PROPERTY(CalculatorVM* calculatorVM READ getCalculatorVM NOTIFY calculatorVMChanged)

public:
    MainVM(QQmlApplicationEngine& engine);
    ~MainVM();

    OptionsVM* getOptionsVM() const;
    FileVM* getFileVM() const;
    FactoryVM* getFactoryVM() const;
    CalculatorVM* getCalculatorVM() const;

signals:
    void optionsVMChanged();
    void fileVMChanged();
    void factoryVMChanged();
    void calculatorVMChanged();

    void loadingFailed();

private:
    Factory factory;

    std::shared_ptr<OptionsVM> optionsVM;
    std::shared_ptr<FileVM> fileVM;
    std::unique_ptr<FactoryVM> factoryVM;
    std::unique_ptr<CalculatorVM> calculatorVM;

};
