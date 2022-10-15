#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class ScribbleArea : public QWidget
{
    Q_OBJECT
public:
    explicit ScribbleArea(QWidget *parent = nullptr);
    bool openImage(const QString &filename);
    bool saveImage(const QString &filename, const char *fileFormat);
    void setPenColor(const QColor &color);
    void setPenWidth(int newWidth);

    bool isModify() const {return modified;}
    QColor getPenColor() const {return penColor;}
    int getPenWidth() const {return penWidth;}
    void resizeImage(QImage *image, const QSize &newSize);
    void drawLineTo(const QPoint &endPoint);
public slots:
    void clearImage();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    bool modified;
    bool painting;
    int penWidth;
    QColor penColor;
    QImage image;
    QPoint lastPoint;
signals:

};

#endif // SCRIBBLEAREA_H
