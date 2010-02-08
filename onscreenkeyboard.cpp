#include "onscreenkeyboard.hpp"
#include "ui_onscreenkeyboard.h"

OnscreenKeyboard::OnscreenKeyboard(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::OnscreenKeyboard)
{
    m_ui->setupUi(this);
}

OnscreenKeyboard::~OnscreenKeyboard()
{
    delete m_ui;
}

void OnscreenKeyboard::changeEvent(QEvent *e)
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
