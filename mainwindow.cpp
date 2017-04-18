#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_Help_triggered()
{
    QMessageBox::information(this,"About", "Copyright © April 2017 by Feng. \nAll rights reserved.\nContact: zhoufeng@umich.edu ");
}
