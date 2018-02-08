#include <QApplication>
#include <QDebug>
#include <QPointer>

#include "logbrowser.h"
#include "mainwindow.h"

QT_MESSAGELOGCONTEXT

QPointer<LogBrowser> logBrowser;

void logMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    if (logBrowser)
        logBrowser->outputMessage(type, context, msg);
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
    //    return a.exec();
    logBrowser = new LogBrowser;
    qInstallMessageHandler(logMessageOutput);

        qDebug() << "Application started";
//        qCDebug(hfFsm) << "TEST";
//        qCWarning(hfFsm) << "WARN";
    int result = a.exec();
        qDebug() << "application exec return result =" << result;

    delete logBrowser;
    return result;
}
