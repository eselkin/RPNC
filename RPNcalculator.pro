TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core gui opengl

SOURCES += main.cpp \
    calcui.cpp \
    fraction.cpp \
    mixednum.cpp \
    oppr.cpp

HEADERS += \
    node.h \
    oppr.h \
    fraction.h \
    mixednum.h \
    dataType.h \
    queue.h \
    theStack.h \
    calcui.h \
    infixtopostfix.h

OTHER_FILES += \
    output-sample.txt

