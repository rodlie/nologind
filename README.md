# nologind

A fake org.freedesktop.login1 service for use on Slackware. Work-in-progress!

```
git clone https://github.com/rodlie/nologind
cd nologind
sudo ./nologind.SlackBuild
sudo upgradepkg --install-new /tmp/nologind-VERSION.tgz
```

**WARNING!!!** Any application (and probably KDE/Xfce) in Slackware that checks for logind vs. ConsoleKit will probably **BREAK**. nologind was made to see if it was possible to fake logind to get Skype [working](https://www.linuxquestions.org/questions/slackware-14/so-no-more-working-skype-for-slackware-15-the-older-versions-crash-because-the-new-glibc-the-newer-ones-needs-systemd-logind-4175638990/) (it was), anything else is untested.
