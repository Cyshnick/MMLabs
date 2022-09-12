#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logic.h"
#include "../Laba1/plotwidget.h"
#include "fileparser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actOpen_triggered();

    void on_actExit_triggered();

private:
    void configurePlotWidget();
    void exec();
    void setPlotData();
    void setInputTable();
    void execOpenFileDialog();

    Ptr<Logic> logic;
    Ptr<FileParser> parser;

    PlotWidget* plotWidget;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
