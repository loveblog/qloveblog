#include "settings.h"
#include "ui_settings.h"

#include <QProcess>
#include <QtGlobal>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <QMessageBox>
using namespace std;

#ifdef Q_OS_WIN
    #include <windows.h>
#endif

inline QString run_command (QString strCmd)
{
    QProcess p;
    p.start("bash", QStringList() <<"-c" << strCmd);
    p.waitForFinished();
    QString strResult = p.readAllStandardOutput();
    return strResult;
}

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

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

inline string q2s(const QString &s)
{
    return string((const char *)s.toLocal8Bit());
}
inline QString s2q(const string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

void Settings::on_settinSave_clicked()
{
    QMessageBox::information(NULL, "Preparing", "Your repo is preparing...", QMessageBox::Yes);
    this->ui->setShow->setText("Please wait...\n");
    QString username = this->ui->username->text().trimmed();
    QString repo = this->ui->repo->text().trimmed();
    QString password = this->ui->password->text().trimmed();
    QString via = this->ui->via->text().trimmed();
    QString dostr = "mkdir -p ~/.config/qloveblog/output ; rm -rf ~/.config/qloveblog/output ; git clone "+via+"://"+username+":"+password+"@"+repo+" ~/.config/qloveblog/output";
    string sdostr = q2s(dostr);
    QString res = s2q(getshell(sdostr))+"\nYour Repo is prepared.";
//    system (dostr);
    this->ui->setShow->setText(res);
}

void Settings::on_pushButton_clicked()
{
    this->hide();
}
