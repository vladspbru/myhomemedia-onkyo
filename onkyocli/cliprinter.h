#ifndef CLIPRINTER_H
#define CLIPRINTER_H

#include <QObject>

class CliPrinter : public QObject
{
    Q_OBJECT
public:
    explicit CliPrinter(QObject *parent = 0);
    
signals:
    
public slots:
    void cout(const QString& s);
    void cerr(const QString& s);

};

#endif // CLIPRINTER_H
