TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
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
    infixtopostfix.h

OTHER_FILES += \
    output-sample.txt

