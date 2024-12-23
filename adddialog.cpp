#include "adddialog.h"
#include "ui_adddialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

AddDialog::AddDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

// Обработчик для кнопки добавления данных
void AddDialog::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO product VALUES (:name, :cat_ID)");
    query.bindValue(":name", ui->lineEdit_2->text());
    query.bindValue(":cat_ID", ui->lineEdit->text());
    query.exec();
    close(); // Закрытие диалогового окна
}
