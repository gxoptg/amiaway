#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "activitymonitor.h"
#include "activitylogger.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = 0);
    ~Manager();

signals:

public slots:
    void start();

private slots:
    void logStatus(ActivityState state);

private /*variables*/:
    ActivityMonitor m_activityMonitor;
    ActivityLogger m_activityLogger;
};

#endif // MANAGER_H
