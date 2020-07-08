#ifndef PROTOCOL_COMM_INTERFACE_H
#define PROTOCOL_COMM_INTERFACE_H

#include <QObject>
#include <QString>
#include <QByteArray>


class CommInterface : public QObject
{
    Q_OBJECT
public:
    CommInterface();
    virtual ~CommInterface();

    virtual qint64 Send(const QByteArray &data) = 0;
    virtual bool Open() = 0;
    virtual void Close() = 0;
    virtual bool IsOpen() = 0;

signals:
    void onRecv(QByteArray &data, void *extra_data);

};



#endif // PROTOCOL_COMM_INTERFACE_H
