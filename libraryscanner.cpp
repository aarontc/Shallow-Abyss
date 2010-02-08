#include "libraryscanner.hpp"
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QVariant>
#include <QDateTime>


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
	QFileInfo info(file);

//	cout << "******************** \"" << file.toLatin1().data() << "\" ********************" << endl;

	TagLib::FileRef f(file.toLatin1().data());

	if(!f.isNull() && f.tag()) {

		TagLib::Tag *tag = f.tag();

//		cout << "-- TAG --" << endl;
//		cout << "title   - \"" << tag->title()   << "\"" << endl;
//		cout << "artist  - \"" << tag->artist()  << "\"" << endl;
//		cout << "album   - \"" << tag->album()   << "\"" << endl;
//		cout << "year    - \"" << tag->year()    << "\"" << endl;
//		cout << "comment - \"" << tag->comment() << "\"" << endl;
//		cout << "track   - \"" << tag->track()   << "\"" << endl;
//		cout << "genre   - \"" << tag->genre()   << "\"" << endl;

		QSqlQuery query;
		query.setForwardOnly( true );

		// See if the artist exists
		quint64 artistid;
		query.prepare ( "SELECT artistid FROM artists WHERE name=?" );
		query.addBindValue( tag->artist().toCString(true) );
		query.exec();

		if ( query.size() > 0 ) {
			query.first();
			artistid = query.value(0).toULongLong();
		} else {
			query.clear();
			query.prepare( "INSERT INTO artists (name) VALUES (?)" );
			query.addBindValue( tag->artist().toCString(true) );
			query.exec();
			query.clear();
			query.exec( "SELECT currval('artists_artistid_seq')" );
			query.first();
			artistid = query.value(0).toULongLong();
		}

		qDebug() << "artistid for \"" << tag->artist().toCString(true) << "\"=" << artistid;

		// Get song ID if it exists
		quint64 songid;
		query.clear();
		query.prepare( "SELECT songid FROM songs WHERE title=? AND artistid=?" );
		query.addBindValue( tag->title().toCString(true) );
		query.addBindValue( artistid );
		query.exec();

		if ( query.size() > 0 ) {
			query.first();
			songid = query.value(0).toULongLong();
		} else {
			query.clear();
			query.prepare( "INSERT INTO songs (artistid, title) VALUES (?, ?)" );
			query.addBindValue( artistid );
			query.addBindValue( tag->title() .toCString(true) );
			query.exec();
			query.clear();
			query.exec( "SELECT currval('songs_songid_seq')" );
			query.first();
			songid = query.value(0).toULongLong();
		}

		// Get file ID if it exists
		query.clear();
		query.prepare( "SELECT fileid FROM files WHERE songid=? AND path=?" );
		query.addBindValue( songid );
		query.addBindValue( file );
		query.exec();


		if ( query.size() > 0 ) {
			qDebug() << "FILE EXISTS IN DB!";
		} else {
			query.clear();
			query.prepare ( "INSERT INTO files (path, size, ctime, mtime, songid) VALUES (?, ?, ?, ?, ?)" );
			query.addBindValue( file );
			query.addBindValue( info.size() );
			query.addBindValue( info.created() );
			query.addBindValue( info.lastModified() );
			query.addBindValue( songid );
			query.exec ();
		}

	}

//	if(!f.isNull() && f.audioProperties()) {
//
//		TagLib::AudioProperties *properties = f.audioProperties();
//
//		int seconds = properties->length() % 60;
//		int minutes = (properties->length() - seconds) / 60;
//
//		cout << "-- AUDIO --" << endl;
//		cout << "bitrate     - " << properties->bitrate() << endl;
//		cout << "sample rate - " << properties->sampleRate() << endl;
//		cout << "channels    - " << properties->channels() << endl;
//		cout << "length      - " << minutes << ":" << seconds << endl;
//	}
}


