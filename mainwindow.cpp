#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "edit.h"

#include <QProcess>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QByteArray>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTimer>
#include <QtGlobal>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

#ifdef Q_OS_WIN
    #include <windows.h>
#endif

inline string getshell(string cmd)
{
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream)
    {
        while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    return data;
}


inline QString run_command (QString strCmd)
{
    QProcess p;
    p.start("bash", QStringList() <<"-c" << strCmd);
    p.waitForFinished();
    QString strResult = p.readAllStandardOutput();
    return strResult;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(),this->height());

    article_fetch();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_settinSave_clicked()
{
    Settings *setting = new Settings(this);
    setting->setFixedSize(setting->width(), setting->height());
    setting->show();
}

void MainWindow::article_fetch()
{
    ui->choose->clear();
    const QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
//    QMessageBox::information(NULL, "", home, QMessageBox::Yes);
    QString fileloc = home + "/.config/qloveblog/config/config.json";
    QFile loadFile(fileloc);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }
    QByteArray allData = loadFile.readAll();
    loadFile.close();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
        return;
    }
    QJsonObject rootObj = jsonDoc.object();

    QStringList keys = rootObj.keys();
//    for(int i = 0; i < keys.size(); i++)
//    {
//        qDebug() << "key" << i << " is:" << keys.at(i);
//    }
    if(rootObj.contains("documents"))
    {
        QJsonArray doc = rootObj.value("documents").toArray();
        QJsonArray tit = rootObj.value("title").toArray();
        QJsonArray date = rootObj.value("date").toArray();
        QString str = "";
        int i;
        for (i = 0; i < doc.size(); i++)
        {
            str+=QString::number(doc.at(i).toInt());
            str+=" : ";
            str+=tit.at(i).toString();
            str+="\n";
            QString t1 = tit.at(i).toString();
            QByteArray ba = t1.toLocal8Bit();
            const char *t = ba.data();
            ui->choose->addItem(QString::asprintf(t,doc.at(i).toInt()));
        }
        const char st[1000] = "New Article";
        this->ui->choose->addItem(QString::asprintf(st, i));
//        QMessageBox::information(NULL, "", QString::number(i), QMessageBox::Ok);
        this->ui->article_show->setText(str);
    }
    else
    {
        this->ui->article_show->setText("Error: Cannot load Config.json in here");
    }
}

void MainWindow::on_fetch_article_clicked()
{
    article_fetch();
}

void MainWindow::on_goedit_clicked()
{
    int num = this->ui->choose->currentIndex();
    num ++;
    Edit *edit = new Edit(this, num);
    edit->setFixedSize(edit->width(), edit->height());
    edit->cid = num;
//    edit->prepareinit();
    //QMessageBox::information(NULL, "", QString::number(edit->cid), QMessageBox::No);
    edit->show();
}

inline string q2s(const QString &s)
{
    return string((const char *)s.toLocal8Bit());
}
inline QString s2q(const string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

void MainWindow::on_publish_clicked()
{
    QMessageBox::information(NULL, "QLoveBlog", "Your Blog is publishing...", QMessageBox::Ok);
    const QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
//    QMessageBox::information(NULL, "", home, QMessageBox::Yes);
    QString fileloc = home + "/.config/qloveblog/config/config.json";
    QFile loadFile(fileloc);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could't open projects json";
        return;
    }
    QByteArray allData = loadFile.readAll();
    loadFile.close();
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!";
        return;
    }
    QJsonObject rootObj = jsonDoc.object();

    QStringList keys = rootObj.keys();
//    for(int i = 0; i < keys.size(); i++)
//    {
//        qDebug() << "key" << i << " is:" << keys.at(i);
//    }
    if(rootObj.contains("documents"))
    {
        QJsonArray doc = rootObj.value("documents").toArray();
        QJsonArray tit = rootObj.value("title").toArray();
        QJsonArray date = rootObj.value("date").toArray();
        QJsonArray url = rootObj.value("url").toArray();
        QJsonArray dis = rootObj.value("display").toArray();
        int i;
        QString index = "";
        getshell("rm -rf ~/.config/qloveblog/output/*.md");
        for (i = 0; i < doc.size(); i++)
        {
            if (dis.at(i).toBool())
            {
                index += "[**"+tit.at(i).toString()+"**]("+url.at(i).toString()+")\n\nCreat in **"+date.at(i).toString()+"** with url **"+url.at(i).toString()+"**\n\n---\n\n";
                QString dos = "cp ~/.config/qloveblog/config/"+QString::number(doc.at(i).toInt())+".md ~/.config/qloveblog/output/"+url.at(i).toString()+".md";
                getshell(q2s(dos));
            }
        }
        index += "This site is powered by [QLoveBlog](https://github.com/loveblog/qloveblog).\n";
        QString indexfile = home+"/.config/qloveblog/output/index.md";
        QFile file(indexfile);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug() << "file error!";
        }
        QTextStream in(&file);
        in << index;
        file.close();
        string res = getshell("cd ~/.config/qloveblog/output ; git pull ; git add -A ; git commit -m \"LanGong QLoveBlog Push\" ; git push");
        QMessageBox::information(NULL, "QLoveBlog", "Your Blog is published!\n\n"+s2q(res), QMessageBox::Ok);
    }
}
