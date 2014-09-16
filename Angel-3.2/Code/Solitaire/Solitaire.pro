TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
            $$PWD/../Angel/Scripting/Interfaces/AngelLuaWrapping.cpp \

INCLUDEPATH += $$PWD/../Angel/ \
            $$PWD/../Angel/Libraries/glfw-3.0.3/include \
            $$PWD/../Angel/Libraries/Box2D-2.2.1 \
            $$PWD/../Angel/Libraries/FTGL/include \
            $$PWD/../Angel/Libraries/FMOD/inc \
            $$PWD/../Angel/Libraries/lua-5.2.1/src

LIBS += -L$$PWD/../Angel/ \
        -L$$PWD/../Angel/Libraries/glfw-3.0.3/src/ \
        -L$$PWD/../Angel/Libraries/Box2D-2.2.1/Build/Box2D/ \
        -L$$PWD/../Angel/Libraries/angel-lua-build/ \
        -L$$PWD/../Angel/Libraries/gwen/lib/linux/gmake/ \
        -L$$PWD/../Angel/Libraries/FTGL/unix/src/.libs/ \
        -langel -lglfw3 -lBox2D -lftgl -lgwen_static -llua \
        -lGL -lGLU -ldl -lfreetype -lXrandr -lX11 -lpthread -lrt -lXxf86vm -lXi \
        -lIL -lILU -lILUT -lpng

QMAKE_CXXFLAGS += -std=gnu++11

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Angel/Libraries/FMOD/lib/release/ -lfmodex64
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Angel/Libraries/FMOD/lib/debug/ -lfmodex64
else:unix:!macx: LIBS += -L$$PWD/../Angel/Libraries/FMOD/lib/ -lfmodex64

DEPENDPATH += $$PWD/../Angel/Libraries/FMOD
