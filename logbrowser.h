#ifndef LOGBROWSER_H
#define LOGBROWSER_H

#include <QLoggingCategory>
#include <QObject>

#define DEBUG true

class MainWindow;

class LogBrowser : public QObject {
    Q_OBJECT
public:
    explicit LogBrowser(QObject* parent = 0);
    ~LogBrowser();

public slots:
    void outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg);

signals:
    void sendMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg);

private:
    MainWindow* logMainWindow; // Окно с виджетом лога
};

#endif // LOGBROWSER_H
