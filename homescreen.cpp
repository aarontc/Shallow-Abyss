#include "homescreen.h"
#include "ui_homescreen.h"

homescreen::homescreen(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::homescreen)
{
    m_ui->setupUi(this);
}

homescreen::~homescreen()
{
    delete m_ui;
}

void homescreen::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
