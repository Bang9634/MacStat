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
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

private slots:
    void updateStats();

private:
    QTimer *updateTimer;
    QLabel *memoryLabel;
    MemoryStats memoryStats;
};

#endif // MAINWINDOW_H 