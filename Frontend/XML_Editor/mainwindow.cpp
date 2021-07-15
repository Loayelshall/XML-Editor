#include "mainwindow.h"
#include "ui_mainwindow.h"



int currentFile = 0;
QVector<QString> files;
QVector<QString> fileEdits;
QVector<QString> fileNames;
QVector<int> flags;
syntaxHighlighter * highlighter;
QVector<tree_node*> trees;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    highlighter = new syntaxHighlighter(ui->textBrowser);
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(save()));
    ui->plainTextEdit->hide();
    ui->deCompBtn->hide();

    ui->compressBtn->setDisabled(true);
    ui->prettyBtn->setDisabled(true);
    ui->miniBtn->setDisabled(true);
    ui->jsonBtn->setDisabled(true);
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
        in.insert(j+1, "   --!");
    }
    return in;

}


void MainWindow::save(){
    if(files.size() != 0 && currentFile != -1){
        //write to file;
        QFile file(fileNames[currentFile]);      
        if(file.open(QIODevice::ReadWrite)){
            if(!flags[currentFile]){
                if(ui->textBrowser->toPlainText().contains("!Error")){
                    QMessageBox::information(0, "Error", "Please fix or delete errors before saving");
                    ui->savedLabel->setText("*Not Saved");
                    ui->savedLabel->setStyleSheet("QLabel { color : red; }");
                } else {
                    file.write(ui->textBrowser->toPlainText().toLocal8Bit(),qstrlen(ui->textBrowser->toPlainText().toLocal8Bit()));
                    fileEdits[currentFile] = ui->textBrowser->toPlainText();
                    files[currentFile] = ui->textBrowser->toPlainText();
                    ui->savedLabel->setText("Saved");
                    ui->savedLabel->setStyleSheet("QLabel { color : green; }");
                }
            } else {
                if(ui->plainTextEdit->toPlainText().contains("!Error")){
                    QMessageBox::information(0, "Error", "Please fix or delete errors before saving");
                    ui->savedLabel->setText("*Not Saved");
                    ui->savedLabel->setStyleSheet("QLabel { color : red; }");
                } else {
                    file.write(ui->plainTextEdit->toPlainText().toLocal8Bit(),qstrlen(ui->plainTextEdit->toPlainText().toLocal8Bit()));
                    fileEdits[currentFile] = ui->plainTextEdit->toPlainText();
                    files[currentFile] = ui->plainTextEdit->toPlainText();
                    ui->savedLabel->setText("Saved");
                    ui->savedLabel->setStyleSheet("QLabel { color : green; }");
                }
            }



            file.close();
        } else {
            QMessageBox::information(0, "Error", file.errorString());
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("XML files (*.xml *.xml-compressed)"));
    QFile file(fileName);
    if(std::find(fileNames.begin(), fileNames.end(),fileName) != fileNames.end()){
        QMessageBox::information(0, "Error", "File Already Opened");
    } else {

        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "Error", file.errorString());
        }
        else {
        #pragma omp parallel num_threads(4)
            QString txt = file.readAll();
            if(fileName.contains("-compressed")){
                flags.push_back(1);
                ui->textBrowser->hide();
                ui->plainTextEdit->show();
                ui->plainTextEdit->setPlainText(txt);
                files.push_back(ui->plainTextEdit->toPlainText());
                fileEdits.push_back(ui->plainTextEdit->toPlainText());
                ui->compressBtn->hide();
                ui->deCompBtn->show();
                ui->compressBtn->setDisabled(true);
                ui->prettyBtn->setDisabled(true);
                ui->miniBtn->setDisabled(true);
                ui->jsonBtn->setDisabled(true);
                ui->deCompBtn->setDisabled(false);

            } else {
                ui->compressBtn->setDisabled(false);
                ui->prettyBtn->setDisabled(false);
                ui->miniBtn->setDisabled(false);
                ui->jsonBtn->setDisabled(false);
                ui->compressBtn->show();
                ui->deCompBtn->hide();

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

        #pragma omp parallel

             QVector<balance_error> errors;
            if(!flags[currentFile]){
                errors = balance_tags(txt.toUtf8().constData());
                QString markedErrors = markErrors(errors, ui->textBrowser->toPlainText());
                fileEdits[currentFile] = markedErrors;
                ui->textBrowser->setText(markedErrors);
            } else if(flags[currentFile] && !fileName.contains("-compressed")){
                errors = balance_tags(txt.toUtf8().constData());
                QString markedErrors = markErrors(errors, ui->plainTextEdit->toPlainText());
                fileEdits[currentFile] = markedErrors;
                ui->plainTextEdit->setPlainText(markedErrors);
            }
            if(errors.size() == 0 && !fileName.contains("-compressed")){
                tree_node * root = new tree_node("XML","");
                parse_tree(root,files[currentFile].toLocal8Bit().constData());
                trees.push_back(root);
            } else {
                trees.push_back(nullptr);
            }

        }


    }

}




