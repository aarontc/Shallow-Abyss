#ifndef ONSCREENKEYBOARD_HPP
#define ONSCREENKEYBOARD_HPP

#include <QtGui/QWidget>

namespace Ui {
    class OnscreenKeyboard;
}

class OnscreenKeyboard : public QWidget {
    Q_OBJECT
public:
    OnscreenKeyboard(QWidget *parent = 0);
    ~OnscreenKeyboard();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::OnscreenKeyboard *m_ui;
};

#endif // ONSCREENKEYBOARD_HPP
