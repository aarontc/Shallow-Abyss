#ifndef ADDMUSIC_HPP
#define ADDMUSIC_HPP

#include <QtGui/QDialog>
#include <QSqlQuery>

#include "onscreenkeyboard.hpp"

namespace Ui {
	class AddMusic;
}

class AddMusic : public QDialog {
	Q_OBJECT
public:
	AddMusic(QWidget *parent = 0);
	~AddMusic();

	static const int MaxResults = 100;

signals:
	void selected_artistid(quint64);
	void selected_albumid(quint64);
	void selected_songid(quint64);
	void selected_file(QString);

private slots:
	void on_buttonBox_accepted();
	void on_txtSearch_textChanged(QString );
	void vk_pressed ( char letter );

	void cell_activated (int row, int col);


protected:
	void changeEvent(QEvent *e);



private:
	Ui::AddMusic *m_ui;
	QSqlQuery * m_query;

	int m_curRow, m_curCol;
	quint64 m_artistIDs[MaxResults], m_albumIDs[MaxResults], m_songIDs[MaxResults];

};

#endif // ADDMUSIC_HPP