void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if(column == 0){
        //open file
        if(currentFile != -1){
            if(flags[currentFile]){
                fileEdits[currentFile] = ui->plainTextEdit->toPlainText();
            } else {
                fileEdits[currentFile] = ui->textBrowser->toPlainText();
            }
        }

        currentFile = row;
        if(fileNames[currentFile].contains("-compressed") || fileNames[currentFile].contains("json")){
            ui->deCompBtn->show();
            ui->compressBtn->hide();
            if(fileNames[currentFile].contains("json")){
                ui->deCompBtn->setDisabled(true);
            } else {
                ui->deCompBtn->setDisabled(false);
            }
            ui->compressBtn->setDisabled(true);
            ui->prettyBtn->setDisabled(true);
            ui->miniBtn->setDisabled(true);
            ui->jsonBtn->setDisabled(true);
        } else {
            ui->deCompBtn->hide();
            ui->compressBtn->show();
            ui->compressBtn->setDisabled(false);
            ui->prettyBtn->setDisabled(false);
            ui->miniBtn->setDisabled(false);
            ui->jsonBtn->setDisabled(false);
        }
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
        trees.erase(trees.begin()+row);
        ui->textBrowser->setText("");
        ui->plainTextEdit->setPlainText("");
        ui->tableWidget->removeRow(row);
        ui->savedLabel->setText("No Opened File");
        ui->savedLabel->setStyleSheet("QLabel { color : black; }");
        ui->compressBtn->setDisabled(true);
        ui->prettyBtn->setDisabled(true);
        ui->miniBtn->setDisabled(true);
        ui->jsonBtn->setDisabled(true);
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
                if(fileNames[currentFile].contains("-compressed") || fileNames[currentFile].contains("json")){
                    ui->deCompBtn->show();
                    ui->compressBtn->hide();
                    if(fileNames[currentFile].contains("json")){
                        ui->deCompBtn->setDisabled(true);
                    } else {
                        ui->deCompBtn->setDisabled(false);
                    }
                    ui->compressBtn->setDisabled(true);
                    ui->prettyBtn->setDisabled(true);
                    ui->miniBtn->setDisabled(true);
                    ui->jsonBtn->setDisabled(true);
                } else {
                    ui->compressBtn->setDisabled(false);
                    ui->prettyBtn->setDisabled(false);
                    ui->miniBtn->setDisabled(false);
                    ui->jsonBtn->setDisabled(false);
                    ui->deCompBtn->hide();
                    ui->compressBtn->show();
                }

            } else {
                ui->compressBtn->setDisabled(true);
                ui->prettyBtn->setDisabled(true);
                ui->miniBtn->setDisabled(true);
                ui->jsonBtn->setDisabled(true);
                ui->deCompBtn->hide();
                ui->compressBtn->show();
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
                if(fileNames[currentFile].contains("-compressed") || fileNames[currentFile].contains("json")){
                    ui->deCompBtn->show();
                    ui->compressBtn->hide();
                    if(fileNames[currentFile].contains("json")){
                        ui->deCompBtn->setDisabled(true);
                    } else {
                        ui->deCompBtn->setDisabled(false);
                    }
                    ui->compressBtn->setDisabled(true);
                    ui->prettyBtn->setDisabled(true);
                    ui->miniBtn->setDisabled(true);
                    ui->jsonBtn->setDisabled(true);
                } else {
                    ui->compressBtn->setDisabled(false);
                    ui->prettyBtn->setDisabled(false);
                    ui->miniBtn->setDisabled(false);
                    ui->jsonBtn->setDisabled(false);
                    ui->deCompBtn->hide();
                    ui->compressBtn->show();
                }
            } else {
                ui->compressBtn->setDisabled(true);
                ui->prettyBtn->setDisabled(true);
                ui->miniBtn->setDisabled(true);
                ui->jsonBtn->setDisabled(true);
                 ui->savedLabel->setText("No Opened File");
                 ui->savedLabel->setStyleSheet("QLabel { color : black; }");
            }
        }
    }


}


