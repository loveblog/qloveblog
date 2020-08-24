#!/bin/bash

echo " :: Checking system..."
qmake --version || (echo " >> Install qmake first!!!" && exit 1)
make --version || (echo " >> Install make first!!!" && exit 1)
git --version || (echo " >> Install git first!!!" && exit 1)
ssh --version || (echo " >> Install ssh first!!!" && exit 1)

echo " :: Starting install QLB..."
echo " >> Compile"
echo "    => Qt5 Make"
qmake QLoveBlog.pro

echo "    => Make"
make

echo " >> Install"
echo "    => Copy bin"
cp ./QLoveblog /usr/bin/qloveblog
echo "    => Copy Desktop file"
cp ./qloveblog.desktop /usr/share/applications
echo "    => Copy dir"
mkdir -p /usr/share/qloveblog
cp -r ./* /usr/share/qloveblog

echo " >> Change mode"
chmod 755 /usr/share/applications/qloveblog.desktop

echo " :: Finish"
