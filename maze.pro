#-------------------------------------------------
#
# Project created by QtCreator 2011-04-11T07:34:59
#
#-------------------------------------------------
#
# version 0.10: Load/save from/to txt file
# version 0.11: Thread
# version 0.2: OpenGl Widget
# version 0.3: bugs corrected (qt 5.7.1)

QT       += core gui opengl

TARGET = mazegen
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

#DEFINES += QT_NO_DEBUG_OUTPUT QT_NO_INFO_OUTPUT QT_NO_WARNING_OUTPUT

QMAKE_CXXFLAGS += -g

# From modelviewer
HEADERS += modelitem.h model.h \
    GL/glew.h
SOURCES += model.cpp modelitem.cpp

SOURCES += main.cpp\
        mainwindow.cpp \
        mazebacktracking.cpp \
        maze.cpp \
        renderthread.cpp \
        mazewidget.cpp \
        Cell.cpp \
        MatrixCoord.cpp \
        entity.cpp \
        mazescene.cpp \ 
        maze2/maze2.cpp   
	
HEADERS  += mainwindow.h \
    mazebacktracking.h \
    maze.h \
    renderthread.h \
    mazewidget.h \
    Cell.h \
    Matrix.h \
    MatrixCoord.h \
    utils.h \
    Walls.h \
    ClassA.h \
    entity.h \
    mazescene.h \
    maze2/maze2.h

FORMS   += \
    mainwindow.ui

win32 {
LIBS = -lglu32 -lopengl32 -lgdi32
}

