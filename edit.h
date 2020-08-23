#ifndef EDIT_H
#define EDIT_H

#include <QDialog>

namespace Ui {
class Edit;
}

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(QWidget *parent = nullptr, int id = -1);
    ~Edit();

    int cid;
    inline void prepareinit();

private slots:
    void on_save_clicked();

    void on_delete_2_clicked();

    void on_back_clicked();

private:
    Ui::Edit *ui;
};

#endif // EDIT_H
