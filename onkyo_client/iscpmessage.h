#ifndef ISCPMESSAGE_H
#define ISCPMESSAGE_H

#include <QByteArray>

class IscpMessage
{
public:
    static const int header_size;

    IscpMessage(int sz = 0);
    IscpMessage(const QByteArray&  ba);

    QByteArray&  bytes(void) {
        return block;
    }

    int  message_size() const {
        return block.size()==0 ? 0 : block.size() - header_size;
    }

    const char*  message() const {
        return block.size()==0 ? 0 : &block.constData()[ header_size ];
    }

    char*  message(){
        return block.size()==0 ? 0 : &block.data()[header_size];
    }

    void  make_rawcommand(const QString &cmd);
    const QByteArray& make_command(const QString &cmd);

private:
    QByteArray block;

};

#endif // ISCPMESSAGE_H