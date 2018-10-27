#include <QCoreApplication>
#include <QtDBus>

#include "login1.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setOrganizationDomain("org");
    QCoreApplication::setApplicationName("freedesktop");

    if (!QDBusConnection::systemBus().isConnected()) {
        qWarning("Cannot connect to the D-Bus system bus.");
        return 1;
    }

    if (!QDBusConnection::systemBus().registerService(LOGIN1_SERVICE)) {
        qWarning() << QDBusConnection::systemBus().lastError().message();
        return 1;
    }

    login1 service;
    if (!QDBusConnection::systemBus().registerObject(LOGIN1_PATH,
                                                     &service,
                                                     QDBusConnection::ExportAllContents)) {
        qWarning() << QDBusConnection::systemBus().lastError().message();
        return 1;
    }
    if (!QDBusConnection::systemBus().registerObject(LOGIN1_FULL_PATH,
                                                     &service,
                                                     QDBusConnection::ExportAllContents)) {
        qWarning() << QDBusConnection::systemBus().lastError().message();
        return 1;
    }

    return a.exec();
}
