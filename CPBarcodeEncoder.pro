QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpbarcode.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cpbarcode.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    CPBarcodeEncoder_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$PWD/ZXing/
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/x64/ -lZXing
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/x64/ -lZXing
else:unix: LIBS += -L$$PWD/libs/x64/ -lZXing
