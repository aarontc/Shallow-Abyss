#include <QtGui/QApplication>
#include <QtSql>
#include "mainwindow.hpp"
#include "homescreen.hpp"
#include "database.hpp"


int main ( int argc, char * argv [] ) {
	QApplication app ( argc, argv );

	if ( ! db_createConnection () )
		return 1;

	HomeScreen h;
	h.show();

	MainWindow window;
	window.show();

	return app.exec();
}
