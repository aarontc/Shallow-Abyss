#include "musicplayer.hpp"
#include "ui_musicplayer.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QTime>



MusicPlayer::MusicPlayer(QWidget *parent) :
		QWidget(parent),
		m_ui(new Ui::MusicPlayer)
{
	m_query = new QSqlQuery;
	m_ui->setupUi(this);


	audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	mediaObject = new Phonon::MediaObject(this);

	mediaObject->setTickInterval(1000);

	connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));

	Phonon::createPath(mediaObject, audioOutput);

	dlgAddMusic = new AddMusic ( this );
	connect ( dlgAddMusic, SIGNAL(selected_artistid(quint64)), this, SLOT(playlist_add_artistid(quint64)));
	connect ( dlgAddMusic, SIGNAL(selected_albumid(quint64)), this, SLOT(playlist_add_albumid(quint64)));
	connect ( dlgAddMusic, SIGNAL(selected_songid(quint64)), this, SLOT(playlist_add_songid(quint64)));
	connect ( dlgAddMusic, SIGNAL(selected_file(QString)), this, SLOT(playlist_add_file(QString)));

	connect ( m_ui->btnAdd, SIGNAL(clicked()), this, SLOT(addFiles()));

}

MusicPlayer::~MusicPlayer () {
	delete m_ui;
}

void MusicPlayer::addFiles()
{

	int result = dlgAddMusic->exec();

	qDebug() << "after dlgaddmusic";

//
//	foreach (QString string, files) {
//			Phonon::MediaSource source(string);
//
//		sources.append(source);
//	}

}

void MusicPlayer::tick ( qint64 time ) {
	QTime displayTime ( 0, ( time / 60000 ) % 60, ( time / 1000 ) % 60 );
	m_ui->lcdTime -> display ( displayTime.toString ( "mm:ss" ) );
}

void MusicPlayer::playlist_add_artistid ( quint64 artistid ) {
	m_query->prepare ( "SELECT files.path FROM files JOIN songs ON songs.songid=files.songid JOIN artists ON songs.artistid=artists.artistid WHERE artists.artistid=? " );
	m_query->addBindValue( artistid );
	m_query->exec();

	while ( m_query->next() ) {
		qDebug() << "adding file" << m_query->value(0).toString();
	}
}

void MusicPlayer::playlist_add_albumid ( quint64 albumid ) {
	m_query->prepare ( "SELECT files.path FROM files JOIN songs ON songs.songid=files.songid JOIN artists ON songs.artistid=artists.artistid" );
	m_query->addBindValue( albumid );
	m_query->exec();

	while ( m_query->next() ) {
		qDebug() << "adding file" << m_query->value(0).toString();
	}
}

void MusicPlayer::playlist_add_songid ( quint64 songid ) {
	m_query->prepare ( "SELECT files.path FROM files JOIN songs ON songs.songid=files.songid WHERE songs.songid=?" );
	m_query->addBindValue( songid );
	m_query->exec();

	while ( m_query->next() ) {
		qDebug() << "adding file" << m_query->value(0).toString();
	}
}

void MusicPlayer::playlist_add_file ( QString file ) {

}

