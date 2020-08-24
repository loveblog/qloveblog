#include "mainwindow.h"

#include <QApplication>
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
#include <QDir>
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

int main(int argc, char *argv[])
{
    const QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString configdir = home+"/.config/qloveblog";
    QDir dir(configdir);
    if(!dir.exists())
    {
        getshell ("mkdir -p ~/.config/qloveblog/config ; echo '{\"date\":[],\"display\":[],\"documents\":[],\"title\":[],\"url\":[]}' > ~/.config/qloveblog/config/config.json");
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
