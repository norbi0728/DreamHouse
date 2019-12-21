TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \
        abstractinterface.cpp \
        admininterface.cpp \
        agent.cpp \
        agentinterface.cpp \
        datahandler.cpp \
        logininterface.cpp \
        main.cpp \
        menu.cpp \
        realestate.cpp \
        user.cpp \
        userinterface.cpp

HEADERS += \
    abstractinterface.h \
    admininterface.h \
    agent.h \
    agentinterface.h \
    datahandler.h \
    logininterface.h \
    menu.h \
    realestate.h \
    user.h \
    userinterface.h

DISTFILES += \
    class.qmodel
