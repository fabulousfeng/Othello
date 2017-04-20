#ifndef OTHELLO_WIDGET_H
#define OTHELLO_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

#include "ui_othello_widget.h"
#include "othello.h"
#include "tile.h"

namespace Ui {
class Othello_Widget;
}

class Othello_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Othello_Widget(QWidget *parent = 0);
    void free_memory();
    ~Othello_Widget();

private slots:
    void on_about_me_clicked();

    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::Othello_Widget *ui;
};

#endif // OTHELLO_WIDGET_H
