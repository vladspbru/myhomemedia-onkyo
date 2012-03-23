#include "onkyoremoteitem.h"
#include <QtDeclarative/qdeclarative.h>

#include "onkyoparameteritem.h"
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
    connect(onkyo_.data(), SIGNAL( newStatus(QString) ), this, SLOT(status_(QString)) );
    connect(onkyo_.data(), SIGNAL( error(QString)), this, SLOT(error_(QString)) );

    if(addr_.isEmpty())
        onkyo_->init();
    else {
        DeviceInfo d;
        d.addr = QHostAddress(addr_);
        d.port = port_;
        onkyo_->init(d);
    }
    onkyo_->setConnected(true);
}

void OnkyoRemoteItem::status_(const QString &str)
{
    if( str.isEmpty() )
        emit connectChanged();
    else {
        emit status(str);
        foreach(OnkyoParameterItem* p, params_){
            if( str.startsWith( p->nik() ) )
                p->setValue( QString(str).remove(0, p->nik().size() ) );
        }
    }
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

OnkyoParameterItem* OnkyoRemoteItem::takeParameter(const QString& name)
{
    OnkyoParameterItem* param=0;
    foreach(OnkyoParameterItem* p, params_){
        if( p->nik() == name )
            param = p;
            break;
    }

    if( param == 0 ){
        OnkyoParameterItem* param = new OnkyoParameterItem(this);
        param->setNik(name);
        params_.push_back(param);
        emit parametersChanged();
    }
    return param;
}

QDeclarativeListProperty<OnkyoParameterItem> OnkyoRemoteItem::parameters()
{
    return QDeclarativeListProperty<OnkyoParameterItem>(this, 0, &OnkyoRemoteItem::append_param);
}

void OnkyoRemoteItem::append_param(QDeclarativeListProperty<OnkyoParameterItem> *list, OnkyoParameterItem *par)
{
    OnkyoRemoteItem *onkyo = qobject_cast<OnkyoRemoteItem *>(list->object);
    if (onkyo) {
        onkyo->params_.append(par);
        emit onkyo->parametersChanged();
    }
}

void OnkyoRemoteItem::query_parameters_state()
{
    foreach(OnkyoParameterItem* p, params_){
            p->query_state();
    }
}

