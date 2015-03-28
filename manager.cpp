#include "manager.h"
#include <QDateTime>
#include <QDebug>

Manager::Manager(QObject *parent) : QObject(parent), m_activityMonitor(1500)
{

}

Manager::~Manager()
{

}

void Manager::start()
{
    connect(&m_activityMonitor, SIGNAL(activityStateChanged(ActivityState)),
            &m_activityLogger, SLOT(logActivityState(ActivityState)));
}

void Manager::logStatus(ActivityState state)
{
    QString stateString = (state == ActivityState::Active) ? "Active" : "Inactive";
    qDebug() << QDateTime::currentDateTime().toString() << stateString;
}

