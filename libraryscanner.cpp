#include "libraryscanner.hpp"
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>


#include <iostream>
#include <stdio.h>
#include <tag.h>
#include <fileref.h>

// FIXME: store this in settings

const QString LibraryPath ( "/opt/music" );

	using namespace std;

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

	// FIXME: Handle symlinks recursively
	while ( library.hasNext() ) {
		QString file(library.next());
		qDebug() << file;

		QFileInfo info(file);
		if ( info.isSymLink() ) {
			file = info.symLinkTarget();
			qDebug() << "symlink";
		}
		QFileInfo realinfo(file);
		if ( realinfo.isDir() ) {
			qDebug() << "Directory, ignoring";
		} else {
			qDebug() << "Attempting to process";
			readtags ( file );
		}

	}
}

void LibraryScanner::readtags ( const QString & file ) {


	cout << "******************** \"" << file.toLatin1().data() << "\" ********************" << endl;

	TagLib::FileRef f(file.toLatin1().data());

	if(!f.isNull() && f.tag()) {

		TagLib::Tag *tag = f.tag();

		cout << "-- TAG --" << endl;
		cout << "title   - \"" << tag->title()   << "\"" << endl;
		cout << "artist  - \"" << tag->artist()  << "\"" << endl;
		cout << "album   - \"" << tag->album()   << "\"" << endl;
		cout << "year    - \"" << tag->year()    << "\"" << endl;
		cout << "comment - \"" << tag->comment() << "\"" << endl;
		cout << "track   - \"" << tag->track()   << "\"" << endl;
		cout << "genre   - \"" << tag->genre()   << "\"" << endl;
	}

	if(!f.isNull() && f.audioProperties()) {

		TagLib::AudioProperties *properties = f.audioProperties();

		int seconds = properties->length() % 60;
		int minutes = (properties->length() - seconds) / 60;

		cout << "-- AUDIO --" << endl;
		cout << "bitrate     - " << properties->bitrate() << endl;
		cout << "sample rate - " << properties->sampleRate() << endl;
		cout << "channels    - " << properties->channels() << endl;
		cout << "length      - " << minutes << ":" << seconds << endl;
	}
}


