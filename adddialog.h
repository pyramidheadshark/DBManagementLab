#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QWidget>

namespace Ui {
class AddDialog;
}

class AddDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddDialog *ui;
    int cat_ID;
};

#endif // ADDDIALOG_H
