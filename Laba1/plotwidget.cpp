#include "plotwidget.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>

PlotWidget::PlotWidget(QWidget* parent) :
    QWidget(parent),
    gridPen(QBrush(Qt::black), 1, Qt::DashLine),
    xMaxValue(100),
    xMinValue(0),
    yMaxValue(100),
    yMinValue(0),
    xGridNum(10),
    yGridNum(10),
    labelFont("Times New Roman", 12)
{
    addPlot(0, QPen(QBrush(Qt::black), 2));
}

void PlotWidget::addPlot(const Reals &data, const QPen &pen)
{
    addPlot({data, pen});
}

void PlotWidget::addPlot(Real yValue, const QPen &pen)
{
    addPlot({Reals{yValue}}, pen);
}

void PlotWidget::clear()
{
    plots.clear();
    addPlot(0, QPen(QBrush(Qt::black), 2));
}

void PlotWidget::setYMax(Real val)
{
    yMaxValue = val;
}

void PlotWidget::setYMin(Real val)
{
    yMinValue = val;
}

void PlotWidget::setXMax(Real val)
{
    xMaxValue = val;
}

void PlotWidget::setXMin(Real val)
{
    xMinValue = val;
}

void PlotWidget::setNumOfXGridLines(size_t val)
{
    xGridNum = val;
    update();
}

void PlotWidget::setNumOfYGridLines(size_t val)
{
    yGridNum = val;
    update();
}

void PlotWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    transformPainter(painter);
    drawPlotField(painter);
    drawPlots(painter);
}

void PlotWidget::addPlot(const Plot &plot)
{
    plots.push_back(plot);
    autoFindYBorders();
    update();
}

void PlotWidget::autoFindYBorders()
{
    Real yMin = std::numeric_limits<Real>::max();
    Real yMax = std::numeric_limits<Real>::min();
    foreach(const auto& plot, plots) {
        for(auto const& val : plot.data) {
            if(yMin > val)
                yMin = val;

            if(yMax < val)
                yMax = val;
        }
    }

    Real margin = (yMax - yMin)*yBordersReserve;

    yMaxValue = yMax + margin;
    yMinValue = yMin - margin;
}

void PlotWidget::transformPainter(QPainter &painter)
{
    plotFieldRect = QRect(leftMargin, topMargin,
                          this->width() - leftMargin - rightMargin,
                          this->height() - topMargin - bottomMargin);
    painter.setBrush(Qt::white);
    painter.setPen(QPen(QBrush(Qt::black), 2));
    painter.drawRect(plotFieldRect);

    auto origin = QPoint(leftMargin, this->height() - bottomMargin);
    painter.translate(origin);
    painter.scale(1.0, -1.0);
}

void PlotWidget::drawPlotField(QPainter &painter)
{
    drawGrid(painter);
}

void PlotWidget::drawGrid(QPainter &painter)
{
    painter.setPen(gridPen);

    Real width = plotFieldRect.width();
    Real cellWidth = width / static_cast<Real>(xGridNum);
    int yBeg = 0;
    int yEnd = plotFieldRect.height();
    for(xGridPos = 0; xGridPos < width + 1; xGridPos += cellWidth) {
        auto x = qRound(xGridPos);
        painter.drawLine(x, yBeg, x, yEnd);
        drawHorizLabel(painter);
    }

    Real height = plotFieldRect.height();
    Real cellHeight = height / static_cast<Real>(yGridNum);
    int xBeg = 0;
    int xEnd = plotFieldRect.width();
    for(yGridPos = 0; yGridPos  < height + 1; yGridPos  += cellHeight) {
        auto y = qRound(yGridPos );
        painter.drawLine(xBeg, y, xEnd, y);
        drawVertLabel(painter);
    }
}

void PlotWidget::drawHorizLabel(QPainter &painter)
{
    labelNumber = (xMaxValue - xMinValue) * xGridPos / plotFieldRect.width() + xMinValue;
    calcLabelBounding();
    labelBounding.translate(qRound(xGridPos - labelBounding.width()/2.),
                            labelBounding.height() + 5);

    drawLabel(painter);
}

void PlotWidget::calcLabelBounding()
{
    labelText = QString::number(labelNumber, 'f', 2);
    QFontMetrics fontMetrics(labelFont);
    labelBounding = fontMetrics.boundingRect(labelText);
    labelBounding.setWidth(labelBounding.width() + 2);
}

void PlotWidget::drawLabel(QPainter& painter)
{
    painter.scale(1.0, -1.0);
    painter.setFont(labelFont);
    painter.drawText(labelBounding, labelText);
    painter.scale(1.0, -1.0);
}

void PlotWidget::drawVertLabel(QPainter &painter)
{
    labelNumber = (yMaxValue - yMinValue) * yGridPos / plotFieldRect.height() + yMinValue;
    calcLabelBounding();
    labelBounding.translate(-labelBounding.width() - 10, labelBounding.height()/4. - yGridPos);

    drawLabel(painter);
}

void PlotWidget::drawPlots(QPainter &painter)
{
    if(yMinValue < 0)
        translatePainterOrigin(painter);

    foreach(drawingPlot, plots)
        drawPlot(painter);
}

void PlotWidget::drawPlot(QPainter &painter)
{
    painter.setPen(drawingPlot.pen);

    kValueToPixels = plotFieldRect.height() / (yMaxValue - yMinValue);

    if(drawingPlot.data.size() == 1)
        drawLinePlot(painter, drawingPlot.data.front()*kValueToPixels);
    else
        drawPolylinePlot(painter);
}

void PlotWidget::translatePainterOrigin(QPainter &painter)
{
    Real refY = -yMinValue/(yMaxValue - yMinValue)*plotFieldRect.height();
    painter.translate(0, refY);
}

void PlotWidget::drawLinePlot(QPainter &painter, Real value)
{
    painter.drawLine(0, value, plotFieldRect.width(), value);
}

void PlotWidget::drawPolylinePlot(QPainter &painter)
{
    Real yBeg = drawingPlot.data.front()*kValueToPixels;
    Real xStep = plotFieldRect.width() / static_cast<Real>(drawingPlot.data.size());

    for(int i = 1; i != drawingPlot.data.size(); i++) {
        auto p = drawingPlot.data[i];
        auto yEnd = p*kValueToPixels;
        painter.drawLine((i-1)*xStep, yBeg, i*xStep, yEnd);
        yBeg = yEnd;
    }
}
