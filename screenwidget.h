#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QWidget>
#include <QImage>

#define FLIPPER_SCREEN_WIDTH 128
#define FLIPPER_SCREEN_HEIGHT 64
#define FLIPPER_SCREEN_RATIO (FLIPPER_SCREEN_WIDTH / FLIPPER_SCREEN_HEIGHT)

class ScreenWidget : public QWidget
{
    Q_OBJECT

    QImage canvas;

protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit ScreenWidget(QWidget *parent = nullptr);

public slots:
    void clearCanvas();
    void data(QByteArray);
};

#endif // SCREENWIDGET_H
