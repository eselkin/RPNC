TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core gui opengl


SOURCES += main.cpp \
    fraction.cpp \
    mixednum.cpp \
    oppr.cpp \
    calcwidget.cpp \
    calcui.cpp

HEADERS += \
    node.h \
    oppr.h \
    fraction.h \
    mixednum.h \
    dataType.h \
    queue.h \
    theStack.h \
    infixtopostfix.h \
    calcwidget.h \
    calcui.h

OTHER_FILES += \
    output-sample.txt

