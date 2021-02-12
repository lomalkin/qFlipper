#ifndef STREAMPARSER_H
#define STREAMPARSER_H

#include <QObject>

class StreamParser : public QObject
{
    Q_OBJECT
    const QByteArray header;
    QByteArray buffer;
    bool found;

public:
    explicit StreamParser(QObject *parent = nullptr);

    void feed(QByteArray);

signals:
    void screenData(QByteArray);
};

#endif // STREAMPARSER_H
