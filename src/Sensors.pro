QT       += core gui
QT += charts
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/SensorManager.cpp \
    Model/Dust.cpp \
    Model/Humidity.cpp \
    View/MainWindow.cpp \
    Model/Sensor.cpp \
    Model/Temperature.cpp \
    ValueCalculatorVisitor.cpp \
    View/SearchBar.cpp \
    View/SensorCharts.cpp \
    View/SensorCreateDialog.cpp \
    View/SensorInfo.cpp \
    main.cpp

HEADERS += \
    Controller/SensorManager.h \
    Model/Dust.h \
    Model/Humidity.h \
    View/MainWindow.h \
    Model/Sensor.h \
    SensorVisitor.h \
    Model/Temperature.h \
    ValueCalculatorVisitor.h \
    ValueCalculatorVisitor.h \
    View/SearchBar.h \
    View/SensorCharts.h \
    View/SensorCreateDialog.h \
    View/SensorInfo.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
