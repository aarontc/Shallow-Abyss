#include <QtGui/QApplication>
#include "homescreen.hpp"
#include "database.hpp"
#include "libraryscanner.hpp"


int main ( int argc, char * argv [] ) {
	QApplication app ( argc, argv );

	if ( ! db_createConnection () )
		return 1;

	HomeScreen h;
	h.show();

	LibraryScanner ls;
	ls.start();

	return app.exec();
}
