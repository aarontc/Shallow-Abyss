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
