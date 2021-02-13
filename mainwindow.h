#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

class StreamParser;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *) override;
    void timerEvent(QTimerEvent *event) override;

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    StreamParser *parser;

    void openPort();
    void closePort();

private slots:
    void onSerialClose();
    void onPortsUpdate();
    void onConnect();
    void onScreenSave();
    void onReadyRead();
};
#endif // MAINWINDOW_H
