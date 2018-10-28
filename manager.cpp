#include "manager.h"
#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QCoreApplication>
#include <QTimer>

Manager::Manager(QObject *parent) : QObject(parent)
  , ckit(0)
{
    ckit = new QDBusInterface(CONSOLEKIT_SERVICE,
                              CONSOLEKIT_MANAGER_PATH,
                              CONSOLEKIT_MANAGER,
                              QDBusConnection::systemBus(),
                              this);
    if (!ckit->isValid()) {
        qWarning() << "ConsoleKit is not available!!!";
        QTimer::singleShot(100, qApp, SLOT(quit()));
    }
    QDBusConnection system = QDBusConnection::systemBus();
    system.connect(CONSOLEKIT_SERVICE,
                   CONSOLEKIT_MANAGER_PATH,
                   CONSOLEKIT_MANAGER,
                   "PrepareForSleep",
                   this,
                   SLOT(handlePrepareForSuspend(bool)));
    system.connect(CONSOLEKIT_SERVICE,
                   CONSOLEKIT_MANAGER_PATH,
                   CONSOLEKIT_MANAGER,
                   "PrepareForShutdown",
                   this,
                   SLOT(handlePrepareForShutdown(bool)));
}

bool Manager::canAction(const QString &action)
{
    if (!ckit->isValid() || action.isEmpty()) { return false; }
    QDBusMessage reply = ckit->call(action);
    qDebug() << "reply for" << action << reply;
    if (reply.arguments().first().toString() == "yes") { return true; }
    bool result = reply.arguments().first().toBool();
    if (!reply.errorMessage().isEmpty()) { result = false; }
    return result;
}

const QString Manager::doAction(const QString &action)
{
    if (!ckit->isValid() || action.isEmpty()) {
        return "ConsoleKit is not running or action is empty";
    }
    QDBusMessage reply = ckit->call(action, true);
    return reply.errorMessage();
}

void Manager::handlePrepareForSuspend(bool suspend)
{
    qDebug() << "handle PrepareForSleep signal from ConsoleKit";
    emit PrepareForSleep(suspend);
}

void Manager::handlePrepareForShutdown(bool shutdown)
{
    qDebug() << "handle PrepareForShutdown signal from ConsoleKit";
    emit  PrepareForShutdown(shutdown);
}

void Manager::PowerOff(bool trigger)
{
    qDebug() << "PowerOff requested" << trigger;
    if (!trigger || !ckit->isValid()) { return; }
    QString result = doAction("PowerOff");
    if (!result.isEmpty()) { qWarning() << result; }
}

void Manager::Reboot(bool trigger)
{
    qDebug() << "Reboot requested" << trigger;
    if (!trigger || !ckit->isValid()) { return; }
    QString result = doAction("Reboot");
    if (!result.isEmpty()) { qWarning() << result; }
}

void Manager::Suspend(bool trigger)
{
    qDebug() << "Suspend requested" << trigger;
    if (!trigger || !ckit->isValid()) { return; }
    QString result = doAction("Suspend");
    if (!result.isEmpty()) { qWarning() << result; }
}

void Manager::Hibernate(bool trigger)
{
    qDebug() << "Hibernate requested" << trigger;
    if (!trigger || !ckit->isValid()) { return; }
    QString result = doAction("Hibernate");
    if (!result.isEmpty()) { qWarning() << result; }
}

void Manager::HybridSleep(bool trigger)
{
    qDebug() << "HybridSleep requested" << trigger;
    if (!trigger || !ckit->isValid()) { return; }
    QString result = doAction("HybridSleep");
    if (!result.isEmpty()) { qWarning() << result; }
}

const QString Manager::CanPowerOff()
{
    qDebug() << "CanPowerOff requested";
    if (canAction("CanPowerOff")) { return "yes"; }
    return "no";
}

const QString Manager::CanReboot()
{
    qDebug() << "CanReboot requested";
    if (canAction("CanReboot")) { return "yes"; }
    return "no";
}

const QString Manager::CanSuspend()
{
    qDebug() << "CanSuspend requested";
    if (canAction("CanSuspend")) { return "yes"; }
    return "no";
}

const QString Manager::CanHibernate()
{
    qDebug() << "CanHibernate requested";
    if (canAction("CanHibernate")) { return "yes"; }
    return "no";
}

const QString Manager::CanHybridSleep()
{
    qDebug() << "CanHybridSleep requested";
    if (canAction("CanHybridSleep")) { return "yes"; }
    return "no";
}

const QString Manager::Inhibit(const QString &what,
                               const QString &who,
                               const QString &why,
                               const QString &mode)
{
    QString result;
    qDebug() << "Inhibit requested" << what << who << why << mode;
    // https://github.com/rodlie/nologind/issues/2
    result = "/tmp/fofo"; // whatever, we don't care (for now)
    return result;
}
