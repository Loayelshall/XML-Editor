#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "QDebug"
#include "QMessageBox"
#include "QVector"
#include "syntaxhighlighter.h"
#include "../../Core/types.h"
#include "../../Core/balance_tags.h"
#include "../../Core/minify.h"
#include "../../Core/parse_tree.h"
#include "../../Core/prettifying.h"
#include "../../Core/compress.h"
#include "../../Core/xml2json.h"
#include "algorithm"
#include <QShortcut>
#include <conio.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void save();

    void on_textBrowser_textChanged();

    void on_plainTextEdit_textChanged();

    void on_prettyBtn_clicked();

    void on_miniBtn_clicked();

    void on_compressBtn_clicked();

    void on_deCompBtn_clicked();

    void on_jsonBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
