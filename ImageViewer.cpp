#include "ImageViewer.h"

#include <iostream>
#include <string>

using namespace std;

ImageViewer::ImageViewer()
{
    setMouseTracking(true);
    r = new QRubberBand(QRubberBand::Rectangle,this);
    selEncours = false;
}

void ImageViewer::mousePressEvent(QMouseEvent *e)
{
    r->hide();
    if (e->button() == Qt::LeftButton) {
        origineSel = e->pos();
        pipette = e->pos();
        selEncours=true;
    }
}

void ImageViewer::mouseMoveEvent(QMouseEvent *e)
{
    if (selEncours) {
        qreal x = origineSel.x(), y = origineSel.y(), w = e->pos().x()-origineSel.x(), h = e->pos().y()-origineSel.y();
        if(x > e->x()) {
            x = e->x();
            w *= -1;
        }
        if(y > e->y()) {
            y = e->y();
            h *= -1;
        }
        if (x + w > this->width()) {
            w = this->width() - x;
        }
        if (x < 0) {
            w += x;
            x = 0;
        }
        if (y + h > this->height()) {
            h = this->height() - y;
        }
        if (y < 0) {
            h += y;
            y = 0;
        }
        r->setGeometry(x, y, w, h);
        r->show();
    }
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        finSel = e->pos();
        selEncours = false;
    }
}

QPoint ImageViewer::getPipette() const
{
    return pipette;
}

void ImageViewer::setPipette(const QPoint &value)
{
    pipette = value;
}

QPoint ImageViewer::getFinSel() const
{
    return finSel;
}

void ImageViewer::setFinSel(const QPoint &value)
{
    finSel = value;
}

QPoint ImageViewer::getOrigineSel() const
{
    return origineSel;
}

void ImageViewer::setOrigineSel(const QPoint &value)
{
    origineSel = value;
}
