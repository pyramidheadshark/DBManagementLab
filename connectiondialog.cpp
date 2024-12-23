#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include <QMessageBox>
#include <QSqlError>

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName(ui->lineEdit->text());
    db.setDatabaseName(ui->lineEdit_2->text());
    db.setUserName(ui->lineEdit_3->text());
    db.setPassword(ui->lineEdit_4->text());
    db.setPort(5432); // Устанавливаем порт по умолчанию

    QMessageBox *msg = new QMessageBox();

    if (db.open())
     {
         msg->setText("Соединение установлено");
     }
     else
     {
        msg->setText("Соединение НЕ установлено: " + db.lastError().text());
     }
    msg->show();
    QTimer::singleShot(2000, msg, &QMessageBox::close); // Закрываем окно через 2 секунды
}