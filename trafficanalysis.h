#ifndef TRAFFICANALYSIS_H
#define TRAFFICANALYSIS_H

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

namespace Ui {
class TrafficAnalysis;
}

class TrafficAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit TrafficAnalysis(QWidget *parent = 0);
    ~TrafficAnalysis();

private:
    Ui::TrafficAnalysis *ui;
    void friend readPackets(QFile); //чтение пакетов с файла

private slots:
    void pushButton_open_pressed();
    void pushButton_find_pressed();
    void pushButton_clear_pressed();
};

#endif // TRAFFICANALYSIS_H
