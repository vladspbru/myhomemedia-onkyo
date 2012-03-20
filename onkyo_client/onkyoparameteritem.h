#ifndef ONKYOPARAMETERITEM_H
#define ONKYOPARAMETERITEM_H

#include <QtDeclarative/QDeclarativeItem>

class OnkyoParameterItem : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(OnkyoParameterItem)

    Q_PROPERTY(QString nik   READ nik   WRITE setNik)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit OnkyoParameterItem(QDeclarativeItem *parent = 0);

    Q_INVOKABLE void query(const QString& sub);

signals:
    void valueChanged();

public slots:
    void query_status() { query("QSTN"); }

protected:
    QString nik() { return nik_; }
    void setNik(const QString& c) { nik_ = c; }
    QString value() { return value_; }
    void setValue(const QString& v) { value_ = v; }


    QString nik_;
    QString value_;
};

QML_DECLARE_TYPE(OnkyoParameterItem)

#endif // ONKYOPARAMETERITEM_H
