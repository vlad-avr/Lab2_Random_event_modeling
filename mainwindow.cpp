#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <time.h>

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




void MainWindow::on_action_Dice_like_scenario_triggered()
{
    dm_win = new DicesManual(this);
    dm_win->show();
}

