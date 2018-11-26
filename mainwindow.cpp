#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // Чтобы менять масштаб мышкой и двигаться по графику
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileBtn_clicked()
{
    // Вызываем диалог и сохраняем путь до файла в строку
    QString filePath = QFileDialog::getOpenFileName(0, "Open txt file", QString(), "*.txt");
    QFile readFile(filePath);
    QTextStream stream(&readFile);

    int countLines = 0;

    ui->widget->clearGraphs();
    if (readFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        while (!stream.atEnd())
        {
            bool checker;
            // Считываем количество точек
            int value = stream.readLine().toInt(&checker); // trimmed() удаляет пробелы
            if (!checker)
            {
                qDebug() << "Не число.[1]";
                readFile.close();
                return;
                //qApp->exit();
                //QApplication::exit();
                //QApplication::close();
            }

            // Меняем размер вектора под необходимое количество точек
            QVector<double> x(value), y(value);
            for (int i = 0; i < value; i++)
            {
                // Считываем в стринг лист строчки, разделённые
                QStringList list = stream.readLine().simplified().split(' '); // метод simplified() заменяет все пробелы на один
                if (list.length() != 2)
                {
                    qDebug() << "Одна или много точек.";
                    readFile.close();
                    return;
                }
                // Добавляем координаты из листа
                x[i] = list.at(0).toDouble(&checker);
                if (!checker)
                {
                    qDebug() << "Не число.[2]";
                    readFile.close();
                    return;
                }
                y[i] = list.at(1).toDouble(&checker);
                if (!checker)
                {
                    qDebug() << "Не число.[3]";
                    readFile.close();
                    return;
                }
            }

            //Установим область для оси Ox, которая будет показываться на графике
            //ui->widget->xAxis->setRange(0.6, 1);

            ui->widget->addGraph();
            //Говорим, что отрисовать нужно график по нашим двум массивам x и y
            ui->widget->graph(countLines)->setData(x, y);
            ui->widget->graph(countLines)->setPen(QColor(50, 50, 50, 255)); //Задаем цвет точки
            //формируем вид точек
            ui->widget->graph(countLines++)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
            qDebug() << x;
            qDebug() << y;
        }
        readFile.close();
    }
    else
        qDebug() << "File opening error.";

    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("X");
    ui->widget->yAxis->setLabel("Y");

    // Перерисовываем график на нашем widget
    ui->widget->replot();
}

void MainWindow::on_action_author_triggered()
{
    QMessageBox::about(this, "Автор", "Слепцов Михаил из группы М8О-212Б-17");
}

void MainWindow::on_action_help_triggered()
{
    QMessageBox::about(this, "Помощь", "Помощи не будет. Программа отдыхает.");
}

void MainWindow::on_action_exit_triggered()
{
    this->close();
}
