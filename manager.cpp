#include "manager.h"
#include <QDebug>

Manager::Manager(QObject *parent) : QObject(parent)
{

}

const QString Manager::Inhibit(const QString &what,
                               const QString &who,
                               const QString &why,
                               const QString &mode)
{
    qDebug() << "Inhibit requested" << what << who << why << mode;
    return "/tmp/fofo";
}
