#ifndef FSM_H
#define FSM_H

#include <QLoggingCategory>
#include <QObject>
#include <QScxmlStateMachine>

Q_DECLARE_LOGGING_CATEGORY(hfFsm)

class Fsm : public QObject {
    Q_OBJECT
public:
    explicit Fsm(QObject* parent = nullptr);
    ~Fsm();

    void run(QString scxmlFilePath);
    void stop();

    void connectMachineEvents();

signals:

public slots:
    void onIdentifyFinished(int id_employee);
    void onDepositboxCellOpened(int cell_num);
    void onDepositboxCellClosed(int cell_num);

private slots:
    void sendCheckCell();

private:
    QScxmlStateMachine* m_machine;
};

#endif // FSM_H
