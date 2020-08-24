#/bin/bash

echo " :: Uninstalling QLB..."
echo " >> Delete bin"
rm -f /usr/bin/qloveblog
echo " >> Delete Dir"
rm -r /usr/share/qloveblog
echo " >> Delete Desktop"
rm -r /usr/share/applications/qloveblog.desktop

echo " :: Uninstalled QLB"

