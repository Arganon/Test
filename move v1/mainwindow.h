#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTCore>
#include <QtGui>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QFileInfo>
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_treeView_2_clicked(const QModelIndex &index);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    QString resource_path;
    QString destination_path;
    QModelIndex index_resource;
    QModelIndex index_destination;
    QString left_tree_viev;
    QString right_tree_viev;

    void validations(QString &filename_resource);
    void ifFileExistInDestFolder(QString &filename_resource);

    void moveOrCopyFile(QString dest, boolean isCopy);

};

#endif // MAINWINDOW_H
