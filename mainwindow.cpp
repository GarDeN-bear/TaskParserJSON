#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->search->setEnabled(loadData);
    ui->lineEdit->setEnabled(loadData);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadData_clicked()
{
    QFile file;
    globPath = QFileDialog::getOpenFileName(nullptr, "", "../TaskParser", "*.json");
    file.setFileName(globPath);
    if (file.open(QIODevice::ReadOnly|QFile::Text))
    {
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
        QMessageBox::information(nullptr, "Data information", "Data has been loaded successfully!");
        loadData = true;
        ui->lineEdit->setEnabled(loadData);
        ui->search->setEnabled(loadData);
    }
    file.close();
    if(docError.errorString().toInt() == QJsonParseError::NoError)
    {
        QStandardItemModel* model = new QStandardItemModel(nullptr);
        model->setHorizontalHeaderLabels(QStringList() << "coords" << "district" << "name" << "population" << "subject");
//        QJsonArray jsonArr = doc.array();
//        for(int i = 0; i < 3; ++i)
//        {
//            QString itemCol1_1 = jsonArr.at(i).toObject().value("coords").toObject().value("lat").toString();
//            QString itemCol1_2 = jsonArr.at(i).toObject().value("coords").toObject().value("lon").toString();
//            QStandardItem* itemCol1 = new QStandardItem("lat: " + itemCol1_1 + "; lon: " + itemCol1_2);
//            QStandardItem* itemCol2 = new QStandardItem(jsonArr.at(i).toObject().value("district").toString());
//            QStandardItem* itemCol3 = new QStandardItem(jsonArr.at(i).toObject().value("name").toString());
//            QStandardItem* itemCol4 = new QStandardItem(QString::number(jsonArr.at(i).toObject().value("population").toInt()));
//            QStandardItem* itemCol5 = new QStandardItem(jsonArr.at(i).toObject().value("subject").toString());
//            model->appendRow(QList<QStandardItem*>() << itemCol1<< itemCol2<< itemCol3<< itemCol4<< itemCol5);
//        }
        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}


void MainWindow::on_search_clicked()
{
}

