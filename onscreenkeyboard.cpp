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

void OnscreenKeyboard::on_btnA_clicked(){
	emit keypress('A');
}
void OnscreenKeyboard::on_btnB_clicked(){
	emit keypress('B');
}
void OnscreenKeyboard::on_btnC_clicked(){
	emit keypress('C');
}
void OnscreenKeyboard::on_btnD_clicked(){
	emit keypress('D');
}
void OnscreenKeyboard::on_btnE_clicked(){
	emit keypress('E');
}
void OnscreenKeyboard::on_btnF_clicked(){
	emit keypress('F');
}
void OnscreenKeyboard::on_btnG_clicked(){
	emit keypress('G');
}
void OnscreenKeyboard::on_btnH_clicked(){
	emit keypress('H');
}
void OnscreenKeyboard::on_btnI_clicked(){
	emit keypress('I');
}
void OnscreenKeyboard::on_btnJ_clicked(){
	emit keypress('J');
}
void OnscreenKeyboard::on_btnK_clicked(){
	emit keypress('K');
}
void OnscreenKeyboard::on_btnL_clicked(){
	emit keypress('L');
}
void OnscreenKeyboard::on_btnM_clicked(){
	emit keypress('M');
}
void OnscreenKeyboard::on_btnN_clicked(){
	emit keypress('N');
}
void OnscreenKeyboard::on_btnO_clicked(){
	emit keypress('O');
}
void OnscreenKeyboard::on_btnP_clicked(){
	emit keypress('P');
}
void OnscreenKeyboard::on_btnQ_clicked(){
	emit keypress('Q');
}
void OnscreenKeyboard::on_btnR_clicked(){
	emit keypress('R');
}
void OnscreenKeyboard::on_btnS_clicked(){
	emit keypress('S');
}
void OnscreenKeyboard::on_btnT_clicked(){
	emit keypress('T');
}
void OnscreenKeyboard::on_btnU_clicked(){
	emit keypress('U');
}
void OnscreenKeyboard::on_btnV_clicked(){
	emit keypress('V');
}
void OnscreenKeyboard::on_btnW_clicked(){
	emit keypress('W');
}
void OnscreenKeyboard::on_btnX_clicked(){
	emit keypress('X');
}
void OnscreenKeyboard::on_btnY_clicked(){
	emit keypress('Y');
}
void OnscreenKeyboard::on_btnZ_clicked(){
	emit keypress('Z');
}
void OnscreenKeyboard::on_btn0_clicked(){
	emit keypress('0');
}
void OnscreenKeyboard::on_btn1_clicked () {
	emit keypress('1');
}
void OnscreenKeyboard::on_btn2_clicked () {
	emit keypress('2');
}
void OnscreenKeyboard::on_btn3_clicked(){
	emit keypress('3');
}
void OnscreenKeyboard::on_btn4_clicked(){
	emit keypress('4');
}
void OnscreenKeyboard::on_btn5_clicked(){
	emit keypress('5');
}
void OnscreenKeyboard::on_btn6_clicked(){
	emit keypress('6');
}
void OnscreenKeyboard::on_btn7_clicked(){
	emit keypress('7');
}
void OnscreenKeyboard::on_btn8_clicked(){
	emit keypress('8');
}
void OnscreenKeyboard::on_btn9_clicked(){
	emit keypress('9');
}
