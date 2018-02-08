#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
