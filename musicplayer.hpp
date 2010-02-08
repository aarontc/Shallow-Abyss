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
#include <QSqlDatabase>


namespace Ui {
	class MusicPlayer;
}

class MusicPlayer : public QWidget {
	Q_OBJECT
public:
	MusicPlayer(QWidget *parent = 0);
	~MusicPlayer();

protected:


private:


	Ui::MusicPlayer * m_ui;


	Phonon::MediaObject * mediaObject;
	Phonon::AudioOutput * audioOutput;
	QList<Phonon::MediaSource> sources;


private slots:
	void addFiles();
	void tick(qint64 time);

};

#endif // MUSICPLAYER_HPP
