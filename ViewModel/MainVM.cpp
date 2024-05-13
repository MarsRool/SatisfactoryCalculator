#include "MainVM.h"

MainVM::MainVM(QQmlApplicationEngine& engine)
{
    optionsVM = std::make_shared<OptionsVM>(engine);
    fileVM = std::make_shared<FileVM>(factory, optionsVM);

    fileVM->performLoad();

    factoryVM = std::make_unique<FactoryVM>(factory);
    calculatorVM = std::make_unique<CalculatorVM>(factory);

    connect(factoryVM.get(),
            &FactoryVM::changed,
            calculatorVM.get(),
            &CalculatorVM::calculate);

    connect(calculatorVM.get(),
            &CalculatorVM::removeResourceRequested,
            factoryVM.get(),
            &FactoryVM::removeResource);

    connect(fileVM.get(),
            &FileVM::loaded,
            factoryVM.get(),
            &FactoryVM::resetRecipeVMs);
    connect(calculatorVM.get(),
            &CalculatorVM::updated,
            fileVM.get(),
            &FileVM::performSave);

    connect(optionsVM.get(),
            &OptionsVM::languageChanged,
            calculatorVM.get(),
            &CalculatorVM::onLanguageChanged);

    qDebug() << __FUNCTION__;
}

MainVM::~MainVM()
{
    fileVM->performSave();
}

OptionsVM *MainVM::getOptionsVM() const
{
    return optionsVM.get();
}

FileVM *MainVM::getFileVM() const
{
    return fileVM.get();
}

FactoryVM *MainVM::getFactoryVM() const
{
    return factoryVM.get();
}

CalculatorVM *MainVM::getCalculatorVM() const
{
    return calculatorVM.get();
}
