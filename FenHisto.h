#ifndef FENHISTO_H
#define FENHISTO_H

#include <QWidget>
#include "qwt_plot.h"
#include "qwt.h"
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include "qwt_plot_histogram.h"
#include "qwt_plot_intervalcurve.h"
#include "Histogramme.h"

namespace Ui {
class FenHisto;
}

class FenHisto : public QwtPlot
{
    Q_OBJECT

public:
    FenHisto(Histogramme h,const QColor &color,QWidget *parent = 0 );
    ~FenHisto();

    QVector<QwtIntervalSample> createPoint(Histogramme h);
private:
    Ui::FenHisto *ui;

protected:
     void changeEvent(QEvent *e);
};

#endif // FENHISTO_H
