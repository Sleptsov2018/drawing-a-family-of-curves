#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QStringList>
#include <QTextStream>

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
    void on_fileBtn_clicked();

    void on_action_author_triggered();

    void on_action_help_triggered();

    void on_action_exit_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
