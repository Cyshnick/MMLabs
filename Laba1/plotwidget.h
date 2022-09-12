#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QPen>
#include "shared.h"

template <typename T>
using List = QList<T>;

class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    PlotWidget(QWidget* parent = nullptr);

    void addPlot(Reals const& data, QPen const &pen);
    void addPlot(Real yValue, QPen const& pen);
    void clear();

    void setYMax(Real val);
    void setYMin(Real val);
    void setXMax(Real val);
    void setXMin(Real val);

    void setNumOfXGridLines(size_t val);
    void setNumOfYGridLines(size_t val);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    struct Plot {
        Reals data;
        QPen pen;
    };

    void addPlot(Plot const& plot);

    void autoFindYBorders();

    void transformPainter(QPainter& painter);
    void drawPlotField(QPainter& painter);
    void drawGrid(QPainter& painter);

    void drawHorizLabel(QPainter& painter);
    void calcLabelBounding();
    void drawLabel(QPainter& painter);
    void drawVertLabel(QPainter& painter);
    void drawPlots(QPainter& painter);
    void drawPlot(QPainter& painter);
    void translatePainterOrigin(QPainter& painter);
    void drawLinePlot(QPainter& painter, Real value);
    void drawPolylinePlot(QPainter& painter);

    Real kValueToPixels;
    Plot drawingPlot;

    List<Plot> plots;

    QPen gridPen;

    Real xMaxValue;
    Real xMinValue;
    Real yMaxValue;
    Real yMinValue;

    int xGridNum;
    int yGridNum;

    QFont labelFont;
    Real labelNumber;
    QRect labelBounding;
    QString labelText;

    const int leftMargin = 60;
    const int rightMargin = 40;
    const int topMargin = 20;
    const int bottomMargin = 30;

    const Real yBordersReserve = 0.1;

    Real xGridPos;
    Real yGridPos;

    QRect plotFieldRect;
};

#endif // PLOTWIDGET_H
