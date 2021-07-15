#include "mainwindow.h"
#include "ui_mainwindow.h"



int currentFile = 0;
QVector<QString> files;
QVector<QString> fileEdits;
QVector<QString> fileNames;
QVector<int> flags;
syntaxHighlighter * highlighter;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    highlighter = new syntaxHighlighter(ui->textBrowser);
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(save()));
    ui->plainTextEdit->hide();
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
            if(!flags[currentFile]){
                file.write(ui->textBrowser->toPlainText().toLocal8Bit(),qstrlen(ui->textBrowser->toPlainText().toLocal8Bit()));
                fileEdits[currentFile] = ui->textBrowser->toPlainText();
                files[currentFile] = ui->textBrowser->toPlainText();
            } else {
                file.write(ui->plainTextEdit->toPlainText().toLocal8Bit(),qstrlen(ui->plainTextEdit->toPlainText().toLocal8Bit()));
                fileEdits[currentFile] = ui->plainTextEdit->toPlainText();
                files[currentFile] = ui->plainTextEdit->toPlainText();
            }

            ui->savedLabel->setText("Saved");
            ui->savedLabel->setStyleSheet("QLabel { color : green; }");

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
    if(std::find(fileNames.begin(), fileNames.end(),fileName) != fileNames.end()){
        QMessageBox::information(0, "Error", "File Already Opened");
    } else {

        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "Error", file.errorString());
        }
        else {
        #pragma omp parallel num_threads(4)

            // Open file in text editor
            QString txt = file.readAll();
            int size = txt.size();
            if(size < 300000){
                flags.push_back(0);
                ui->textBrowser->show();
                ui->plainTextEdit->hide();
                ui->textBrowser->setPlainText(txt);
                files.push_back(ui->textBrowser->toPlainText());
                fileEdits.push_back(ui->textBrowser->toPlainText());

            } else {
                flags.push_back(1);
                QMessageBox::information(0, "Warning", "Styling disabled for better performance");
                ui->textBrowser->hide();
                ui->plainTextEdit->show();
                ui->plainTextEdit->setPlainText(txt);
                files.push_back(ui->plainTextEdit->toPlainText());
                fileEdits.push_back(ui->plainTextEdit->toPlainText());
            }


    //        ui->textEdit->setText(txt);

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

    //        if(!flag){
    //            QVector<balance_error> errors;
    //            errors = balance_tags(txt.toUtf8().constData());
    //            QString markedErrors = markErrors(errors, ui->textBrowser->toPlainText());
    //            fileEdits[currentFile] = markedErrors;
    //            ui->textBrowser->setText(markedErrors);
    //        } else {
    //            QVector<balance_error> errors;
    //            errors = balance_tags(txt.toUtf8().constData());
    //            QString markedErrors = markErrors(errors, ui->plainTextEdit->toPlainText());
    //            fileEdits[currentFile] = markedErrors;
    //            ui->plainTextEdit->setPlainText(markedErrors);

    //        }

        }

    }

}




void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if(column == 0){
        //open file
        if(flags[currentFile]){
            fileEdits[currentFile] = ui->plainTextEdit->toPlainText();
        } else {
            fileEdits[currentFile] = ui->textBrowser->toPlainText();
        }
        currentFile = row;
        if(!flags[currentFile]){
            ui->textBrowser->setText(fileEdits[currentFile]);
            ui->textBrowser->show();
            ui->plainTextEdit->hide();
        } else {
            ui->textBrowser->hide();
            ui->plainTextEdit->setPlainText(fileEdits[currentFile]);
            ui->plainTextEdit->show();

        }


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
        flags.erase(flags.begin()+row);
        ui->textBrowser->setText("");
        ui->plainTextEdit->setPlainText("");
        ui->tableWidget->removeRow(row);
        ui->savedLabel->setText("No Opened File");
        ui->savedLabel->setStyleSheet("QLabel { color : black; }");
    }

}


void MainWindow::on_textBrowser_textChanged()
{
    if(currentFile != -1){
        if(!flags[currentFile]){
            if(files.size() != 0 && currentFile != -1){
                if(ui->textBrowser->toPlainText() == files[currentFile]){
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
    }

}

void MainWindow::on_plainTextEdit_textChanged()
{
    if(currentFile != -1){
        if(flags[currentFile]){
            if(files.size() != 0 && currentFile != -1){
                if(ui->plainTextEdit->toPlainText() == files[currentFile]){
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
    }


}

