#include "addmusic.hpp"
#include "ui_addmusic.h"

AddMusic::AddMusic(QWidget *parent) :
		QDialog(parent),
		m_ui(new Ui::AddMusic)
{
	m_ui->setupUi(this);

}

AddMusic::~AddMusic()
{
	delete m_ui;
}

void AddMusic::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void AddMusic::vk_pressed(char letter) {
	m_ui->txtSearch->setText(QString(letter));
}

//void AddMusic::browse() {
//		QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"),
//		QDesktopServices::storageLocation(QDesktopServices::MusicLocation));
//
//	if (files.isEmpty())
//		return;
//}