void MainWindow::on_prettyBtn_clicked()
{
#pragma omp parallel
    std::string prettyTxt = "";
    if(trees[currentFile] != nullptr){
        tree_node * root = trees[currentFile];
        pretty(root,-1 ,&prettyTxt);
    }
    if(!flags[currentFile]){
        ui->textBrowser->setPlainText(QString::fromLocal8Bit(prettyTxt.c_str()));
    } else {
        ui->plainTextEdit->setPlainText(QString::fromLocal8Bit(prettyTxt.c_str()));
    }
}


void MainWindow::on_miniBtn_clicked()
{
#pragma omp parallel
    std::string miniTxt = "";
    if(trees[currentFile] != nullptr){
        tree_node * root = trees[currentFile];
        minify(root, &miniTxt);
    }
    if(!flags[currentFile]){
        ui->textBrowser->setPlainText(QString::fromLocal8Bit(miniTxt.c_str()));
    } else {
        ui->plainTextEdit->setPlainText(QString::fromLocal8Bit(miniTxt.c_str()));
    }
}


void MainWindow::on_compressBtn_clicked()
{
#pragma omp parallel
    if(!flags[currentFile]){
        QFile file(fileNames[currentFile] + "-compressed");
        if(file.open(QIODevice::ReadWrite)){
            QString txt = ui->textBrowser->toPlainText();
            std::vector<int> compressed = compress(txt.toLocal8Bit().constData());
            file.write("",0);
            QTextStream stream( &file );
            for(int i = 0; i < compressed.size(); i++){
                stream << compressed[i] << " ";
            }
            QMessageBox::information(0, "Success", "File Saved Successfully at" + fileNames[currentFile]);
            ui->savedLabel->setText("Saved");
            ui->savedLabel->setStyleSheet("QLabel { color : green; }");

            file.close();
        } else {
            QMessageBox::information(0, "Error", file.errorString());
        }
    } else {

    }


}


