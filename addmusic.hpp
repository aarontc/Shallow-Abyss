#ifndef ADDMUSIC_HPP
#define ADDMUSIC_HPP

#include <QtGui/QDialog>

namespace Ui {
    class AddMusic;
}

class AddMusic : public QDialog {
    Q_OBJECT
public:
    AddMusic(QWidget *parent = 0);
    ~AddMusic();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AddMusic *m_ui;
};

#endif // ADDMUSIC_HPP
