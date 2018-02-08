#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString type_msg = "";

    switch (type) {
    case QtWarningMsg:
        type_msg = "— WARNING: ";
        break;

    case QtCriticalMsg:
        type_msg = "— CRITICAL: ";
        break;

    case QtFatalMsg:
        type_msg = "— FATAL: ";
        break;

    default:
        break;
    }

    ui->txtLogBrowser->append(tr("%1 [%2](%3): %4").arg(type_msg).arg(context.category).arg(context.function).arg(msg));
}

void MainWindow::save()
{
    QString saveFileName = QFileDialog::getSaveFileName(
        this,
        tr("Save Log Output"),
        tr("%1/logfile.txt").arg(QDir::homePath()),
        tr("Text Files (*.txt);;All Files (*)"));

    if (saveFileName.isEmpty())
        return;

    QFile file(saveFileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(
            this,
            tr("Error"),
            QString(tr("<nobr>File '%1'<br/>cannot be opened for writing.<br/><br/>"
                       "The log output could <b>not</b> be saved!</nobr>"))
                .arg(saveFileName));
        return;
    }

    QTextStream stream(&file);
    stream << ui->txtLogBrowser->toPlainText();
    file.close();
}
