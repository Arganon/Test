#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    QString path = "C:/";
    model = new QFileSystemModel(this);
    model->setRootPath(path);
    model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::AllEntries);
    model->setReadOnly(false);

    ui->treeView->setModel(model);
    ui->treeView_2->setModel(model);
    ui->treeView->setSortingEnabled(true);
    ui->treeView_2->setSortingEnabled(true);

    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
    ui->treeView_2->hideColumn(1);
    ui->treeView_2->hideColumn(2);
    ui->treeView_2->hideColumn(3);
}

MainWindow::~MainWindow() {
    delete ui;
    delete model;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index) {
    resource_path = model->fileInfo(index).absoluteFilePath();
    index_resource = ui->treeView->currentIndex();
    index_destination = ui->treeView_2->currentIndex();
    destination_path = model->fileInfo(index_destination).absoluteFilePath();
}

void MainWindow::on_treeView_2_clicked(const QModelIndex &index) {
    resource_path = model->fileInfo(index).absoluteFilePath();
    index_resource = ui->treeView_2->currentIndex();
    index_destination = ui->treeView->currentIndex();
    destination_path = model->fileInfo(index_destination).absoluteFilePath();
}

// move file
void MainWindow::on_pushButton_clicked() {
    QString filename_resource;
    validations(filename_resource);
    ifFileExistInDestFolder(filename_resource);
    moveOrCopyFile(destination_path + "/" + filename_resource, false);
}
//copy file
void MainWindow::on_pushButton_2_clicked() {
    QString filename_resource;
    validations(filename_resource);
    ifFileExistInDestFolder(filename_resource);
    moveOrCopyFile(destination_path + "/" + filename_resource, true);
}
//delete file
void MainWindow::on_pushButton_3_clicked()
{
    if(!index_resource.isValid()) {
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Warning", "Do you want delete this object?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if (model->fileInfo(index_resource).isDir()) {
            QDir dir(model->fileInfo(index_resource).absoluteFilePath());
            dir.removeRecursively();
        } else {
            model->remove(index_resource);
        }
    }
}
//checkin file
void MainWindow::validations(QString &filename_resource) {
    if (!index_resource.isValid()) {
        return;
    }
    if (model->fileInfo(index_resource).isDir()) { //if we choosen dir - do nothing. Because we copy only file, not dir
        return;
    }
    if (model->fileInfo(index_destination).isFile()) {
        destination_path = model->fileInfo(index_destination).absolutePath();
    }
    if (model->fileInfo(index_resource).isFile()) {
        filename_resource = model->fileInfo(index_resource).fileName();
    }
}

void MainWindow::ifFileExistInDestFolder(QString &filename_resource) {
    if (!index_destination.isValid()) { // if we do not choosen dest folder - do nothing
        return;
    }
    if (QFileInfo::exists(destination_path + "/" + filename_resource)) {
        if (resource_path == (destination_path + "/" + filename_resource)) {
            return;
        }
        QMessageBox msgBox;
        msgBox.setText("Destiny folder has file with the same name");

        QPushButton *rename = msgBox.addButton(tr("Rename"), QMessageBox::ActionRole);
        QPushButton *overwrite = msgBox.addButton(tr("Overwrite"), QMessageBox::ActionRole);
        QPushButton *cancel = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);
        msgBox.exec();

        if (msgBox.clickedButton() == rename) {
            QString newFileName = filename_resource;
            while(filename_resource == newFileName) {
                newFileName = QInputDialog::getText(
                              this,
                              tr("String"),
                              tr("Enter a new filename with extension:"),
                              QLineEdit::Normal,
                              tr(qPrintable(filename_resource)));
            }
            filename_resource = newFileName;
        }
        if (msgBox.clickedButton() == overwrite) {
            QFile::remove(destination_path + "/" + filename_resource);
        }
        if (msgBox.clickedButton() == cancel) {
            return;
        }
    }
}

void MainWindow::moveOrCopyFile(QString dest, boolean isCopy) {
    if (!isCopy) {
        QFile::rename(resource_path, dest);
    } else {
        QFile::copy(resource_path, dest);
    }
}
