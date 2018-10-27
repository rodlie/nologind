#ifndef LOGIN1_H
#define LOGIN1_H

#include <QObject>

#define LOGIN1_SERVICE "org.freedesktop.login1"
#define LOGIN1_PATH "/login1"
#define LOGIN1_FULL_PATH "/org/freedesktop/login1"

class login1 : public QObject
{
    Q_OBJECT
public:
    explicit login1(QObject *parent = NULL);

signals:
    void test();

public slots:
};

#endif // LOGIN1_H
