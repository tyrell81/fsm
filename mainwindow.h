#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fsm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg);

protected slots:
    void save();

signals:
    void identifyFinished(int id_employee);
    void depositboxCellOpened(int cell_num);
    void depositboxCellClosed(int cell_num);

private slots:
    void on_btnStart_released();
    void on_btnPalm1_released();
    void on_btnPalm2_released();
    void on_btnCard1_released();
    void on_btnCard2_released();
    void on_btnOpenCell2_released();
    void on_btnOpenCell3_released();
    void on_btnOpenCell4_released();
    void on_btnCloseCell2_released();
    void on_btnCloseCell3_released();
    void on_btnCloseCell4_released();

private:
    Ui::MainWindow* ui;
    Fsm m_fsm;
};

#endif // MAINWINDOW_H
