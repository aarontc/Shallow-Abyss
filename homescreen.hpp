#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include <QTimer>
#include <QLCDNumber>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include <QWidget>

#include "musicplayer.hpp"

class HomeScreen : public QWidget {
	Q_OBJECT

public:
	HomeScreen ( QWidget * parent = 0 );
	~HomeScreen ();

public slots:
	void update_clock ();
	void mode_music ();
	void mode_shutdown ();

protected:

private:
	QTimer * tmrClockUpdate;
	QLCDNumber * lcdTime;
	QPushButton * btnMusic;
	QPushButton * btnShutdown;
	QVBoxLayout * vbxHome;
	QHBoxLayout * hbxModes;
	QVBoxLayout * vbxMusic;
	MusicPlayer * musPlayer;

};

#endif // HOMESCREEN_HPP
