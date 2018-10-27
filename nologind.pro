TARGET = nologind
VERSION = 0.1
QT += core dbus
QT -= gui
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += $${TARGET}.cpp manager.cpp
HEADERS += manager.h
OTHER_FILES += nologind.conf.in

isEmpty(PREFIX): PREFIX = /usr/local
isEmpty(DBUS_CONF): DBUS_CONF = /etc
isEmpty(DBUS_SERVICE): DBUS_SERVICE = /usr/share
isEmpty(DOCDIR): DOCDIR = $$PREFIX/share/doc
isEmpty(USER): USER = root
isEmpty(GROUP): GROUP = users

target.path = $${PREFIX}/sbin
target_dbus_conf.path = $${DBUS_CONF}/dbus-1/system.d
target_dbus_service.path = $${DBUS_SERVICE}/dbus-1/system-services
target_dbus_conf.commands = $$quote(cat $${PWD}/nologind.conf.in | sed "\"s/_GROUP_/$${GROUP}/g;s/_USER_/$${USER}/g"\" > ${INSTALL_ROOT}$${DBUS_CONF}/dbus-1/system.d/org.freedesktop.login1.conf$$escape_expand(\\n\\t))
target_dbus_service.commands = $$quote(echo "\"[D-BUS Service]"\" > ${INSTALL_ROOT}$${DBUS_SERVICE}/dbus-1/system-services/org.freedesktop.login1.service$$escape_expand(\\n\\t))
target_dbus_service.commands += $$quote(echo "\"Name=org.freedesktop.login1"\" >> ${INSTALL_ROOT}$${DBUS_SERVICE}/dbus-1/system-services/org.freedesktop.login1.service$$escape_expand(\\n\\t))
target_dbus_service.commands += $$quote(echo "\"Exec=$${PREFIX}/sbin/$${TARGET}"\" >> ${INSTALL_ROOT}$${DBUS_SERVICE}/dbus-1/system-services/org.freedesktop.login1.service$$escape_expand(\\n\\t))
target_dbus_service.commands += $$quote(echo "\"User=$${USER}"\" >> ${INSTALL_ROOT}$${DBUS_SERVICE}/dbus-1/system-services/org.freedesktop.login1.service$$escape_expand(\\n\\t))
INSTALLS += target target_dbus_conf target_dbus_service