void MainWindow::on_deCompBtn_clicked()
{
#pragma omp parallel
        QString txt = ui->plainTextEdit->toPlainText();
        std::vector<int> compressed;
        std::string txtStr = txt.toLocal8Bit().constData();
        for(int i=0; i<txt.length(); i++){
            std::string tmp = "";
            for(;txt[i]!=' ';i++){
                tmp += txtStr[i];
            }

            compressed.push_back(stoi(tmp));
        }

        fileNames[currentFile].replace("-compressed", "");
        ui->tableWidget->removeRow(currentFile);

        QTableWidget * table = ui->tableWidget;
        int rowCount = table->rowCount();
        table->insertRow(rowCount);
        table->setItem(rowCount,0, new QTableWidgetItem(fileNames[currentFile]));
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // Add Exit Button
        table->setItem(rowCount,1, new QTableWidgetItem("Close File"));
        table->item(rowCount,1)->setForeground(QBrush(QColor(255, 0, 0)));

        std::string fileStr = decompress(compressed);
        if(fileStr.size() > 300000){
            flags[currentFile] = 1;
            ui->plainTextEdit->setPlainText(QString::fromLocal8Bit(fileStr.c_str()));
        } else {
            flags[currentFile] = 0;
            ui->plainTextEdit->hide();
            ui->textBrowser->show();
            ui->textBrowser->setText(QString::fromLocal8Bit(fileStr.c_str()));
        }

        QMessageBox::information(0, "Success", "File Decompressed Successfully");
        ui->deCompBtn->hide();
        ui->compressBtn->show();
        ui->savedLabel->setText("*Not Saved");
        ui->savedLabel->setStyleSheet("QLabel { color : red; }");

}


void MainWindow::on_jsonBtn_clicked()
{
#pragma omp parallel
    std::string jsonTxt = "";
    if(!flags[currentFile]){
        QString txt = ui->textBrowser->toPlainText();
        tree_node * root = new tree_node("XML","");
        parse_tree(root,txt.toLocal8Bit().constData());
        xml2json(root,-1, &jsonTxt);

        ui->textBrowser->setPlainText(QString::fromLocal8Bit(jsonTxt.c_str()));
    } else {
        QString txt = ui->plainTextEdit->toPlainText();
        tree_node * root = new tree_node("XML","");
        parse_tree(root,txt.toLocal8Bit().constData());
        xml2json(root,-1, &jsonTxt);


        ui->plainTextEdit->setPlainText(QString::fromLocal8Bit(jsonTxt.c_str()));
    }


    int size = jsonTxt.size();
    if(size < 300000){
        flags.push_back(0);
        ui->textBrowser->show();
        ui->plainTextEdit->hide();
        ui->textBrowser->setPlainText(QString::fromLocal8Bit(jsonTxt.c_str()));
        files.push_back(ui->textBrowser->toPlainText());
        fileEdits.push_back(ui->textBrowser->toPlainText());

    } else {
        flags.push_back(1);
        QMessageBox::information(0, "Warning", "Styling disabled for better performance");
        ui->textBrowser->hide();
        ui->plainTextEdit->show();
        ui->plainTextEdit->setPlainText(QString::fromLocal8Bit(jsonTxt.c_str()));
        files.push_back(ui->plainTextEdit->toPlainText());
        fileEdits.push_back(ui->plainTextEdit->toPlainText());
    }

    QString tmp = fileNames[currentFile];
    QFile file(tmp.replace(".xml", ".json"));
    if(file.open(QIODevice::ReadWrite)){
        file.write("",0);
        QTextStream stream( &file );
        stream << QString::fromLocal8Bit(jsonTxt.c_str());
        QMessageBox::information(0, "Success", "File Saved Successfully");
        ui->savedLabel->setText("Saved");
        ui->savedLabel->setStyleSheet("QLabel { color : green; }");

        file.close();
    } else {
        QMessageBox::information(0, "Error", file.errorString());
    }


    fileNames.push_back(tmp.replace(".xml", ".json"));
    currentFile = files.size()-1;

    trees.push_back(nullptr);

    // Add file to table
    QTableWidget * table = ui->tableWidget;
    int rowCount = table->rowCount();
    table->insertRow(rowCount);
    table->setItem(rowCount,0, new QTableWidgetItem(fileNames[currentFile]));
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Add Exit Button
    table->setItem(rowCount,1, new QTableWidgetItem("Close File"));
    table->item(rowCount,1)->setForeground(QBrush(QColor(255, 0, 0)));

    ui->compressBtn->setDisabled(true);
    ui->prettyBtn->setDisabled(true);
    ui->miniBtn->setDisabled(true);
    ui->jsonBtn->setDisabled(true);

}

