#include "homescreen.hpp"

HomeScreen::HomeScreen ( QWidget *parent ) :
		QWidget ( parent ),
		musPlayer ( 0 )
{

	// Create layout
	vbxHome = new QVBoxLayout ();

	tmrClockUpdate = new QTimer ( this );
	lcdTime = new QLCDNumber ( 8 );
	lcdTime -> setSegmentStyle ( QLCDNumber::Filled );
	//vbxHome -> addWidget ( lcdTime );

	//FIXME
	musPlayer = new MusicPlayer ( this );
	vbxHome -> addWidget ( musPlayer );


	hbxModes = new QHBoxLayout ();
	btnMusic = new QPushButton ( "Music" );
	btnShutdown = new QPushButton ( "Shutdown" );
	hbxModes -> addWidget ( btnMusic );
	hbxModes -> addWidget ( btnShutdown );

	vbxHome -> addLayout ( hbxModes );
	setLayout ( vbxHome );

	connect ( tmrClockUpdate, SIGNAL ( timeout () ), this, SLOT ( update_clock () ) );
	tmrClockUpdate -> start ( 1000 );

	connect ( btnMusic, SIGNAL ( clicked() ), this, SLOT ( mode_music () ) );

}

HomeScreen::~HomeScreen() {
	delete tmrClockUpdate;
	delete btnShutdown;
	delete btnMusic;
	delete lcdTime;
	delete hbxModes;
	delete vbxHome;
}

void HomeScreen::update_clock() {
	QTime displayTime ( QTime::currentTime () );
	lcdTime -> display ( displayTime.toString ( "hh:mm:ss" ) );
}

void HomeScreen::mode_music () {
	tmrClockUpdate->deleteLater();
	lcdTime -> deleteLater();
	vbxHome->deleteLater();


	musPlayer = new MusicPlayer ( this );
	vbxMusic = new QVBoxLayout ();
	vbxMusic ->addWidget(musPlayer);
	vbxMusic->addLayout(hbxModes);

	setLayout ( vbxMusic );
}

void HomeScreen::mode_shutdown () {

}
