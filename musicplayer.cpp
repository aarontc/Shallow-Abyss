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
	m_ui->setupUi(this);


	audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	mediaObject = new Phonon::MediaObject(this);

	mediaObject->setTickInterval(1000);

	connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));

	Phonon::createPath(mediaObject, audioOutput);

	dlgAddMusic = new AddMusic ( this );

	connect ( m_ui->btnAddFiles, SIGNAL(clicked()), this, SLOT(addFiles()));

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






