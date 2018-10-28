#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QString>
#include <QDBusInterface>

#define CONSOLEKIT_SERVICE "org.freedesktop.ConsoleKit"
#define CONSOLEKIT_MANAGER_PATH "/org/freedesktop/ConsoleKit/Manager"
#define CONSOLEKIT_MANAGER "org.freedesktop.ConsoleKit.Manager"

#define UPOWER_SERVICE "org.freedesktop.UPower"
#define UPOWER_PATH "/org/freedesktop/UPower"
#define UPOWER_MANAGER "org.freedesktop.UPower"

class Manager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool Docked READ Docked)
    Q_PROPERTY(bool PreparingForShutdown READ PreparingForShutdown)
    Q_PROPERTY(bool PreparingForSleep READ PreparingForSleep)

public:
    explicit Manager(QObject *parent = NULL);
    bool Docked();
    bool PreparingForShutdown();
    bool PreparingForSleep();
/*
      readwrite b EnableWallMessages = false;
      readwrite s WallMessage = '';
      readonly u NAutoVTs = 6;
      readonly as KillOnlyUsers = [];
      readonly as KillExcludeUsers = ['root'];
      readonly b KillUserProcesses = false;
      readonly b RebootToFirmwareSetup = false;
      readonly b IdleHint = false;
      readonly t IdleSinceHint = 0;
      readonly t IdleSinceHintMonotonic = 0;
      readonly s BlockInhibited = 'handle-power-key:handle-suspend-key:handle-hibernate-key';
      readonly s DelayInhibited = 'sleep';
      readonly t InhibitDelayMaxUSec = 5000000;
      readonly s HandlePowerKey = 'poweroff';
      readonly s HandleSuspendKey = 'suspend';
      readonly s HandleHibernateKey = 'hibernate';
      readonly s HandleLidSwitch = 'suspend';
      readonly s HandleLidSwitchDocked = 'ignore';
      readonly t HoldoffTimeoutUSec = 30000000;
      readonly s IdleAction = 'ignore';
      readonly t IdleActionUSec = 1800000000;
[X]   readonly b PreparingForShutdown = false;
[X]   readonly b PreparingForSleep = false;
      readonly (st) ScheduledShutdown = ('', 0);
[X]   readonly b Docked = false;
*/

private:
    QDBusInterface *ckit;
    QDBusInterface *upower;
    bool shutdownStatus;
    bool sleepStatus;

signals:
    void PrepareForShutdown(bool shutdown);
    void PrepareForSleep(bool suspend);
/*
      SessionNew(s session_id,
                 o object_path);
      SessionRemoved(s session_id,
                     o object_path);
      UserNew(u uid,
              o object_path);
      UserRemoved(u uid,
                  o object_path);
      SeatNew(s seat_id,
              o object_path);
      SeatRemoved(s seat_id,
                  o object_path);
[X]   PrepareForShutdown(b start);
[X]   PrepareForSleep(b start);
*/

private slots:
    bool canAction(const QString &action);
    const QString doAction(const QString &action);
    void handlePrepareForSuspend(bool suspend);
    void handlePrepareForShutdown(bool shutdown);

public slots:
    void PowerOff(bool trigger);
    void Reboot(bool trigger);
    void Suspend(bool trigger);
    void Hibernate(bool trigger);
    void HybridSleep(bool trigger);
    const QString CanPowerOff();
    const QString CanReboot();
    const QString CanSuspend();
    const QString CanHibernate();
    const QString CanHybridSleep();
    const QString Inhibit(const QString &what,
                          const QString &who,
                          const QString &why,
                          const QString &mode);
/*
GetSession(in  s session_id,
                 out o object_path);
      GetSessionByPID(in  u pid,
                      out o object_path);
      GetUser(in  u uid,
              out o object_path);
      GetUserByPID(in  u pid,
                   out o object_path);
      GetSeat(in  s seat_id,
              out o object_path);
      ListSessions(out a(susso) session_list);
      ListUsers(out a(uso) user_list);
      ListSeats(out a(so) seat_list);
      ListInhibitors(out a(ssssuu) inhibitor_list);
      CreateSession(in  u uid,
                    in  u pid,
                    in  s service,
                    in  s type,
                    in  s class,
                    in  s desktop,
                    in  s seat_id,
                    in  u vtnr,
                    in  s tty,
                    in  s display,
                    in  b remote,
                    in  s remote_user,
                    in  s remote_host,
                    in  a(sv) properties,
                    out s session_id,
                    out o object_path,
                    out s runtime_path,
                    out h fifo_fd,
                    out u uid,
                    out s seat_id,
                    out u vtnr,
                    out b existing);
      ReleaseSession(in  s session_id);
      ActivateSession(in  s session_id);
      ActivateSessionOnSeat(in  s session_id,
                            in  s seat_id);
      LockSession(in  s session_id);
      UnlockSession(in  s session_id);
      LockSessions();
      UnlockSessions();
      KillSession(in  s session_id,
                  in  s who,
                  in  i signo);
      KillUser(in  u uid,
               in  i signo);
      TerminateSession(in  s session_id);
      TerminateUser(in  u uid);
      TerminateSeat(in  s seat_id);
      SetUserLinger(in  u uid,
                    in  b linger,
                    in  b interactive);
      AttachDevice(in  s seat_id,
                   in  s sysfs,
                   in  b interactive);
      FlushDevices(in  b interactive);
[X]   PowerOff(in  b interactive);
[X]   Reboot(in  b interactive);
[X]   Suspend(in  b interactive);
[X]   Hibernate(in  b interactive);
[X]   HybridSleep(in  b interactive);
[X]   CanPowerOff(out s result);
[X]   CanReboot(out s result);
[X]   CanSuspend(out s result);
[X]   CanHibernate(out s result);
[X]   CanHybridSleep(out s result);
      ScheduleShutdown(in  s type,
                       in  t usec);
      CancelScheduledShutdown(out b cancelled);
[*]   Inhibit(in  s what,
              in  s who,
              in  s why,
              in  s mode,
              out h pipe_fd);
      CanRebootToFirmwareSetup(out s result);
      SetRebootToFirmwareSetup(in  b enable);
      SetWallMessage(in  s wall_message,
                     in  b enable);
*/
};

#endif // MANAGER_H
