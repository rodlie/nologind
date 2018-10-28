# nologind

A logind wrapper for ConsoleKit(2) on Slackware. Used as a compatibility layer for applications that require (parts of) the org.freedesktop.login1.Manager D-Bus system service.

**WARNING!!!** This is experimental software and may break applications, login managers and desktop environments, **only a pure Slackware 14.2 installation is supported.** If something breaks let me know (and ``killall nologind && removepkg nologind`` to revert to default).

## Implemented

org.freedesktop.login1.Manager:

 * PreparingForShutdown
 * PreparingForSleep
 * Docked
 * PrepareForShutdown
 * PrepareForSleep
 * PowerOff
 * Reboot
 * Suspend
 * Hibernate
 * HybridSleep
 * CanPowerOff
 * CanReboot
 * CanSuspend
 * CanHibernate
 * CanHybridSleep
 * Inhibit (does nothing, see issue #2)
