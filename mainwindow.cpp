#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "probexp.h"
#include <iostream>
#include <time.h>
#include "RandEvent.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    srand(time(0));
    ProbExp* p_exp = new ProbExp();
    for(int i = 0; i < 10; i++){
        p_exp->set(i, REvent(rand()%10, (rand()%10)/10));
    }
    p_exp->print();
}

