#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include <QtGui/QMainWindow>
#include <QTimer>

namespace Ui {
	class HomeScreen;
}

class HomeScreen : public QMainWindow {
	Q_OBJECT
public:
	HomeScreen(QWidget *parent = 0);
	~HomeScreen();

public slots:
	void update_clock ();


protected:
	void changeEvent(QEvent *e);

private:
	Ui::HomeScreen *m_ui;
	QTimer * tmrClockUpdate;


};

#endif // HOMESCREEN_HPP
