#include <QCoreApplication>
#include <QtDBus>

#include "manager.h"

#define LOGIN1_SERVICE "org.freedesktop.login1"
#define LOGIN1_PATH "/login1"
#define LOGIN1_FULL_PATH "/org/freedesktop/login1"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setOrganizationDomain("org");
    QCoreApplication::setApplicationName("freedesktop.login1");

    if (!QDBusConnection::systemBus().isConnected()) {
        qWarning("Cannot connect to the D-Bus system bus.");
        return 1;
    }

    if (!QDBusConnection::systemBus().registerService(LOGIN1_SERVICE)) {
        qWarning() << QDBusConnection::systemBus().lastError().message();
        return 1;
    }

    Manager man;
    if (!QDBusConnection::systemBus().registerObject(LOGIN1_PATH,
                                                     &man,
                                                     QDBusConnection::ExportAllContents)) {
        qWarning() << QDBusConnection::systemBus().lastError().message();
        return 1;
    }
    if (!QDBusConnection::systemBus().registerObject(LOGIN1_FULL_PATH,
                                                     &man,
                                                     QDBusConnection::ExportAllContents)) {
        qWarning() << QDBusConnection::systemBus().lastError().message();
        return 1;
    }

    return a.exec();
}
