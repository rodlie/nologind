# nologind

A fake org.freedesktop.login1 service for use on Slackware. Work-in-progress!

```
git clone https://github.com/rodlie/nologind
cd nologind
sudo ./nologind.SlackBuild
sudo upgradepkg --install-new /tmp/nologind-VERSION.tgz
```

**WARNING!!!** Any application (DE) in Slackware that checks for logind/ConsoleKit will probably **BREAK**. This software was made to test if it was possible to fake logind to get Skype working (it was). So consider yourself warned.
