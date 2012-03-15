#include "onkyoremoteitem.h"
#include <QtDeclarative/qdeclarative.h>

#include "onkyoclient.h"

OnkyoRemoteItem::OnkyoRemoteItem(QDeclarativeItem *parent):
    QDeclarativeItem(parent)
{
    // By default, QDeclarativeItem does not draw anything. If you subclass
    // QDeclarativeItem to create a visual item, you will need to uncomment the
    // following line:
    // setFlag(ItemHasNoContents, false);
}

OnkyoRemoteItem::~OnkyoRemoteItem()
{
}

QString OnkyoRemoteItem::addr()
{
    return addr_;
}
void OnkyoRemoteItem::setAddr(const QString& addr)
{
    addr_ = addr;
    removeLink();
}

int OnkyoRemoteItem::port()
{
    return port_;
}
void OnkyoRemoteItem::setPort(int p)
{
    port_ = p;
    removeLink();
}

void OnkyoRemoteItem::removeLink()
{
    if(! onkyo_.isNull() ){
        this->disconnect(onkyo_.data());
        onkyo_.reset();
    }
}

void OnkyoRemoteItem::createLink()
{
    onkyo_.reset( new OnkyoClient() );
    onkyo_->init(addr_, port_);
    connect(onkyo_.data(), SIGNAL( newStatus(QString) ), this, SLOT(status_(QString)) );
    connect(onkyo_.data(), SIGNAL( error(QString)), this, SLOT(error_(QString)) );
}

void OnkyoRemoteItem::status_(const QString &str)
{
    if( str.isEmpty() )
        emit connectChanged();
    else emit status(str);
}

void OnkyoRemoteItem::error_(const QString &str)
{
    qDebug() << str.toLocal8Bit();
}

bool OnkyoRemoteItem::getConnected()
{
    return ( !onkyo_.isNull() && onkyo_->is_connected() );
}

void OnkyoRemoteItem::cmd(const QString &str)
{
    if( onkyo_.isNull() )
           createLink();
    onkyo_->request(str);
}

