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

void MusicPlayer::clearPlaylist()
{
	playlist.clear();
	m_ui->tblMusic->clearContents();
	m_ui->tblMusic->setRowCount(0);
}

void MusicPlayer::shufflePlaylist() {
	QVector<Song *> newlist;
	int x = playlist.size();

	while ( x > 0 ) {
		int y = rand() % x;

		newlist.append(playlist.at(y));
		playlist.remove(y);

		x = playlist.size();
	}

	clearPlaylist();
	int row = m_ui->tblMusic->rowCount();
	playlist = newlist;
	foreach(Song * song, playlist) {
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
		playlist += new Song(m_query->value(0).toULongLong());
		m_ui->tblMusic->setRowCount(row+1);
		QTableWidgetItem * newitem = new QTableWidgetItem(playlist.last()->artist());
		m_ui->tblMusic->setItem(row, 0, newitem);
		newitem = new QTableWidgetItem(playlist.last()->title());
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
		playlist += new Song(m_query->value(0).toULongLong());
		m_ui->tblMusic->setRowCount(row+1);
		QTableWidgetItem * newitem = new QTableWidgetItem(playlist.last()->artist());
		m_ui->tblMusic->setItem(row, 0, newitem);
		newitem = new QTableWidgetItem(playlist.last()->title());
		m_ui->tblMusic->setItem(row++, 1, newitem);
	}
	m_ui->tblMusic->setRowCount(row);

}

void MusicPlayer::playlist_add_songid ( quint64 songid ) {
	playlist += new Song(songid);

	int row = m_ui->tblMusic->rowCount();

	m_ui->tblMusic->setRowCount(row + 1);
	QTableWidgetItem * newitem = new QTableWidgetItem(playlist.last()->artist());
	m_ui->tblMusic->setItem(row, 0, newitem);
	newitem = new QTableWidgetItem(playlist.last()->title());
	m_ui->tblMusic->setItem(row, 1, newitem);
}

void MusicPlayer::playlist_add_file ( QString file ) {
	int row = m_ui->tblMusic->rowCount();
	m_ui->tblMusic->setRowCount(row+1);
	QTableWidgetItem * newitem = new QTableWidgetItem(file);
	m_ui->tblMusic->setItem(row++, 0, newitem);
	m_ui->tblMusic->setRowCount(row);

}

