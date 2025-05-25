#include "../include/mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Mac Stats Monitor");
    resize(400, 200);  // 창 크기를 좀 더 작게 조정
    
    // 중앙 위젯 설정
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    // 상태 표시를 위한 레이블들
    QLabel *titleLabel = new QLabel("System Statistics", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    layout->addWidget(titleLabel);
    
    // 메모리 정보 레이블
    memoryLabel = new QLabel(this);
    memoryLabel->setAlignment(Qt::AlignCenter);
    memoryLabel->setStyleSheet("font-size: 14px; margin: 5px;");
    layout->addWidget(memoryLabel);
    
    // 업데이트 타이머 설정
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateStats);
    updateTimer->start(1000); // 1초마다 업데이트
    
    // 초기 상태 업데이트
    updateStats();
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateStats()
{
    if (memoryStats.updateMemoryInfo()) {
        MemoryInfo info = memoryStats.getMemoryInfo();
        
        // 메모리 정보 업데이트
        QString memoryText = QString("Memory: %1 used of %2 (%3%)")
            .arg(memoryStats.formatSize(info.used))
            .arg(memoryStats.formatSize(info.total))
            .arg(QString::number(info.usedPercent, 'f', 1));
        memoryLabel->setText(memoryText);
    }
} 