#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include "connectiondialog.h"
#include <QSqlQueryModel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tableView,
     SIGNAL(customContextMenuRequested(QPoint)),
     SLOT(CustomMenuReq(QPoint)));
    fl = 0; //установка начального значения

    // Инициализация модели для работы с SQL запросами
    qmodel = new QSqlQueryModel(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete qmodel;
}


void MainWindow::on_action_triggered()
{
    dlg = new ConnectionDialog();
    dlg->show();

}


void MainWindow::on_pushButton_clicked()
{
    fl=1;
    qmodel->setQuery("SELECT * FROM product");
    ui->tableView->setModel(qmodel);

}


void MainWindow::on_pushButton_2_clicked()
{
    AddDialog *add = new AddDialog();
    add->show();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int temp_ID;
        temp_ID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();

        QSqlQuery *query = new QSqlQuery();
        query->prepare("SELECT name, cat_ID, ImagePath FROM product WHERE ID = :ID");
        query->bindValue(":ID", temp_ID);

        ui->lineEdit->setText(QString::number(temp_ID));
        if (query->exec())
        {
            query->next();
            ui->lineEdit_2->setText(query->value(0).toString());
            ui->lineEdit_3->setText(query->value(1).toString());
            Img = query->value(2).toString();
            ui->label_4->setPixmap(Img);

        }
}


void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery *query = new QSqlQuery();
     query->prepare("DELETE FROM product WHERE ID = :ID");
     query->bindValue(":ID",ui->lineEdit->text());
     query->exec();
    //очищаем поля ввода
     ui->lineEdit->setText("");
     ui->lineEdit_2->setText("");
     ui->lineEdit_3->setText("");
    //вызов обраотчика кнопки «Удалить»
     MainWindow::on_pushButton_clicked();

}


void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery *query = new QSqlQuery();
     query->prepare("UPDATE product SET name = :name, cat_ID = :cat_ID, ImagePath = :image WHERE ID = :ID");
     query->bindValue(":ID",ui->lineEdit->text());
     query->bindValue(":name",ui->lineEdit_2->text());
     query->bindValue(":cat_ID",ui->lineEdit_3->text());
     query->bindValue(":image",Img);
     query->exec();
     ui->lineEdit->setText("");
     ui->lineEdit_2->setText("");
     ui->lineEdit_3->setText("");
     ui->label_4->setText("");

     MainWindow::on_pushButton_clicked();

}


void MainWindow::CustomMenuReq(QPoint pos)

{
    if (fl == 1)
    {
        QModelIndex index = ui->tableView->indexAt(pos);
        GlobID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
        //Создаём меню и два действия
        QMenu *menu = new QMenu(this);
        QAction *ModRec = new QAction("Изменить...", this);
        QAction *DelRec = new QAction("Удалить", this);
        //Соединяем действие с соответствующим сигналом и слотом

        //(который нужно создать позже)
        connect(ModRec, SIGNAL(triggered()), this, SLOT(ModRecAction()));
        connect(DelRec, SIGNAL(triggered()), this, SLOT(DelRecAction()));

        //Добавление действий, созданных ранее
        menu->addAction(ModRec);
        menu->addAction(DelRec);

        menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::DelRecAction()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM product WHERE ID = :ID");
    query->bindValue(":ID", GlobID);
    query->exec();
    MainWindow::on_pushButton_clicked();
}

void MainWindow::ModRecAction()
{
    mdlg = new ModifyDialog();
    connect(this,SIGNAL(sendID(int)),mdlg, SLOT(sendingID(int)));
    emit sendID(GlobID);
    mdlg->show();
    disconnect(this,SIGNAL(sendID(int)),mdlg,
    SLOT(sendingID(int)));
}


void MainWindow::on_pushButton_5_clicked()
{
    pdlg = new PrintDialog();
    pdlg->show();
}


void MainWindow::on_pushButton_6_clicked()
{
    QString str;
     str.append("<html><head></head><body><center>"
     +QString("Пример создания отчёта"));
     str.append("<table border=1><tr>");
     str.append("<td>"+QString("ID")+"</td>");
      str.append("<td>"+QString("Наименование")+"</td>");
      str.append("<td>"+QString("Категория")+"</td></tr>");
      QSqlQuery *query = new QSqlQuery();
      query->exec("SELECT * FROM product");
      query->next();
      while(query->next())
      {
      str.append("<tr>");
      str.append("<td>"
      +QString(query->value(0).toString())+"</td>");
      str.append("<td>"
      +QString(query->value(1).toString())+"</td>");
      str.append("<td>"
      +QString(query->value(2).toString())
      +"</td></tr>");
      }
      str.append("</table>");
      str.append("</center></body></html>");

      QPrinter printer;
       printer.setOrientation(QPrinter::Portrait);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setPaperSize(QPrinter::A4);

       QString path =
        QFileDialog::getSaveFileName(NULL,"Сохранить",
        "Отчёт","PDF(*.pdf)");
        if (path.isEmpty()) return;
        printer.setOutputFileName(path);
        QTextDocument doc;
         doc.setHtml(str);
         doc.print(&printer);

}


void MainWindow::on_toolButton_clicked()
{
    Img = QFileDialog::getOpenFileName(0, "Открыть файл",
     Img,"*.jpg");
     ui->label_4->setPixmap(Img);
}

