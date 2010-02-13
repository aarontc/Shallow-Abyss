#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <QtGui/QWidget>


#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QList>
#include <QFile>
#include <QSqlQuery>
#include <QVector>

#include "addmusic.hpp"
#include "song.hpp"

namespace Ui {
	class MusicPlayer;
}

class MusicPlayer : public QWidget {
	Q_OBJECT
public:
	MusicPlayer(QWidget *parent = 0);
	~MusicPlayer();

public slots:
	void playlist_add_artistid ( quint64 artistid );
	void playlist_add_albumid ( quint64 albumid );
	void playlist_add_songid ( quint64 songid );
	void playlist_add_file ( QString path );


protected:


private:


	Ui::MusicPlayer * m_ui;


	Phonon::MediaObject * mediaObject;
	Phonon::AudioOutput * audioOutput;

	AddMusic * dlgAddMusic;

	QSqlQuery * m_query;

	QVector<Song *> m_playlist;
	int m_nowplaying; // item in the playlist we are currently playing

private slots:
	void addFiles();
	void tick(qint64 time);
	void clearPlaylist();
	void shufflePlaylist();

	void playPause();
	void playPrevious();
	void playNext();
	void enqueueNextSource();

};

#endif // MUSICPLAYER_HPP
