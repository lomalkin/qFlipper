#include "screenwidget.h"

#include <QPainter>
#include <QDebug>

ScreenWidget::ScreenWidget(QWidget *parent) :
    QWidget(parent),
    canvas(FLIPPER_SCREEN_WIDTH, FLIPPER_SCREEN_HEIGHT, QImage::Format_RGB32),
    color_0(QColor(0xFF, 0x8B, 0x29)),
    color_1(QColor(0, 0, 0))
{
    clearCanvas();
    setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
}

void ScreenWidget::saveToFile(QString filename) {
    canvas.save(filename);
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

    canvas.fill(Qt::GlobalColor::white);

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
            auto color = ((data.at(i) & (1 << z))) ? color_1 : color_0;
            canvas.setPixelColor(x, y, color);
        }
    }
    update();
}
