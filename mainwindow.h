#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class BusyTipWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    BusyTipWidget* m_tip = nullptr;
};

#endif // MAINWINDOW_H
