#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QWidget>
#include <QImage>
#include <QColor>

#define FLIPPER_SCREEN_WIDTH 128
#define FLIPPER_SCREEN_HEIGHT 64
#define FLIPPER_SCREEN_RATIO (FLIPPER_SCREEN_WIDTH / FLIPPER_SCREEN_HEIGHT)

class ScreenWidget : public QWidget
{
    Q_OBJECT

    QImage canvas;
    const QColor color_0;
    const QColor color_1;

protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit ScreenWidget(QWidget *parent = nullptr);
    void saveToFile(QString filename);

public slots:
    void clearCanvas();
    void data(QByteArray);
};

#endif // SCREENWIDGET_H
