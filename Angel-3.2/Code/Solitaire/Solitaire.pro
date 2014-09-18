TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    ../Angel/Scripting/Interfaces/AngelLuaWrapping.cpp \
    board.cpp \
    game.cpp \
    solitairelogic.cpp \
    card.cpp

HEADERS += \
    board.h \
    game.h \
    solitairelogic.h \
    card.h

resources.files = Resources/*
resources.path  = $$OUT_PWD/Resources/
unix:resources.extra = mkdir -p $$OUT_PWD/Resources;
INSTALLS += resources

INCLUDEPATH += ../Angel/ \
            ../Angel/Libraries/glfw-3.0.3/include \
            ../Angel/Libraries/Box2D-2.2.1 \
            ../Angel/Libraries/FTGL/include \
            ../Angel/Libraries/FMOD/inc \
            ../Angel/Libraries/lua-5.2.1/src

LIBS += -L$$PWD/../Angel/ \
        -L$$PWD/../Angel/Libraries/glfw-3.0.3/src/ \
        -L$$PWD/../Angel/Libraries/Box2D-2.2.1/Build/Box2D/ \
        -L$$PWD/../Angel/Libraries/angel-lua-build/ \
        -L$$PWD/../Angel/Libraries/gwen/lib/linux/gmake/ \
        -L$$PWD/../Angel/Libraries/FTGL/unix/src/.libs/ \
        -L$$PWD/../Angel/Libraries/FMOD/lib/    \
        -langel -lglfw3 -lBox2D -lftgl -lgwen_static -llua -lfmodex64 \
        -lGL -lGLU -ldl -lfreetype -lXrandr -lX11 -lpthread -lrt -lXxf86vm -lXi \
        -lIL -lILU -lILUT -lpng

QMAKE_CXXFLAGS += -std=gnu++11

DEPENDPATH += ../Angel/Libraries/FMOD
