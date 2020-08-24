# LanGong QLoveBlog

Loveblog with QT.

# Install

## Application needs

- Qt5 : Download Qt5
- git : 
  - Linux :
    - Arch/Arco/Manjaro : `# pacman -S git`
    - Debian/Ubuntu : `# apt install git`
    - Redhat/Fedora/CentOS : `# yum install git`
  - MacOS : Install on git-scm.com
  - Windows : Not service for windows.

## Install QLB

```lansh
$ git clone https://github.com/loveblog/qloveblog.git
$ cd qloveblog
# bash install.sh
```

## Enhanced plug-ins

- For `ssh` : `x11-ssh-askpass`
  - Linux:
    - Arch/Arco/Manjaro : `# pacman -S x11-ssh-askpass`
    - Debian/Ubuntu : `# apt install x11-ssh-askpass`
    - Redhat/Fedora/CentOS : `# yum install x11-ssh-askpass`
  - MacOS: Maybe `$ brew install x11-ssh-askpass`
  - Windows: Not service for windows.
- For

# Usage

## Start app

- Start with terminal.

```lansh
$ qloveblog
```

- Start with Applications Menu `QLoveBlog`

## Set up repo

### Make blog with GitHub

- Creat a user on GitHub
- Creat a repo and named `username.github.io`

### Make blog with your server

- Creat a git repo on your server

### Then you have to do with client

- Start app and click `repo settings`

![1](http://victorwoo.synology.me:516/img/qlb1.png)

- Fill form from the dialog and click `save`

![2](http://victorwoo.synology.me:516/img/qlb2.png)

> NOTICE:
> 
> You cannot input `ssh://`, `https://` or `http://` in input box `git repo` on the dialog!!!
> 

# Uninstall

```lansh
# bash /usr/share/qloveblog/uninstall.sh
```
