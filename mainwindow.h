#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include "model.h"
#include "widget.h"

//создание класса MainWindow, наследующего класс QMainWindow
//этот класс выполняет роль контроллера между моделью и графическим интерфейсом
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Model *model;       //динамический объект класса Model
    Widget *widget;     //динамический объект класса Widget
    QProgressBar *prbr; //динамический объект класса QProgressBar
    QProcess *proc;     //динамический объект класса QProcess


public slots:
    void showApex(unsigned long long n, double r, double d);
    void onHelp();
    //слот об отрисовке гистограммы
    void onPlotHistogram();

protected:
    void createMenu();



};

#endif // MAINWINDOW_H
