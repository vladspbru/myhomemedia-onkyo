#include "onkyoparameteritem.h"
#include "onkyoremoteitem.h"


OnkyoParameterItem::OnkyoParameterItem(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
}


void OnkyoParameterItem::query(const QString& subcmd)
{
    OnkyoRemoteItem* onkyo = dynamic_cast<OnkyoRemoteItem*>( this->parent() );
    if(onkyo){
        onkyo->cmd( nik_+subcmd );
        qDebug()<<"Cmd: nik="<< nik_<<", subcmd="<<subcmd;
    }
}



