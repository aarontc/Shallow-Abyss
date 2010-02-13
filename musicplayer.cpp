#include "musicplayer.hpp"
#include "ui_musicplayer.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QTime>



MusicPlayer::MusicPlayer(QWidget *parent) :
		QWidget(parent),
		m_ui(new Ui::MusicPlayer),
		m_query(new QSqlQuery)
{
	m_ui->setupUi(this);


	mediaObject = new Phonon::MediaObject(this);
	audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	Phonon::createPath(mediaObject, audioOutput);

	mediaObject->setTickInterval(1000);

	connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
	connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(enqueueNextSource()));


	dlgAddMusic = new AddMusic ( this );
	connect ( dlgAddMusic, SIGNAL(selected_artistid(quint64)), this, SLOT(playlist_add_artistid(quint64)));
	connect ( dlgAddMusic, SIGNAL(selected_albumid(quint64)), this, SLOT(playlist_add_albumid(quint64)));
	connect ( dlgAddMusic, SIGNAL(selected_songid(quint64)), this, SLOT(playlist_add_songid(quint64)));
	connect ( dlgAddMusic, SIGNAL(selected_file(QString)), this, SLOT(playlist_add_file(QString)));


}

void MusicPlayer::playPause()
{
	// are we paused?
	Phonon::State s = mediaObject->state();
	switch(s) {
		case Phonon::PausedState:
		// resume playing
		mediaObject->play();
		m_ui->btnPause->setText("Pause");
		break;
		case Phonon::PlayingState:
		// pause playback
		mediaObject->pause();
		m_ui->btnPause->setText("Play");
		break;
		case Phonon::StoppedState:
		case Phonon::LoadingState:
		// load song and play
		if ( m_playlist.size() > 0 ) {
			m_ui->btnPause->setText("Pause");
			mediaObject->enqueue(Phonon::MediaSource(m_playlist.first()->filePath()));
			m_nowplaying = 0;
			mediaObject->play();
		}
		break;
	}
}

void MusicPlayer::playPrevious() {
	qDebug()<<"playPrevious: m_nowPlaying was:"<<m_nowplaying;
	if (mediaObject->state() == Phonon::PlayingState) {
		if ( m_nowplaying > 0 ) {
			--m_nowplaying;
			qDebug()<<"playPrevious: m_nowPlaying now:"<<m_nowplaying;
			mediaObject->setCurrentSource(Phonon::MediaSource(m_playlist.at(m_nowplaying)->filePath()));
			mediaObject->play();
		}
	}
}

void MusicPlayer::playNext() {
	if (mediaObject->state() == Phonon::PlayingState) {
		if ( m_playlist.size() > m_nowplaying ) {
			++m_nowplaying;
			mediaObject->setCurrentSource(Phonon::MediaSource(m_playlist.at(m_nowplaying)->filePath()));
			mediaObject->play();
		}
	}
}

void MusicPlayer::enqueueNextSource() {
}


MusicPlayer::~MusicPlayer () {
	delete m_ui;
}

void MusicPlayer::clearPlaylist()
{
	m_playlist.clear();
	m_ui->tblMusic->clearContents();
	m_ui->tblMusic->setRowCount(0);
}

void MusicPlayer::shufflePlaylist() {
	QVector<Song *> newlist;
	int x = m_playlist.size();

	while ( x > 0 ) {
		int y = rand() % x;

		newlist.append(m_playlist.at(y));
		m_playlist.remove(y);

		x = m_playlist.size();
	}

	clearPlaylist();
	int row = m_ui->tblMusic->rowCount();
	m_playlist = newlist;
	foreach(Song * song, m_playlist) {
		m_ui->tblMusic->setRowCount(row+1);
		QTableWidgetItem * newitem = new QTableWidgetItem(song->artist());
		m_ui->tblMusic->setItem(row, 0, newitem);
		newitem = new QTableWidgetItem(song->title());
		m_ui->tblMusic->setItem(row++, 1, newitem);
	}
	m_ui->tblMusic->setRowCount(row);


}

void MusicPlayer::addFiles()
{

	dlgAddMusic->exec();

}

void MusicPlayer::tick ( qint64 time ) {
	QTime displayTime ( 0, ( time / 60000 ) % 60, ( time / 1000 ) % 60 );
	m_ui->lcdTime -> display ( displayTime.toString ( "mm:ss" ) );
}

void MusicPlayer::playlist_add_artistid ( quint64 artistid ) {
	m_query->prepare ( "SELECT songs.songid FROM songs WHERE songs.artistid=? " );
	m_query->addBindValue( artistid );
	m_query->exec();


	int row = m_ui->tblMusic->rowCount();
	while ( m_query->next() ) {
		m_playlist += new Song(m_query->value(0).toULongLong());
		m_ui->tblMusic->setRowCount(row+1);
		QTableWidgetItem * newitem = new QTableWidgetItem(m_playlist.last()->artist());
		m_ui->tblMusic->setItem(row, 0, newitem);
		newitem = new QTableWidgetItem(m_playlist.last()->title());
		m_ui->tblMusic->setItem(row++, 1, newitem);
	}
	m_ui->tblMusic->setRowCount(row);

}

void MusicPlayer::playlist_add_albumid ( quint64 albumid ) {
	m_query->prepare ( "SELECT songs.songid FROM songs WHERE songs.albumid=?" );
	m_query->addBindValue( albumid );
	m_query->exec();

	int row = m_ui->tblMusic->rowCount();
	while ( m_query->next() ) {
		m_playlist += new Song(m_query->value(0).toULongLong());
		m_ui->tblMusic->setRowCount(row+1);
		QTableWidgetItem * newitem = new QTableWidgetItem(m_playlist.last()->artist());
		m_ui->tblMusic->setItem(row, 0, newitem);
		newitem = new QTableWidgetItem(m_playlist.last()->title());
		m_ui->tblMusic->setItem(row++, 1, newitem);
	}
	m_ui->tblMusic->setRowCount(row);

}

void MusicPlayer::playlist_add_songid ( quint64 songid ) {
	m_playlist += new Song(songid);

	int row = m_ui->tblMusic->rowCount();

	m_ui->tblMusic->setRowCount(row + 1);
	QTableWidgetItem * newitem = new QTableWidgetItem(m_playlist.last()->artist());
	m_ui->tblMusic->setItem(row, 0, newitem);
	newitem = new QTableWidgetItem(m_playlist.last()->title());
	m_ui->tblMusic->setItem(row, 1, newitem);
}

void MusicPlayer::playlist_add_file ( QString file ) {
	int row = m_ui->tblMusic->rowCount();
	m_ui->tblMusic->setRowCount(row+1);
	QTableWidgetItem * newitem = new QTableWidgetItem(file);
	m_ui->tblMusic->setItem(row++, 0, newitem);
	m_ui->tblMusic->setRowCount(row);

}

