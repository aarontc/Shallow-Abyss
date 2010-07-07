#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QtGui/QWidget>

namespace Ui {
    class homescreen;
}

class homescreen : public QWidget {
    Q_OBJECT
public:
    homescreen(QWidget *parent = 0);
    ~homescreen();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::homescreen *m_ui;
};

#endif // HOMESCREEN_H
