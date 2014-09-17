TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
            ../Angel/Scripting/Interfaces/AngelLuaWrapping.cpp \

resources.files = Resources/*
resources.path  = $$OUT_PWD/Resources/
unix:resources.extra = mkdir $$OUT_PWD/Resources; echo "HEY";
INSTALLS += resources

INCLUDEPATH += ../Angel/ \
            ../Angel/Libraries/glfw-3.0.3/include \
            ../Angel/Libraries/Box2D-2.2.1 \
            ../Angel/Libraries/FTGL/include \
            ../Angel/Libraries/FMOD/inc \
            ../Angel/Libraries/lua-5.2.1/src

LIBS += -L../Angel/ \
        -L../Angel/Libraries/glfw-3.0.3/src/ \
        -L../Angel/Libraries/Box2D-2.2.1/Build/Box2D/ \
        -L../Angel/Libraries/angel-lua-build/ \
        -L../Angel/Libraries/gwen/lib/linux/gmake/ \
        -L../Angel/Libraries/FTGL/unix/src/.libs/ \
        -langel -lglfw3 -lBox2D -lftgl -lgwen_static -llua \
        -lGL -lGLU -ldl -lfreetype -lXrandr -lX11 -lpthread -lrt -lXxf86vm -lXi \
        -lIL -lILU -lILUT -lpng

QMAKE_CXXFLAGS += -std=gnu++11

win32:CONFIG(release, debug|release): LIBS += -L../Angel/Libraries/FMOD/lib/release/ -lfmodex64
else:win32:CONFIG(debug, debug|release): LIBS += -L../Angel/Libraries/FMOD/lib/debug/ -lfmodex64
else:unix:!macx: LIBS += -L../Angel/Libraries/FMOD/lib/ -lfmodex64

DEPENDPATH += ../Angel/Libraries/FMOD
