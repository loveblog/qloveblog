# LanGong QLoveBlog

Loveblog with QT.

# Install 安装

## Application needs 应用程序依赖

- Qt5 : Download Qt5 下载 QT5
- git : 
  - Linux :
    - Arch/Arco/Manjaro : `# pacman -S git`
    - Debian/Ubuntu : `# apt install git`
    - Redhat/Fedora/CentOS : `# yum install git`
  - MacOS : Install on git-scm.com
  - Windows : Not service for windows.

## Install QLB 安装QLB

```lansh
$ git clone https://github.com/loveblog/qloveblog.git
$ cd qloveblog
# bash install.sh
```

## Enhanced plug-ins 安装增强插件

- For `ssh` : `x11-ssh-askpass` (If you want to use ssh-git in QLB)
  - Linux:
    - Arch/Arco/Manjaro : `# pacman -S x11-ssh-askpass`
    - Debian/Ubuntu : `# apt install x11-ssh-askpass`
    - Redhat/Fedora/CentOS : `# yum install x11-ssh-askpass`
  - MacOS: Maybe `$ brew install x11-ssh-askpass`
  - Windows: Not service for windows.
- For

# Usage 使用

## Start app 启动程序

- Start with terminal. 使用命令行启动

```lansh
$ qloveblog
```

- Start with Applications Menu `QLoveBlog`

## Set up repo 初始化 Repo

### Make blog with GitHub 使用 GitHub 创建博客

- Creat a user on GitHub
- Creat a repo and named `username.github.io`

### Make blog with your server 使用自己的服务器创建博客

- Creat a git repo on your server
- Install `Jekyll` https://jekyllrb.com/

### Then you have to do with client 然后启动客户端

- Start app and click `repo settings`

![1](http://victorwoo.synology.me:516/img/qlb1.png)

- Fill form from the dialog and click `save`

![2](http://victorwoo.synology.me:516/img/qlb2.png)

> Warning:
> 
> You cannot input `ssh://`, `https://` or `http://` in input box `git repo` on the dialog!!!
> 
> We can parse them in version 1.0.2 上述警告可以在 1.0.2 中被解析，所以您不用担心。
> 

# Uninstall

```lansh
# bash /usr/share/qloveblog/uninstall.sh
```

# Beautify

Edit File `~/.config/qloveblog/output/_config.yml`

- theme: _THEME_ (GitHub Theme or https://jekyllthemes.io/)
- title: "_TITLE_" (Blog Title)
- description: "_DESCRIPTION_" (Blog Description)
- ... (This site will help you https://jekyllrb.com/docs/configuration/)

Like:

```yaml
theme: jekyll-theme-cayman
title: "Love Blog Show"
description: "My Love Blog"
```
