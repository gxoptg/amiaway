#ifndef ACTIVITYMONITOR_H
#define ACTIVITYMONITOR_H

#include <QObject>
#include <QTimer>

enum class ActivityState { Inactive, Active };

/**
 * @brief The ActivityMonitor class tracks the activity and inactivity periods on the computer.
 * When a user gets active after a period of inactivity, it emits becameActive() signal.
 * When a user gets inactive after a period of activity, it emits becameInactive() signal.
 *
 * A user is inactive if they do not produce any input events for a specific time interval (“inactivity interval”).
 * The inactivity interval is measured in milliseconds and is set by passing its value to the construtor.
 * The default value for the inactivity interval is 300000 ms (5 minutes).
 *
 * The inactivity interval is measured with the precision of 500 ms.
 */
class ActivityMonitor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int inactivityInterval READ inactivityInterval WRITE setInactivityInterval)

public:
    explicit ActivityMonitor(QObject *parent = 0);
    ActivityMonitor(int inactivityInterval, QObject *parent = 0);

    int inactivityInterval() const;

signals:
    /**
     * @brief The becameActive signal is emitted when a user switches to active state \
     * by performing an input event in inactive state.
     */
    void becameActive();

    /**
     * @brief The becameInactive signal is emitted when a user switches to inactive state \
     * by not performing any input events during the inactivity interval.
     */
    void becameInactive();

    /**
     * @brief The activityStateChanged signal is emitted each time the user’s status changes.
     */
    void activityStateChanged(ActivityState);

public slots:

private /*methods*/:
    void initState();
    void initTimer();

private slots:
    void checkStateChanged();

private /*variables*/:
    ActivityState m_activityState;
    int m_lastInputEventTimestamp = 0;

    const int ACTIVITY_TIMER_INTERVAL = 500 /*ms*/;
    QTimer m_activityTimer;

    int m_inactivityInterval = 300000;
};

#endif // ACTIVITYMONITOR_H