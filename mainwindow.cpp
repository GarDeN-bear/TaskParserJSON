#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->search->setEnabled(loadData);
    ui->lineEdit->setEnabled(loadData);
    ui->lineEdit->setPlaceholderText("Input city name");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadData_clicked()
{
    QFile file;
    globPath = QFileDialog::getOpenFileName(nullptr, "", "..", "*.json");
    file.setFileName(globPath);
    if (file.open(QIODevice::ReadOnly|QFile::Text))
    {
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
        loadData = true;
        ui->lineEdit->setEnabled(loadData);
        ui->search->setEnabled(loadData);
    }
    file.close();
    if(docError.errorString().toInt() == QJsonParseError::NoError)
    {
        QStandardItemModel* model = new QStandardItemModel(nullptr);
//        model->setHorizontalHeaderLabels(QStringList() << "coords" << "district" << "name" << "population" << "subject");
        model->setHorizontalHeaderLabels(QStringList() << "Название города" << "Регион" << "Население");
        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}


void MainWindow::on_search_clicked()
{
    QRegExp regExpCyrillic("[а-яА-Я-]+");
    QString searchString = ui->lineEdit->text();
    QJsonArray jsonArr = doc.array();
    QStandardItemModel* model = new QStandardItemModel(nullptr);
    model->setHorizontalHeaderLabels(QStringList() << "Название города" << "Регион" << "Население");
//    model->setHorizontalHeaderLabels(QStringList() << "coords" << "district" << "name" << "population" << "subject");
    bool foundName = false;
    for(int i = 0; i < jsonArr.size(); ++i)
    {
        if (!regExpCyrillic.exactMatch(searchString))
        {
            break;
        }
        else if(jsonArr.at(i).toObject().value("name").toString().toUpper().indexOf(searchString.toUpper()) == 0){
//            QString itemCol1_1 = jsonArr.at(i).toObject().value("coords").toObject().value("lat").toString();
//            QString itemCol1_2 = jsonArr.at(i).toObject().value("coords").toObject().value("lon").toString();
//            QStandardItem* itemCol1 = new QStandardItem("lat: " + itemCol1_1 + ";\nlon: " + itemCol1_2);
//            QStandardItem* itemCol2 = new QStandardItem(jsonArr.at(i).toObject().value("district").toString());
//            QStandardItem* itemCol3 = new QStandardItem(jsonArr.at(i).toObject().value("name").toString());
//            QStandardItem* itemCol4 = new QStandardItem(QString::number(jsonArr.at(i).toObject().value("population").toInt()));
//            QStandardItem* itemCol5 = new QStandardItem(jsonArr.at(i).toObject().value("subject").toString());
//            model->appendRow(QList<QStandardItem*>() << itemCol1<< itemCol2<< itemCol3<< itemCol4<< itemCol5);
            QStandardItem* itemCol1 = new QStandardItem(jsonArr.at(i).toObject().value("name").toString());
            QStandardItem* itemCol2 = new QStandardItem(jsonArr.at(i).toObject().value("district").toString());
            QStandardItem* itemCol3 = new QStandardItem(QString::number(jsonArr.at(i).toObject().value("population").toInt()));
            model->appendRow(QList<QStandardItem*>() << itemCol1<< itemCol2<< itemCol3);
            foundName = true;
        }
    }
    if(!foundName)
    {
        QMessageBox::warning(this, "Warning", "No such city name!");
    }
    ui->tableView->setModel(model);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && loadData)
    {
        MainWindow::on_search_clicked();
    }
}

