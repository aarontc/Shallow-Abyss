#include "libraryscanner.hpp"
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDirIterator>


// FIXME: store this in settings

const QString LibraryPath ( "/opt/music" );

LibraryScanner::LibraryScanner() {
	qDebug() << "Instantiated LibraryScanner";
}

LibraryScanner::~LibraryScanner() {
}

void LibraryScanner::run () {

	qDebug() << "LibraryScanner: running";

}

void LibraryScanner::scan ( QString directory ) {

	 QDirIterator library ( LibraryPath, QDirIterator::Subdirectories );

	 while ( library.hasNext() ) {
		 qDebug() << library.next();
	 }
}

