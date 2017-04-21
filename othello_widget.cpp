#include "othello_widget.h"

bool start = false; // global variables

// static evaluation values

std::vector<std::vector<int>> weights = {
    {100000, -10000, 5000, 2000,  2000, 5000, -10000, 100000},
    {-10000, -30000, -1500, -1500,  -1500, -1500, -30000, -10000},
    {5000,   -1500,  5000,    1000,   1000, 5000,  -1500,  5000},
    {2000,    -1500, 1000,    50,      50,     1000,  -1500,  2000},
    {2000,    -1500, 1000,    50,      50,     1000,  -1500,   2000},
    {5000,   -1500,  5000,    1000,    1000,  5000,  -1500,   5000},
    {-10000, -30000, -1500, -1500,  -1500, -1500, -30000, -10000},
    {100000, -10000, 5000, 2000,  2000, 5000,  -10000, 100000},
};

Othello_Widget::Othello_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Othello_Widget)
{
    ui->setupUi(this);
    // initalization

    //two buttons
    ui->pushButton->setStyleSheet("QPushButton {background-image:url(:/Images/play.png);}");

    ui->about_me->setStyleSheet("QPushButton {background-image:url(:/Images/aboutme.png);}");

    othello::turn = WHITE;

    // radio buttons
    if(othello::mode == ONEPLAYER){
        ui->radioButton_3->setCheckable(true);
        ui->radioButton_4->setCheckable(true);
        ui->radioButton_5->setCheckable(true);
        ui->radioButton->setChecked(true);
        if(othello::difficulty == EASY){
            ui->radioButton_3->setChecked(true);
        }else if(othello::difficulty == HARD){
            ui->radioButton_4->setChecked(true);
        }else if(othello::difficulty == MEDIUM){
            ui->radioButton_5->setChecked(true);
        }
    }
    else if(othello::mode == TWOPLAYER){
        ui->radioButton_2->setChecked(true);
        ui->radioButton_3->setCheckable(false);
        ui->radioButton_4->setCheckable(false);
        ui->radioButton_5->setCheckable(false);
    }
}
void Othello_Widget::free_memory(){
    // free the dynamically allacated memory in the last game
    delete othello::label;
    delete othello::score1;
    delete othello::score2;
    delete othello::name1;
    delete othello::name2;
    delete othello::player1;
    delete othello::player2;
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            delete othello::tile[i][j];
        }
    }
    delete othello::myWidget;
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
        if(ui->radioButton_3->isChecked()){
            othello::difficulty = EASY;
        }
        else if(ui->radioButton_4->isChecked()){
           othello::difficulty = HARD;
        }
        else if(ui->radioButton_5->isChecked()){
           othello::difficulty = MEDIUM;
        }
    }
    else if(ui->radioButton_2->isChecked()){
        othello::mode = TWOPLAYER;
        othello::difficulty = EASY;
    }
    if(othello::running){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Restart", "The game is running, are you sure to restart a new game?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            free_memory();// free the dynamically allacated memory in the last game

            auto myWidget = new Othello_Widget();
            myWidget->setGeometry(0,0,1370,700);
            othello oth(myWidget);
            myWidget->show();
            start = true;
            QMessageBox::information(othello::myWidget,"Started!", "Good Luck, Enjoy!");
        }
    }
    else{

        free_memory();// free the dynamically allacated memory in the last game

        auto myWidget = new Othello_Widget();
        myWidget->setGeometry(0,0,1370,700);
        othello oth(myWidget);
        myWidget->show();
        start = true;
        QMessageBox::information(othello::myWidget,"Started!", "Good Luck, Enjoy!");

    }
}

void Othello_Widget::on_radioButton_clicked()
{
    othello::mode = ONEPLAYER;
    othello::difficulty = EASY;
    ui->radioButton_3->setCheckable(true);
    ui->radioButton_4->setCheckable(true);
    ui->radioButton_5->setCheckable(true);
    ui->radioButton_3->setChecked(true);
}

void Othello_Widget::on_radioButton_2_clicked()
{
    othello::mode = TWOPLAYER;

    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(false);
    ui->radioButton_5->setChecked(false);

    ui->radioButton_3->setCheckable(false);
    ui->radioButton_4->setCheckable(false);
    ui->radioButton_5->setCheckable(false);
}
