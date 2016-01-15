#include "FenHisto.h"
#include "ui_fenhisto.h"

#include "qwt_plot.h"
#include "qwt.h"
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include "qwt_plot_histogram.h"
#include "qwt_plot_intervalcurve.h"
#include "Histogramme.h"

FenHisto::FenHisto(Histogramme h, const QColor &color,QWidget *parent) :
    ui(new Ui::FenHisto)
{
    ui->setupUi(this);

    QVector<QwtIntervalSample> p = createPoint(h);
    QwtPlotHistogram *histo = new QwtPlotHistogram("Histogramme");
    histo->setTitle( "Histogramme" );
    histo->setPen( color, 4 );
    histo->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    histo->setSamples(p);
    histo->attach(this);
    this->resize( 600, 400 );
}

FenHisto::~FenHisto()
{
    delete ui;
}

void FenHisto::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QVector<QwtIntervalSample> FenHisto::createPoint(Histogramme h){
    QVector<QwtIntervalSample> points;

    for(int i=0; i<256;i++){
        points<<QwtIntervalSample(h.gettableauHisto()[i],i,i+1);
    }
    return points;
}
