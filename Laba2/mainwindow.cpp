#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    parser = Ptr<FileParser>(new FileParser());

    logic = Ptr<Logic>(new Logic(0.05));
    configurePlotWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configurePlotWidget()
{
    plotWidget = new PlotWidget(this);
    this->setCentralWidget(plotWidget);
}

void MainWindow::exec()
{
    try{
        setInputTable();
        logic->exec();
        setPlotData();
    }
    catch(std::exception const& e)
    {
        // Todo inform;
        return;
    }
}

void MainWindow::setPlotData()
{
    plotWidget->clear();
    plotWidget->setXMin(logic->getLeft());
    plotWidget->setXMax(logic->getRight());

    plotWidget->addPlot(logic->getInterpolatedData(), QPen(QBrush(Qt::magenta), 3));
}

void MainWindow::setInputTable()
{
//    logic->setInput(
//                {
//                    {0.0, 1.000},
//                    {0.5, 0.938},
//                    {1.0, 0.765},
//                    {1.5, 0.512},
//                    {2.0, 0.224},
//                    {2.5,-0.048},
//                    {3.0,-0.260},
//                    {3.5,-0.380},
//                    {4.0,-0.402}
//                });
    execOpenFileDialog();
    parser->parse();
    logic->setInput(parser->getParsed());
}

void MainWindow::execOpenFileDialog()
{
    auto fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("Открыть данные");
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter("Text files(*.txt)");
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);

    if(fileDialog->exec()) {
        auto filename = fileDialog->selectedFiles().front();
        parser->setFilename(filename.toStdString());
    }
}

void MainWindow::on_actOpen_triggered()
{
    exec();
}

void MainWindow::on_actExit_triggered()
{
    this->close();
}

