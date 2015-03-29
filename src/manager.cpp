#include "manager.h"
#include <QDateTime>
#include <QDebug>
#include <QSettings>

const QString MONITOR_SETTINGS_FILE = "./monitor_settings.ini";
const QString SERVER_SETTINGS_FILE = "./server_settings.ini";

Manager::Manager(QObject *parent) : QObject(parent)
{
    setupActivityMonitor();
    setupActivityServer();
}

Manager::~Manager()
{

}

void Manager::start()
{
    connect(&m_activityMonitor, SIGNAL(activityStateChanged(ActivityState)),
            &m_activityLogger, SLOT(updateActivityState(ActivityState)));

    connect(&m_activityMonitor, SIGNAL(activityStateChanged(ActivityState)),
            &m_activityServer, SLOT(updateActivityState(ActivityState)));
}

void Manager::setupActivityMonitor()
{
    QSettings settings(MONITOR_SETTINGS_FILE, QSettings::IniFormat);
    m_activityMonitor.setInactivityInterval(settings.value("inactivity_interval").toString().toInt());
}

void Manager::setupActivityServer()
{
    QSettings settings(SERVER_SETTINGS_FILE, QSettings::IniFormat);
    m_activityServer.setUrl(settings.value("url").toString());
    m_activityServer.setComputerId(settings.value("computer_id").toString());
    m_activityServer.setSecretKey(settings.value("secret_key").toString());
}

