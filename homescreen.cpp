#include "homescreen.hpp"
#include "ui_homescreen.h"
#include <QTimer>
#include <stdio.h>

HomeScreen::HomeScreen(QWidget *parent) :
		QMainWindow(parent),
		m_ui(new Ui::HomeScreen) {

	m_ui->setupUi(this);
	tmrClockUpdate = new QTimer(this);
	connect(tmrClockUpdate, SIGNAL(timeout()), this, SLOT(update_clock()));
	tmrClockUpdate -> start ( 1000 );
}

HomeScreen::~HomeScreen() {
	delete tmrClockUpdate;
	delete m_ui;
}

void HomeScreen::changeEvent(QEvent *e) {
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void HomeScreen::update_clock() {
	static double x = 0;
	++x;
	m_ui->lcdTime->display(x);
}
