#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject> // for working with JSON files
#include <QJsonParseError> // for checking JSON errors
#include <QFile> // for working with files
#include <QFileDialog> // for touching the neccessary file from any directory
#include <QStandardItem> // for forming cells in a table
#include <QJsonArray> // for working with JSON arrays
#include <QDebug> // for debugging code
#include <QMessageBox> // for using message box
#include <QKeyEvent> // for using hot keys
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool loadData = false;
    QJsonDocument doc;
    QJsonParseError docError;
    QString globPath;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadData_clicked();

    void on_search_clicked();

    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
