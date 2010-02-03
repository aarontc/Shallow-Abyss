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
	mainwindow.cpp \
	homescreen.cpp \
	libraryscanner.cpp
HEADERS += mainwindow.hpp \
	homescreen.hpp \
	database.hpp \
	libraryscanner.hpp
FORMS += mainwindow.ui \
	homescreen.ui
INCLUDEPATH += "/usr/include" \
/usr/include/taglib
LIBS += -L/usr/lib \
	-lpq \
-ltag

