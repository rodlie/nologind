#include "manager.h"
#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QCoreApplication>
#include <QTimer>

Manager::Manager(QObject *parent) : QObject(parent)
  , ckit(0)
  , upower(0)
  , shutdownStatus(false)
  , sleepStatus(false)
{
    QDBusConnection system = QDBusConnection::systemBus();
    if (!system.isConnected()) {
        qWarning() << "D-Bus not available!!!";
        QTimer::singleShot(0, qApp, SLOT(quit()));
    }
    ckit = new QDBusInterface(CONSOLEKIT_SERVICE,
                              CONSOLEKIT_MANAGER_PATH,
                              CONSOLEKIT_MANAGER,
                              system,
                              this);
    upower = new QDBusInterface(UPOWER_SERVICE,
                                UPOWER_PATH,
                                UPOWER_MANAGER,
                                system,
                                this);
    if (!ckit->isValid()) {
        qWarning() << "ConsoleKit is not available!!!";
        QTimer::singleShot(100, qApp, SLOT(quit()));
    }
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

bool Manager::Docked()
{
    if (upower->isValid()) { return upower->property("IsDocked").toBool(); }
    return false;
}

bool Manager::PreparingForShutdown()
{
    return shutdownStatus;
}

bool Manager::PreparingForSleep()
{
    return sleepStatus;
}

bool Manager::canAction(const QString &action)
{
    if (!ckit->isValid() || action.isEmpty()) { return false; }
    QDBusMessage reply = ckit->call(action);
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
    sleepStatus = suspend;
    emit PrepareForSleep(suspend);
}

void Manager::handlePrepareForShutdown(bool shutdown)
{
    shutdownStatus = shutdown;
    emit  PrepareForShutdown(shutdown);
}

void Manager::PowerOff(bool trigger)
{
    if (!trigger || !ckit->isValid()) { return; }
    QString result = doAction("PowerOff");
    if (!result.isEmpty()) { qWarning() << result; }
}

void Manager::Reboot(bool trigger)
{
    if (!trigger || !ckit->isValid()) { return; }
    QString result = doAction("Reboot");
    if (!result.isEmpty()) { qWarning() << result; }
}

void Manager::Suspend(bool trigger)
{
    if (!trigger || !ckit->isValid()) { return; }
    QString result = doAction("Suspend");
    if (!result.isEmpty()) { qWarning() << result; }
}

void Manager::Hibernate(bool trigger)
{
    if (!trigger || !ckit->isValid()) { return; }
    QString result = doAction("Hibernate");
    if (!result.isEmpty()) { qWarning() << result; }
}

void Manager::HybridSleep(bool trigger)
{
    if (!trigger || !ckit->isValid()) { return; }
    QString result = doAction("HybridSleep");
    if (!result.isEmpty()) { qWarning() << result; }
}

const QString Manager::CanPowerOff()
{
    if (canAction("CanPowerOff")) { return "yes"; }
    return "no";
}

const QString Manager::CanReboot()
{
    if (canAction("CanReboot")) { return "yes"; }
    return "no";
}

const QString Manager::CanSuspend()
{
    if (canAction("CanSuspend")) { return "yes"; }
    return "no";
}

const QString Manager::CanHibernate()
{
    if (canAction("CanHibernate")) { return "yes"; }
    return "no";
}

const QString Manager::CanHybridSleep()
{
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
