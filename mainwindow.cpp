#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_fsm(this)
{
    ui->setupUi(this);
    connect(this, SIGNAL(identifyFinished(int)), &m_fsm, SLOT(onIdentifyFinished(int)));
    connect(this, SIGNAL(depositboxCellOpened(int)), &m_fsm, SLOT(onDepositboxCellOpened(int)));
    connect(this, SIGNAL(depositboxCellClosed(int)), &m_fsm, SLOT(onDepositboxCellClosed(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
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

void MainWindow::on_btnStart_released()
{
    // Start QScxmlStateMachine
    m_fsm.run("depositbox.scxml");
}

void MainWindow::on_btnPalm1_released()
{
    emit identifyFinished(1);
}

void MainWindow::on_btnPalm2_released()
{
    emit identifyFinished(2);
}

void MainWindow::on_btnCard1_released()
{
    emit identifyFinished(11);
}

void MainWindow::on_btnCard2_released()
{
    emit identifyFinished(12);
}

void MainWindow::on_btnOpenCell2_released()
{
    emit depositboxCellOpened(2);

}

void MainWindow::on_btnOpenCell3_released()
{
    emit depositboxCellOpened(3);
}

void MainWindow::on_btnOpenCell4_released()
{
    emit depositboxCellOpened(4);
}

void MainWindow::on_btnCloseCell2_released()
{
    emit depositboxCellClosed(2);
}

void MainWindow::on_btnCloseCell3_released()
{
    emit depositboxCellClosed(3);
}

void MainWindow::on_btnCloseCell4_released()
{
    emit depositboxCellClosed(4);
}
