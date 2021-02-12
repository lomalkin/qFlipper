#include "streamparser.h"

#include <QDebug>

StreamParser::StreamParser(QObject *parent) : QObject(parent),
    header(QByteArray::fromHex("F0E1D2C3")),
    buffer(),
    found(false)
{

}

void StreamParser::feed(QByteArray data) {
    buffer += data;

    if (!found) {
        int pos = buffer.indexOf(header);
        if (pos >= 0) {
            buffer = buffer.right(buffer.length() - pos - header.size());
            found = true;
        } else {
            buffer = buffer.right(4);
        }
    }

    if (found) {
        if(buffer.size()>=1024) {
            auto data = buffer.left(1024);
            emit screenData(data);
            buffer = buffer.right(buffer.length() - 1024);
            found = false;
        }
    }
}
