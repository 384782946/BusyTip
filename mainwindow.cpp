#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "busytipwidget.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_tip = new BusyTipWidget(this);
    m_tip->setTip(QStringLiteral("数据加载中..."));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    m_tip->setStyle(BusyTipWidget::Dot);
    m_tip->show(8000);
}

void MainWindow::on_pushButton_2_clicked()
{
    m_tip->setStyle(BusyTipWidget::Round);
    m_tip->show(8000);
}
