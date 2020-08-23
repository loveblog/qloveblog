#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_settinSave_clicked();

    void on_pushButton_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
