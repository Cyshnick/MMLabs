#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "plotwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    configureHighLogic();
    configurePlotWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureHighLogic()
{
    Real A = 0;
    Real B = PI;
    auto func = [A, B](Real x) {
        if(x < A)
            return 0.;
        if(x < B)
            return exp(x);
        return 0.;
    };

    size_t numOfIntegralSteps = 1000;
    size_t numOfHarmonics = 5;
    Real dataStep = 0.05;

    HighLogic::Input input {A, B, func};
    HighLogic::Parameters params {numOfIntegralSteps, numOfHarmonics, dataStep};

    logic = Ptr<HighLogic>(new HighLogic(input, params));
}

void MainWindow::configurePlotWidget()
{
    auto plotWidget = new PlotWidget(this);
    this->setCentralWidget(plotWidget);

    plotWidget->setXMin(logic->getBegin());
    plotWidget->setXMax(logic->getEnd());

    plotWidget->setNumOfXGridLines(15);
    plotWidget->setNumOfYGridLines(10);

    plotWidget->addPlot(logic->getBaseFunc(), QPen(QBrush(Qt::black), 3));
    plotWidget->addPlot(logic->getHarmonics()[0], QPen(QBrush(Qt::green), 2));
    plotWidget->addPlot(logic->getHarmonics()[1], QPen(QBrush(Qt::red), 2));
    plotWidget->addPlot(logic->getHarmonics()[2], QPen(QBrush(Qt::blue), 2));
    plotWidget->addPlot(logic->getHarmonics()[3], QPen(QBrush(Qt::cyan), 2));
    plotWidget->addPlot(logic->getHarmonics()[4], QPen(QBrush(Qt::yellow), 2));
    plotWidget->addPlot(logic->getHarmonicsSum(), QPen(QBrush(Qt::magenta), 3));

    plotWidget->addPlot(logic->getEffectiveValue(), QPen(QBrush(Qt::black), 2));
    plotWidget->addPlot(logic->getMeanValue(), QPen(QBrush(Qt::darkGray), 2));
}
