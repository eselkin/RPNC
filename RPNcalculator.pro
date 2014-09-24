TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fraction.cpp \
    mixednum.cpp \
    infixtopostfix.cpp \
    oppr.cpp

HEADERS += \
    fraction.h \
    mixednum.h \
    infixtopostfix.h \
    queue.h \
    theStack.h \
    node.h \
    dataType.h \
    oppr.h

OTHER_FILES += \
    output-sample.txt

