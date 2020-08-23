#include "edit.h"
#include "ui_edit.h"
#include "mainwindow.h"

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
#include <QProcess>
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

int max(int x, int y)
{
    return x > y ? x : y;
}

Edit::Edit(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::Edit)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(),this->height());

    cid = id;
    prepareinit();
}

Edit::~Edit()
{
    delete ui;
}

inline void Edit::prepareinit()
{
    const QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
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

    //因为是预先定义好的JSON数据格式，所以这里可以这样读取
    if(rootObj.contains("documents"))
    {
        QJsonArray doc = rootObj.value("documents").toArray();
        QJsonArray tit = rootObj.value("title").toArray();
        QJsonArray date = rootObj.value("date").toArray();
        QJsonArray url = rootObj.value("url").toArray();
        QJsonArray dis = rootObj.value("display").toArray();
        QString str = "";
        int i = cid - 1;
        this->ui->url->setText(url.at(i).toString());
        this->ui->date->setText(date.at(i).toString());
        this->ui->title->setText(tit.at(i).toString());
        this->ui->dis->setChecked(dis.at(i).toBool());
        QString file = home+"/.config/qloveblog/config/"+QString::number(cid)+".md";
//                QMessageBox::information(NULL, "", file, QMessageBox::Ok);
        QFile pgf(file);
        if (!pgf.open(QIODevice::ReadOnly))
        {
            qDebug() << "Open "+file+" Error!";
        }
        int line = 1;
        QString pgs = "";
        while(!pgf.atEnd()){
            char buffer[1024];
            qint64 length = pgf.readLine(buffer,1024);
            if(length != -1){
                line++;
                pgs += buffer;
                pgs += "\n";
            }
        }
        pgf.close();

        this->ui->pg->setText(pgs);
    }
}

void Edit::on_save_clicked()
{
    QString surl = ui->url->text().trimmed();
    QString spgs = ui->pg->toPlainText().trimmed();
    QString stit = ui->title->text().trimmed();
    QString sdate = ui->date->text().trimmed();
    bool sdis = ui->dis->checkState();
//    QMessageBox::information(NULL, "", QString::number(cid), QMessageBox::No);

    const QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
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
    QVariantHash newdata;
    if(rootObj.contains("documents"))
    {
        QJsonArray doc = rootObj.value("documents").toArray();
        QJsonArray tit = rootObj.value("title").toArray();
        QJsonArray date = rootObj.value("date").toArray();
        QJsonArray url = rootObj.value("url").toArray();
        QJsonArray dis = rootObj.value("display").toArray();
        QJsonArray ndoc, ntit, ndate, nurl, ndis;
        for (int i = 0; i < max(cid, doc.size()); i ++)
        {
            if (i + 1 == cid)
            {
                ndoc.insert(i, i + 1);
                ntit.insert(i, stit);
                ndate.insert(i, sdate);
                nurl.insert(i, surl);
                ndis.insert(i, sdis);
            }
            else
            {
                ndoc.insert(i, i + 1);
                ntit.insert(i, tit.at(i).toString());
                ndate.insert(i, date.at(i).toString());
                nurl.insert(i, url.at(i).toString());
                ndis.insert(i, dis.at(i).toBool());
            }
        }
        newdata.insert("documents", ndoc);
        newdata.insert("title", ntit);
        newdata.insert("display",ndis);
        newdata.insert("date", ndate);
        newdata.insert("url", nurl);
    }

    QJsonObject newobj = QJsonObject::fromVariantHash(newdata);
    QJsonDocument document;
    document.setObject(newobj);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    QFile file(fileloc);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug() << "file error!";
    }
    QTextStream in(&file);
    in << json_str;
    file.close();
//    QMessageBox::information(NULL, "", json_str, QMessageBox::Ok);
//    QMessageBox::information(NULL, "", QString::number(cid), QMessageBox::Ok);
    QString tfile = home+"/.config/qloveblog/config/"+QString::number(cid)+".md";
    QFile gfile(tfile);
    if(!gfile.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug() << "file error!";
    }
    QTextStream in2(&gfile);
    in2 << spgs;
    gfile.close();
//    QMessageBox::information(NULL, "", tfile, QMessageBox::Ok);
    prepareinit();
}

void Edit::on_delete_2_clicked()
{
    string x = "rm -rf ~/.config/qloveblog/config/"+to_string(cid)+".md";
    getshell(x);
    const QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
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
    QVariantHash newdata;
    if(rootObj.contains("documents"))
    {
        QJsonArray doc = rootObj.value("documents").toArray();
        QJsonArray tit = rootObj.value("title").toArray();
        QJsonArray date = rootObj.value("date").toArray();
        QJsonArray url = rootObj.value("url").toArray();
        QJsonArray dis = rootObj.value("display").toArray();
        QJsonArray ndoc, ntit, ndate, nurl, ndis;
        for (int i = 0; i < cid - 1; i ++)
        {
            ndoc.insert(i, i + 1);
            ntit.insert(i, tit.at(i).toString());
            ndate.insert(i, date.at(i).toString());
            nurl.insert(i, url.at(i).toString());
            ndis.insert(i, dis.at(i).toBool());
        }
        newdata.insert("documents", ndoc);
        newdata.insert("title", ntit);
        newdata.insert("display",ndis);
        newdata.insert("date", ndate);
        newdata.insert("url", nurl);
    }

    QJsonObject newobj = QJsonObject::fromVariantHash(newdata);
    QJsonDocument document;
    document.setObject(newobj);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    QFile file(fileloc);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug() << "file error!";
    }
    QTextStream in(&file);
    in << json_str;
    file.close();
//    QMessageBox::information(NULL, "", json_str, QMessageBox::Ok);
//    QMessageBox::information(NULL, "", QString::number(cid), QMessageBox::Ok);
    this->hide();
}

void Edit::on_back_clicked()
{
    this->hide();
}
