#include "ScribbleArea.h"
#include "qevent.h"
#include <QPainter>

ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    painting = false;
    penWidth = 1;
    penColor = Qt::blue;
}

bool ScribbleArea::openImage(const QString &filename)
{
    QImage loadimage;
    if(!loadimage.load(filename)){
            return false;
    }
    QSize newSize = loadimage.size().expandedTo(size());
    resizeImage(&loadimage, newSize);
    this->image = loadimage;
    modified = false;
    update();
    return true;
}

bool ScribbleArea::saveImage(const QString &filename, const char *fileFormat)
{
    QImage visibleImage = this->image;
    resizeImage(&visibleImage, size());
    if(visibleImage.save(filename, fileFormat)){
        modified = false;
        return true;
    }
    return false;
}

void ScribbleArea::setPenColor(const QColor &color)
{
    this->penColor = color;
}

void ScribbleArea::setPenWidth(int newWidth)
{
    this->penWidth = newWidth;
}

void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    if(image->size() == newSize){
        return;
    }
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(this->penColor, this->penWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;
    int rad = (this->penWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void ScribbleArea::clearImage()
{
    this->image.fill(qRgb(255,255,255));
    modified = true;
    update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        lastPoint = event->pos();
        painting = true;
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && this->painting){
        drawLineTo(event->pos());
        painting = false;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && painting){
            drawLineTo(event->pos());
    }
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dRect = event->rect();
    painter.drawImage(dRect, image, dRect);
}

void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
            int newWidth = qMax(width() + 128, image.width());
            int newHeight = qMax(height() + 128, image.height());
            resizeImage(&image, QSize(newWidth, newHeight));
            update();
        }
    QWidget::resizeEvent(event);
}
