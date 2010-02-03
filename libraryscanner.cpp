#include "libraryscanner.hpp"
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDirIterator>
#include <taglib/tag.h>


// FIXME: store this in settings

const QString LibraryPath ( "/opt/music" );

LibraryScanner::LibraryScanner() {
	qDebug() << "Instantiated LibraryScanner";
}

LibraryScanner::~LibraryScanner() {
}

void LibraryScanner::run () {

	qDebug() << "LibraryScanner: running";
	scan ();

}

void LibraryScanner::scan ( const QString & directory ) {
	QString path = directory;
	if ( path == NULL )
		path = LibraryPath;

	qDebug() << "LibraryScanner::scan(path=\"" + path + "\")";

	 QDirIterator library ( path, QDirIterator::Subdirectories );

	 while ( library.hasNext() ) {
		 qDebug() << library.next();
	 }
}

