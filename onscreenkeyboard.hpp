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

signals:
	void keypress ( char key );

protected:
	void changeEvent(QEvent *e);

private:
	Ui::OnscreenKeyboard *m_ui;

private slots:
	void on_btnY_clicked();
 void on_btnM_clicked();
 void on_btnN_clicked();
 void on_btnL_clicked();
 void on_btnK_clicked();
 void on_btnJ_clicked();
 void on_btnH_clicked();
 void on_btnP_clicked();
 void on_btnO_clicked();
 void on_btnI_clicked();
 void on_btnU_clicked();
 void on_btn0_clicked();
 void on_btn9_clicked();
 void on_btn8_clicked();
 void on_btn7_clicked();
 void on_btnB_clicked();
 void on_btnV_clicked();
 void on_btnC_clicked();
 void on_btnX_clicked();
 void on_btnZ_clicked();
 void on_btnG_clicked();
 void on_btnF_clicked();
 void on_btnD_clicked();
 void on_btnS_clicked();
 void on_btnA_clicked();
 void on_btnT_clicked();
 void on_btnR_clicked();
 void on_btnE_clicked();
 void on_btnW_clicked();
 void on_btnQ_clicked();
 void on_btn6_clicked();
 void on_btn5_clicked();
 void on_btn4_clicked();
 void on_btn3_clicked();
 void on_btn2_clicked();
 void on_btn1_clicked();
};

#endif // ONSCREENKEYBOARD_HPP
