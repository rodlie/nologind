# nologind

A org.freedesktop.login1 service that acts as a wrapper for ConsoleKit on Slackware.

```
git clone https://github.com/rodlie/nologind
cd nologind
```
```
git pull
sudo ./nologind.SlackBuild
sudo upgradepkg --install-new /tmp/nologind-VERSION.tgz
```

**WARNING!!!** Any application, login manager and desktop environment in Slackware that checks for logind vs. ConsoleKit will probably **BREAK**

nologind was made to see if it was possible to fake logind to get Skype [working](https://www.linuxquestions.org/questions/slackware-14/so-no-more-working-skype-for-slackware-15-the-older-versions-crash-because-the-new-glibc-the-newer-ones-needs-systemd-logind-4175638990/) on Slackware (it was).

## Implemented

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
 * Inhibit (does not do anything yet, see issue #2)

## Roadmap

* Fix power managers
* Fix desktop environments (KDE/Xfce)
* Fix login managers
* Fix whatever is left that is broken
