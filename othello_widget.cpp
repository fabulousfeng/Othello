#include "othello_widget.h"
bool start = false;
Othello_Widget::Othello_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Othello_Widget)
{
    ui->setupUi(this);
    // initalization

    //two buttons
    ui->pushButton->setStyleSheet("QPushButton {background-image:url(:/Images/play.png);}");

    ui->about_me->setStyleSheet("QPushButton {background-image:url(:/Images/aboutme.png);}");

    // radio buttons
    if(othello::mode == ONEPLAYER){
        ui->radioButton->setChecked(true);
    }
    else{
        ui->radioButton_2->setChecked(true);
    }
}

Othello_Widget::~Othello_Widget()
{
    delete ui;
}

void Othello_Widget::on_about_me_clicked()
{
   QMessageBox::about(this, "About me", "Copyright © 2017 by Feng. All rights reserved.\nContact: zhoufeng@umich.edu");
}

void Othello_Widget::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked()){
        othello::mode = ONEPLAYER;
        ui->radioButton->setChecked(true);
    }
    else{
        othello::mode = TWOPLAYER;
        ui->radioButton_2->setChecked(true);
    }
    if(othello::running){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Restart", "The game is running, are you sure to restart a new game?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            auto myWidget = new Othello_Widget();
            myWidget->setGeometry(0,0,1370,700);
            othello oth(myWidget);
            myWidget->show();
            start = true;
            QMessageBox::information(othello::myWidget,"Started!", "Good Luck! Enjoy");
        }
    }
    else{
        auto myWidget = new Othello_Widget();
        myWidget->setGeometry(0,0,1370,700);
        othello oth(myWidget);
        myWidget->show();
        start = true;
        QMessageBox::information(othello::myWidget,"Started!", "Good Luck! Enjoy");
    }


}
