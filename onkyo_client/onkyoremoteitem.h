#ifndef ONKYOREMOTEITEM_H
#define ONKYOREMOTEITEM_H

#include <QtDeclarative/QDeclarativeItem>
#include <QScopedPointer>

class OnkyoClient;
class OnkyoRemoteItem : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(OnkyoRemoteItem)

    Q_PROPERTY(QString addr READ addr WRITE setAddr)
    Q_PROPERTY(int     port READ port WRITE setPort)
    Q_PROPERTY(bool connected  READ getConnected  NOTIFY connectChanged)

public:
    OnkyoRemoteItem(QDeclarativeItem *parent = 0);
    ~OnkyoRemoteItem();

    Q_INVOKABLE void cmd(const QString& str);

signals:
    void status(const QString& str);
    void connectChanged();

private slots:
    void status_(const QString& str);
    void error_(const QString& str);

private:

    QString addr();
    void setAddr(const QString& addr);
    int  port();
    void setPort(int p);

    bool getConnected();
    void removeLink();
    void createLink();

    QString addr_;
    int     port_;

    QScopedPointer<OnkyoClient> onkyo_;
};

QML_DECLARE_TYPE(OnkyoRemoteItem)

#endif // ONKYOREMOTEITEM_H

