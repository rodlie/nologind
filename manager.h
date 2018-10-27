#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = NULL);

signals:

public slots:
    const QString Inhibit(const QString &what,
                          const QString &who,
                          const QString &why,
                          const QString &mode);
};

#endif // MANAGER_H
