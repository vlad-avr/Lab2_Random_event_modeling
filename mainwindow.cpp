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



void MainWindow::on_pushButton_Dice_manual_clicked()
{

}

