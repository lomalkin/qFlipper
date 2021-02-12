#include "screenwidget.h"

#include <QPainter>
#include <QDebug>

ScreenWidget::ScreenWidget(QWidget *parent) :
    QWidget(parent), canvas(FLIPPER_SCREEN_WIDTH, FLIPPER_SCREEN_HEIGHT, QImage::Format_Mono)
{
    clearCanvas();
    setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
}

void ScreenWidget::paintEvent(QPaintEvent *event) {
    (void) event;

    QPainter p;
    p.begin(this);
    p.drawImage(this->rect(), this->canvas);
    p.end();
}

void ScreenWidget::clearCanvas() {
    qDebug() << this << "Clearing canvas";
    canvas.fill(1);
    QPainter p;
    p.begin(&canvas);
    p.drawText(canvas.rect(), Qt::AlignCenter, "No Signal");
    p.end();
    update();
}

void ScreenWidget::data(QByteArray data) {
    qDebug() << this << "data" << data.length();
    for (size_t x=0; x < FLIPPER_SCREEN_WIDTH; x++) {
        for (size_t y=0; y < FLIPPER_SCREEN_HEIGHT; y++) {
            auto i = y / 8 * 128 + x;
            auto z = y & 7;
            auto color = (data.at(i) & (1 << z)) == 0;
            canvas.setPixel(x, y, color);
        }
    }
    update();
}
