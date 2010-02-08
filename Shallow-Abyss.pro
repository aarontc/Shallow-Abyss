# -------------------------------------------------
# Project created by QtCreator 2010-01-25T09:43:37
# -------------------------------------------------
QT += network \
    opengl \
    sql \
    script \
    svg \
    webkit \
    xml \
    xmlpatterns \
    phonon \
    testlib \
    dbus
TARGET = Shallow-Abyss
TEMPLATE = app
SOURCES += main.cpp \
    homescreen.cpp \
    libraryscanner.cpp \
    musicplayer.cpp
HEADERS += homescreen.hpp \
    database.hpp \
    libraryscanner.hpp \
    musicplayer.hpp
FORMS += homescreen.ui \
    musicplayer.ui
INCLUDEPATH += "/usr/include" \
    /usr/include/taglib
LIBS += -L/usr/lib \
    -lpq \
    -ltag
