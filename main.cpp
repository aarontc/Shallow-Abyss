#include <QtGui/QApplication>
#include <QtSql>
#include "mainwindow.hpp"
#include "homescreen.hpp"
#include "database.hpp"


int main ( int argc, char * argv [] ) {
	QApplication app ( argc, argv );

	// Setup database connection
	QSqlDatabase db = QSqlDatabase::addDatabase ( "QPSQL" );
	db.setHostName ( "localhost" );
	db.setDatabaseName ( "shallow" );
	db.setUserName ( "shallow" );
	db.setPassword ( "test" );
	bool ok = db.open();

	if ( ! ok )
		return 1;

	HomeScreen h;
	h.show();

	QFile *albumDetails = new QFile("albumdetails.xml");
	MainWindow window ( db );
	window.show();

	return app.exec();
}
