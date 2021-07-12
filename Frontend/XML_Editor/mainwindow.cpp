#include "mainwindow.h"
#include "ui_mainwindow.h"


int currentFile = 0;
QVector<QString> files;
QVector<QString> fileEdits;
syntaxHighlighter * highlighter;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    highlighter = new syntaxHighlighter(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete highlighter;
}


QString markErrors(QVector<int> errors, QString in){
    for(int i=0; i<errors.size(); i++){
        in.insert(errors[i]-3, "!Error <--");
        int j = errors[i];
        while(1){
            j++;
            if(in[j] == ">"){
                break;
            }
        }
        in.insert(j+1, "  -->");
    }
    return in;

}


void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("XML files (*.xml)"));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Error", file.errorString());
    }
    else {
        // Open file in text editor
        QString txt = file.readAll();
        ui->textEdit->setText(txt);
        files.push_back(ui->textEdit->toPlainText());
        fileEdits.push_back(ui->textEdit->toPlainText());
        currentFile = files.size()-1;
        ui->savedLabel->setText("Saved");
        ui->savedLabel->setStyleSheet("QLabel { color : green; }");

        // Add file to table
        QTableWidget * table = ui->tableWidget;
        int rowCount = table->rowCount();
        table->insertRow(rowCount);
        table->setItem(rowCount,0, new QTableWidgetItem(fileName));
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // Add Exit Button
        table->setItem(rowCount,1, new QTableWidgetItem("Close File"));
        table->item(rowCount,1)->setForeground(QBrush(QColor(255, 0, 0)));

        QVector<int> test;
        test.push_back(11);
        QString testStr = markErrors(test, ui->textEdit->toPlainText());
        ui->textEdit->setText(testStr);




    }
}


void MainWindow::on_textEdit_textChanged()
{


    if(files.size() != 0 && currentFile != -1){
        fileEdits[currentFile] = ui->textEdit->toPlainText();
        if(fileEdits[currentFile] == files[currentFile]){
            ui->savedLabel->setText("Saved");
            ui->savedLabel->setStyleSheet("QLabel { color : green; }");
        } else {
            ui->savedLabel->setText("*Not Saved");
            ui->savedLabel->setStyleSheet("QLabel { color : red; }");
        }
    } else {
         ui->savedLabel->setText("No Opened File");
         ui->savedLabel->setStyleSheet("QLabel { color : black; }");
    }


}


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if(column == 0){
        //open file
        currentFile = row;
        ui->textEdit->setText(files[currentFile]);
        if(fileEdits[currentFile] == files[currentFile]){
            ui->savedLabel->setText("Saved");
            ui->savedLabel->setStyleSheet("QLabel { color : green; }");
        } else {
            ui->savedLabel->setText("*Not Saved");
            ui->savedLabel->setStyleSheet("QLabel { color : red; }");
        }

    } else {
        //close file
        currentFile = -1;
        files.erase(files.begin()+row);
        ui->textEdit->setText("");
        ui->tableWidget->removeRow(row);
        ui->savedLabel->setText("No Opened File");
        ui->savedLabel->setStyleSheet("QLabel { color : black; }");
    }

}

