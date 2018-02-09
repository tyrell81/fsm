#include "fsm.h"
#include "logbrowser.h"

QT_MESSAGELOGCONTEXT
Q_LOGGING_CATEGORY(hfFsm, "hf.fsm")

Fsm::Fsm(QObject* parent)
    : QObject(parent)
    , m_machine{}
{
}

Fsm::~Fsm()
{
    qCDebug(hfFsm);
    if (m_machine != Q_NULLPTR) {
        m_machine->stop();
        m_machine->deleteLater();
    }
}

void Fsm::run(QString scxmlFilePath)
{
    qCDebug(hfFsm) << "scxmlFilePath:" << scxmlFilePath;

    if (m_machine != Q_NULLPTR) {
        m_machine->stop();
        m_machine->deleteLater();
        qCDebug(hfFsm) << "m_machine stopped";
    }

    try {
        m_machine = QScxmlStateMachine::fromFile(scxmlFilePath);
    } catch (int e) {
        qCCritical(hfFsm) << "Cannot load scxml file";
        qCCritical(hfFsm) << "Cannot load scxml file" << scxmlFilePath;
    }

    if (!m_machine->parseErrors().isEmpty()) {
        const auto errors = m_machine->parseErrors();
        for (const QScxmlError& error : errors) {
            qCCritical(hfFsm) << error.toString();
        }
        return;
    }

    qCDebug(hfFsm) << "scxml file loaded successfully:" << scxmlFilePath;

    connectMachineEvents();
    m_machine->setParent(this);
    m_machine->start();
}

void Fsm::stop()
{
    qCDebug(hfFsm);

    if (m_machine != Q_NULLPTR) {
        m_machine->stop();
        m_machine->deleteLater();
    }
}

void Fsm::connectMachineEvents()
{
    /*********  события переходов FSM *********
     * grep -oP 'event=\"\K\w+' depositbox.scxml
     * m_machine->submitEvent("tap", data);
     *****************************************/

    /********* raise-send cобытия из FSM *********/
    m_machine->connectToEvent("sendCheckCell", this, &Fsm::sendCheckCell);
}

/********* События из воркера *********/
void Fsm::onIdentifyFinished(int id_employee)
{
    if (m_machine == Q_NULLPTR || !m_machine->isRunning()) {
        qCWarning(hfFsm) << "FSM not running. Start it first";
        return;
    }

    qCDebug(hfFsm) << "id_employee:" << id_employee;
}

void Fsm::onDepositboxCellOpened(int cell_num)
{
    if (m_machine == Q_NULLPTR || !m_machine->isRunning()) {
        qCWarning(hfFsm) << "FSM not running. Start it first";
        return;
    }

    qCDebug(hfFsm) << "cell_num:" << cell_num;
}

void Fsm::onDepositboxCellClosed(int cell_num)
{
    if (m_machine == Q_NULLPTR || !m_machine->isRunning()) {
        qCWarning(hfFsm) << "FSM not running. Start it first";
        return;
    }

    qCDebug(hfFsm) << "cell_num:" << cell_num;
}

/********* raise-send cобытия из FSM *********/
void Fsm::sendCheckCell()
{
    qCDebug(hfFsm);
    QVariantMap data;
    qCDebug(hfFsm) << "evCheckCellSuccess";
    m_machine->submitEvent("evCheckCellSuccess", data);
}




