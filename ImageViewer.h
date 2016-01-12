#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QtWidgets>


class ImageViewer : public QLabel
{
public:
    ImageViewer();

    QPoint getOrigineSel() const;
    void setOrigineSel(const QPoint &value);

    QPoint getFinSel() const;
    void setFinSel(const QPoint &value);

    QPoint getPipette() const;
    void setPipette(const QPoint &value);

    void sign();

signals :
    void sign_pip();

protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);

private:
    qint64  pixmapKey;
    QRubberBand *r;
    QPoint origineSel,finSel,pipette;
    bool selEncours;
};

#endif // IMAGEVIEWER_H
