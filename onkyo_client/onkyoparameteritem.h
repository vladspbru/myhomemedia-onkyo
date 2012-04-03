#ifndef ONKYOPARAMETERITEM_H
#define ONKYOPARAMETERITEM_H

#include <QObject>

class OnkyoParameterItem : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(OnkyoParameterItem)

    Q_PROPERTY(QString nik   READ nik   WRITE setNik)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit OnkyoParameterItem(QObject *parent = 0);

    QString nik() { return nik_; }
    void setNik(const QString& c) { nik_ = c; }

    QString value() { return value_; }
    void setValue(const QString& v);

    Q_INVOKABLE void cmd(const QString& sub);

signals:
    void valueChanged();

public slots:
    void query_state() { cmd("QSTN"); }


protected:
    QString nik_;
    QString value_;
};

#endif // ONKYOPARAMETERITEM_H
