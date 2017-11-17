#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "calculator.h"
#include "trafficanalysis.h"
#include <QMainWindow>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void CalculatorWindow();
    void TrafficAnalysisWindow();
};

#endif // MAINWINDOW_H
