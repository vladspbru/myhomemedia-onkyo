#include "onkyoparameteritem.h"
#include "onkyoremoteitem.h"


OnkyoParameterItem::OnkyoParameterItem(QObject *parent) :
    QObject(parent)
{
}


void OnkyoParameterItem::cmd(const QString& subcmd)
{
    OnkyoRemoteItem* onkyo = dynamic_cast<OnkyoRemoteItem*>( this->parent() );
    if(onkyo){
        onkyo->cmd( nik_+subcmd );
        qDebug() << "Cmd: nik="<< nik_<< ", subcmd=" << subcmd;
    }
    else
        qDebug() << "No ONKYO, No Parent! OnkyoParameterItem : nik="<< nik_<< ", subcmd=" << subcmd;

}

void OnkyoParameterItem::setValue(const QString& v)
{
    if(value_ != v){
        value_ = v;
        emit valueChanged();
    }
}


