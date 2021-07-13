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
#include "algorithm"
#include <QShortcut>

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

    void on_textEdit_textChanged();

    void on_tableWidget_cellClicked(int row, int column);

    void save();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
