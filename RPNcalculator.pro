TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core gui opengl

SOURCES += calcui.cpp \
    main.cpp \
    fraction.cpp \
    mixednum.cpp \
    oppr.cpp

HEADERS += \
    dataType.h \
    oppr.h \
    queue.h \
    theStack.h \
    fraction.h \
    mixednum.h \
    calcui.h \
    infixtopostfix.h \
    node.h

OTHER_FILES += \
    output-sample.txt

