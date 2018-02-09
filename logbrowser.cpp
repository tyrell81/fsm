#include <QMetaType>

#include "logbrowser.h"
#include "mainwindow.h"

LogBrowser::LogBrowser(QObject* parent)
    : QObject(parent)
{
    qRegisterMetaType<QtMsgType>("QtMsgType");
    logMainWindow = new MainWindow;
    //    connect(this, SIGNAL(sendMessage(QtMsgType, QMessageLogContext, QString)), logMainWindow, SLOT(outputMessage(QtMsgType, QMessageLogContext, QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(sendMessage(QtMsgType, QMessageLogContext, QString)), logMainWindow, SLOT(outputMessage(QtMsgType, QMessageLogContext, QString)));
    logMainWindow->show();
}

LogBrowser::~LogBrowser()
{
    delete logMainWindow;
}

void LogBrowser::outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    emit sendMessage(type, context, msg);
}
