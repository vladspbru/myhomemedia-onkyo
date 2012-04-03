#include "onkyoremoteitem.h"
#include <QtDeclarative/qdeclarative.h>

#include "onkyoparameteritem.h"
#include "onkyoclient.h"

OnkyoRemoteItem::OnkyoRemoteItem(QDeclarativeItem *parent):
    QObject(parent)
{
}

OnkyoRemoteItem::~OnkyoRemoteItem()
{
}

bool OnkyoRemoteItem::getConnected() const
{
    return ( !onkyo_.isNull() && onkyo_->is_connected() );
}

void OnkyoRemoteItem::connect_(bool conn)
{
    bool linked_ = getConnected();
    if( linked_ != conn ){

        if(conn){
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
        else {//make diskonnect
            if(! onkyo_.isNull() ){
                this->disconnect(onkyo_.data());
                onkyo_.reset();
            }
        }
        emit connectChanged();
    }

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

void OnkyoRemoteItem::cmd(const QString &str)
{
    if( getConnected()==false )
        connect_(true);

    if( getConnected() )
        onkyo_->request(str);
}

OnkyoParameterItem* OnkyoRemoteItem::getParameter(const QString& name)
{
    OnkyoParameterItem* param=0;
    foreach(OnkyoParameterItem* p, params_){
        if( p->nik() == name ){
            param = p;
            break;
        }
    }

    if( param == 0 ){
        param = new OnkyoParameterItem(this);
        param->setNik(name);
        params_.append(param);
        parametersChanged();
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
        onkyo->parametersChanged();
    }
}

void OnkyoRemoteItem::query_all_parameters_state()
{
    foreach(OnkyoParameterItem* p, params_){
        p->query_state();
    }
}

