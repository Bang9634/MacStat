#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "system_stats/memory_stats.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateStats();

private:
    QLabel *memoryLabel;
    QTimer *updateTimer;
    MemoryStats memoryStats;
};

#endif // MAINWINDOW_H 