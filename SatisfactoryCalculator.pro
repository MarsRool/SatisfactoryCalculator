QT += core gui widgets quick

CONFIG += c++17 lrelease embed_translations

TARGET = SatisfactoryCalculator
TEMPLATE = app

VERSION_MAJOR = 2
VERSION_MINOR = 0
VERSION_BUILD = 0

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}

# OBJECTS_DIR = compile/.obj
# MOC_DIR     = compile/.moc
# UI_DIR      = compile/.ui

LRELEASE_DIR=.
QM_FILES_RESOURCE_PREFIX=/

RC_ICONS = MRS.ico

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    View/Controls/CustomButton.qml \
    View/Controls/CustomComboBox.qml \
    View/Controls/CustomHorizontalHeaderView.qml \
    View/Controls/CustomTabButton.qml \
    View/Main.qml \
    View/MainContent.qml \
    View/MenuView.qml \
    View/OptionsDialog.qml \
    View/PaletteManager.qml \
    View/ProductionListContent.qml \
    View/ProductionRow.qml \
    View/ProductionView.qml \
    View/RecipeView.qml \
    View/ResultTableView.qml \
    View/ResultView.qml

HEADERS += \
    DataModel/Factory.h \
    DataModel/Item.h \
    DataModel/Production.h \
    DataModel/Recipe.h \
    DataModel/Resource.h \
    DataModel/Theme.h \
    Helpers/logger.h \
    Logic/Calculator.h \
    Logic/FactorySerializer.h \
    ViewModel/CalculatorVM.h \
    ViewModel/FactoryVM.h \
    ViewModel/FileVM.h \
    ViewModel/MainVM.h \
    ViewModel/OptionsVM.h \
    ViewModel/RecipeVM.h \
    ViewModel/ResourceVM.h

SOURCES += \
    DataModel/Factory.cpp \
    DataModel/Item.cpp \
    DataModel/Production.cpp \
    DataModel/Recipe.cpp \
    DataModel/Resource.cpp \
    Helpers/logger.cpp \
    Logic/Calculator.cpp \
    Logic/FactorySerializer.cpp \
    ViewModel/CalculatorVM.cpp \
    ViewModel/FactoryVM.cpp \
    ViewModel/FileVM.cpp \
    ViewModel/MainVM.cpp \
    ViewModel/OptionsVM.cpp \
    ViewModel/RecipeVM.cpp \
    ViewModel/ResourceVM.cpp \
    main.cpp

TRANSLATIONS += \
    SatisfactoryCalculator_ru_RU.ts

LCONVERT_LANGS=ru
include(lconvert.pri)

# deploy by
# C:\Qt\6.7.0\mingw_64\bin/windeployqt.exe --dir "G:\Programming\C++ Projects\SatisfactoryCalculator\build\release" "G:\Programming\C++ Projects\SatisfactoryCalculator\build\Desktop_Qt_6_7_0_MinGW_64_bit-Release\release\SatisfactoryCalculator.exe" --qmldir "G:\Programming\C++ Projects\SatisfactoryCalculator\SatisfactoryCalculator\View"
