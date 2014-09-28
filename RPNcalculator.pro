TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += gui opengl core

SOURCES += main.cpp \
    calcui.cpp \
    fraction.cpp \
    infixtopostfix.cpp \
    mixednum.cpp \
    node.cpp \
    oppr.cpp \
    queue.cpp \
    theStack.cpp

HEADERS += \
    oppr.h \
    fraction.h \
    mixednum.h \
    dataType.h \
    calcui.h \
    infixtopostfix.h \
    node.h \
    theStack.h \
    queue.h

OTHER_FILES += \
    output-sample.txt

