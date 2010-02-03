#include <QtGui/QApplication>
#include <QtSql>
#include "mainwindow.hpp"
#include "homescreen.hpp"
#include "database.hpp"
#include "libraryscanner.hpp"


int main ( int argc, char * argv [] ) {
	QApplication app ( argc, argv );

	if ( ! db_createConnection () )
		return 1;

	HomeScreen h;
	h.show();

//	MainWindow window;
//	window.show();

	LibraryScanner ls;
	ls.start();

	return app.exec();
}
