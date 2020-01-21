#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEditor);//the text editor will take the full screen.(this is the widget that will take the full screen)
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEditor->setText(QString());//clear the text editor
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/myText",tr("Text file (*.txt)"));
    QFile file(fileName);
    currentFile = fileName;

    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot Open File: "+ file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);//interface for reading text
    QString text = in.readAll();
    ui->textEditor->setText(text);
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
     QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"/myText",tr("Text file (*.txt)"));
     QFile file(fileName);
     if(!file.open(QFile::WriteOnly | QFile::Text))
     {
         QMessageBox::warning(this, "Warning", "Cannot Save File: "+ file.errorString());
         return;
     }
     currentFile = fileName;
     setWindowTitle(fileName);
     QTextStream out(&file);
     QString text = ui->textEditor->toPlainText();
     out<<text;
     file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEditor->cut();
}

void MainWindow::on_actionCopy_triggered()
{
     ui->textEditor->copy();
}

void MainWindow::on_actionPaste_triggered()
{
   ui->textEditor->paste();
}

void MainWindow::on_actionUndo_triggered()
{
     ui->textEditor->undo();
}

void MainWindow::on_actionRedo_triggered()
{
     ui->textEditor->redo();
}

void MainWindow::on_actionPrint_triggered()
{
    // Allows for interacting with printer
      QPrinter printer;

      //Put printer name here
      printer.setPrinterName("Printer Name");

      // Create the print dialog and pass the name and parent
      QPrintDialog pDialog(&printer, this);

      if(pDialog.exec() == QDialog::Rejected){
          QMessageBox::warning(this, "Warning", "Cannot Access Printer");
          return;
      }

      // Send the text to the printer
      ui->textEditor->print(&printer);
}
