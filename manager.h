#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "activitymonitor.h"
#include "activitylogger.h"
#include "activityserver.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = 0);
    ~Manager();

signals:

public slots:
    void start();

private /*methods*/:
    void setupActivityServer();

private /*variables*/:
    ActivityMonitor m_activityMonitor;
    ActivityLogger m_activityLogger;
    ActivityServer m_activityServer;
};

#endif // MANAGER_H
