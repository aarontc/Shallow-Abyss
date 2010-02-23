#include <QtGui/QApplication>
#include "homescreen.hpp"
#include "database.hpp"
#include "libraryscanner.hpp"


int main ( int argc, char * argv [] ) {
	QApplication app ( argc, argv );

	if ( ! db_createConnection () )
		return 1;

	HomeScreen h;
	//h.setMinimumSize(QSize(800, 480));
	h.showFullScreen();

	LibraryScanner ls;
	ls.start();

	return app.exec();
}
