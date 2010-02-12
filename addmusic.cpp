#include "addmusic.hpp"
#include "ui_addmusic.h"

#include <QDebug>

AddMusic::AddMusic(QWidget *parent) :
		QDialog(parent),
		m_ui(new Ui::AddMusic)
{
	m_query = new QSqlQuery;
	m_ui->setupUi(this);
	m_ui->txtSearch->setText("");
}

AddMusic::~AddMusic() {
	delete m_ui;
	delete m_query;
}

void AddMusic::changeEvent(QEvent *e) {
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
	m_ui->txtSearch->setText(m_ui->txtSearch->text().append(letter));
}

//void AddMusic::browse() {
//		QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"),
//		QDesktopServices::storageLocation(QDesktopServices::MusicLocation));
//
//	if (files.isEmpty())
//		return;
//}

void AddMusic::on_txtSearch_textChanged(QString text)
{
	QString search = "%" + text + "%";

	qDebug() << "Search string:" << search;

	m_query->clear();
	m_query->prepare("SELECT artists.artistid, artists.name AS artist_name, albums.albumid, albums.name AS album_name, songs.songid, songs.title AS song_title FROM songs JOIN artists ON artists.artistid=songs.artistid JOIN albums ON albums.albumid=songs.albumid WHERE LOWER(artists.name) LIKE LOWER(?) OR LOWER(songs.title) LIKE LOWER(?) OR LOWER(albums.name) LIKE LOWER(?) ORDER BY artists.name ASC, albums.name ASC, songs.title ASC LIMIT ?");
	m_query->addBindValue(search);
	m_query->addBindValue(search);
	m_query->addBindValue(search);
	m_query->addBindValue(MaxResults);
	m_query->exec();

	m_ui->tblSongs->clearContents();
	m_query->first();
	int row = 0;
	while ( m_query->next() ) {
		m_artistIDs[row] = m_query->value(0).toULongLong();
		m_albumIDs[row] = m_query->value(2).toULongLong();
		m_songIDs[row] = m_query->value(4).toULongLong();

		m_ui->tblSongs->setRowCount(row+1);
		QTableWidgetItem * newitem = new QTableWidgetItem(m_query->value(1).toString());
		m_ui->tblSongs->setItem(row, 0, newitem);
		newitem = new QTableWidgetItem(m_query->value(3).toString());
		m_ui->tblSongs->setItem(row, 1, newitem);
		newitem = new QTableWidgetItem(m_query->value(5).toString());
		m_ui->tblSongs->setItem(row++, 2, newitem);

	}
	m_ui->tblSongs->setRowCount(row);
}

void AddMusic::on_buttonBox_accepted()
{
	qDebug() << "accept happened";
	switch (m_curCol) {
		case 0: // artist
			qDebug() << "Selected artist ID" << m_artistIDs[m_curRow];
			emit selected_artistid(m_artistIDs[m_curRow]);
			break;
		case 1: // album
			qDebug() << "Selected album ID" << m_albumIDs[m_curRow];
			emit selected_albumid(m_albumIDs[m_curRow]);
			break;
		case 2: // song
			qDebug() << "Selected song ID" << m_songIDs[m_curRow];
			emit selected_songid(m_songIDs[m_curRow]);
			break;
		}
}

void AddMusic::cell_activated(int row, int col) {
	m_curRow = row;
	m_curCol = col;
}
