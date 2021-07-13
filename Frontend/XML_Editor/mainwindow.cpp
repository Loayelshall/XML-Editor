#include "mainwindow.h"
#include "ui_mainwindow.h"



int currentFile = 0;
QVector<QString> files;
QVector<QString> fileEdits;
QVector<QString> fileNames;
syntaxHighlighter * highlighter;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    highlighter = new syntaxHighlighter(ui->textEdit);
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(save()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete highlighter;
}


QString markErrors(QVector<balance_error> errors, QString in){
    std::sort(errors.begin(), errors.end(), [](balance_error a, balance_error b) { return a.index < b.index; });
    for(int i=0; i<errors.size(); i++){
        int insertionIndex = errors[i].index + (i*14);
        in.insert(insertionIndex, "!Error <--   ");
        int j = insertionIndex;
        while(1){
            j++;
            if(in[j] == ">"){
                break;
            }
        }
        in.insert(j+1, "   -->");
    }
    return in;

}


void MainWindow::save(){
    if(files.size() != 0 && currentFile != -1){
        //write to file;
        QFile file(fileNames[currentFile]);
        if(file.open(QIODevice::ReadWrite)){
            file.write(ui->textEdit->toPlainText().toLocal8Bit(),qstrlen(ui->textEdit->toPlainText().toLocal8Bit()));
            ui->savedLabel->setText("Saved");
            ui->savedLabel->setStyleSheet("QLabel { color : green; }");
            fileEdits[currentFile] = ui->textEdit->toPlainText();
            files[currentFile] = ui->textEdit->toPlainText();
            file.close();
        } else {
            QMessageBox::information(0, "Error", file.errorString());
        }
    }
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
        fileNames.push_back(fileName);
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

        QVector<balance_error> errors;
        errors = balance_tags(txt.toUtf8().constData());
        QString markedErrors = markErrors(errors, ui->textEdit->toPlainText());
        fileEdits[currentFile] = markedErrors;
        ui->textEdit->setText(markedErrors);

    }
}


void MainWindow::on_textEdit_textChanged()
{
    if(files.size() != 0 && currentFile != -1){
        if(ui->textEdit->toPlainText() == files[currentFile]){
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
        fileEdits[currentFile] = ui->textEdit->toPlainText();
        currentFile = row;
        ui->textEdit->setText(fileEdits[currentFile]);
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
        fileEdits.erase(fileEdits.begin()+row);
        fileNames.erase(fileNames.begin()+row);
        ui->textEdit->setText("");
        ui->tableWidget->removeRow(row);
        ui->savedLabel->setText("No Opened File");
        ui->savedLabel->setStyleSheet("QLabel { color : black; }");
    }

}

