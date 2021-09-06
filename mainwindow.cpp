#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //set the textEdit box to be the central widget
    this->setCentralWidget(ui->textEdit);
    //set the window title
    this->setWindowTitle("Notepad 1.0");
    //the filename is initially empty
    file_path = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    //the new file function will just reset the text file to a initial state
    file_path = "";
    ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_triggered()
{
    //Get the open file name
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
    //open the file
    QFile file(file_name);
    //set the file name to the opened file name
    file_path = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "file cannot be opened");
        return;
    }
    //pass the opened Qfile object to a QtextStream obj
    QTextStream in(&file);
    //read all the text
    QString text = in.readAll();
    //set the text to the text edit box
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    //if the file name is NULL, we must use saved as option
    if(file_path == "")
    {
        on_actionSave_as_triggered();
        return;
    }

    //open the Qfile object with the current file name
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "file cannot be saved");
        return;
    }
    //Create a QtextStream object and pass the Qfile obj to the new stream obj
    QTextStream out(&file);
    //get all the text in the text edit box
    QString text = ui->textEdit->toPlainText();
    //send all the text to the out textStream obj
    out << text;
    //flush the file and close
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    //same as save funtion, the only thing that is different is that we need to
    //open a file dialog and get the file name entered by the user.
    QString file_name = QFileDialog::getSaveFileName(this, "Open the file");

    //everything below is the same as save
    QFile file(file_name);
    // we need to set the newly filename in order for save to work properly
    file_path = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Error", "file cannot be saved");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionAbout_triggered()
{
    QString info = "Author: Xiaohu Zheng\n";
    info += "Date: 9/6/2021\n";
    info += "Version: 1.0";
    info += "(C) Notepad (R)\n";

    QMessageBox::about(this, "About", info);
}
