#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui/QMainWindow>

#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QList>
#include <QFile>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
class QAction;
class QTableWidget;
class QLCDNumber;
QT_END_NAMESPACE

//![0]

class MainWindow : public QMainWindow
{
//![0]
	Q_OBJECT

public:
	MainWindow ( QWidget *parent = 0 );

	QSize sizeHint() const {
		return QSize(500, 300);
	}

private slots:
	void addFiles();
	void about();
//![1]
	void stateChanged(Phonon::State newState, Phonon::State oldState);
	void tick(qint64 time);
	void sourceChanged(const Phonon::MediaSource &source);
	void metaStateChanged(Phonon::State newState, Phonon::State oldState);
	void aboutToFinish();
	void tableClicked(int row, int column);
//![1]

private:
	void setupActions();
	void setupMenus();
	void setupUi();
	QString m_artistTable;
	QString m_albumTable;
	QFile * m_albumDetails;

//![2]
	Phonon::SeekSlider *seekSlider;
	Phonon::MediaObject *mediaObject;
	Phonon::MediaObject *metaInformationResolver;
	Phonon::AudioOutput *audioOutput;
	Phonon::VolumeSlider *volumeSlider;
	QList<Phonon::MediaSource> sources;
//![2]

	QAction *playAction;
	QAction *pauseAction;
	QAction *stopAction;
	QAction *nextAction;
	QAction *previousAction;
	QAction *addFilesAction;
	QAction *exitAction;
	QAction *aboutAction;
	QAction *aboutQtAction;
	QLCDNumber *timeLcd;
	QTableWidget *musicTable;
};

#endif // MAINWINDOW_HPP
