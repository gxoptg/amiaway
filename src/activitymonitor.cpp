#include "activitymonitor.h"
#include <QDateTime>
#include <windows.h>

/************************* HELPERS ************************/
/**
 * @brief Returns the timestamp of the last input event.
 */
quint64 getLastInputTickCount()
{
    PLASTINPUTINFO lastInputInfo = new LASTINPUTINFO;
    lastInputInfo->cbSize = sizeof(LASTINPUTINFO);
    GetLastInputInfo(lastInputInfo);
    return lastInputInfo->dwTime;
}

/**
 * @brief Returns the timestamp of this exact moment.
 */
quint64 getCurrentTickCount()
{
    return GetTickCount();
}


/************************* CLASS METHODS ******************/
ActivityMonitor::ActivityMonitor(QObject *parent) :
    ActivityMonitor(ActivityMonitor::DEFAULT_INACTIVITY_INTERVAL, parent)
{

}

ActivityMonitor::ActivityMonitor(int inactivityInterval, QObject *parent) :
    QObject(parent), m_inactivityInterval(inactivityInterval)
{
    initState();
    initTimer();
}

/**
 * @brief Returns the inactivity interval.
 */
int ActivityMonitor::inactivityInterval() const
{
    return m_inactivityInterval;
}

/**
 * @brief Sets the inactivity interval.
 */
void ActivityMonitor::setInactivityInterval(quint64 inactivityInterval)
{
    m_inactivityInterval = inactivityInterval;
}

/**
 * @brief Initializes the current user’s state.
 */
void ActivityMonitor::initState()
{
    // Retrieve the last input timestamp
    quint64 lastInputTimestamp = getLastInputTickCount();
    quint64 currentTimestamp = getCurrentTickCount();

    // Deside which state is user in now
    ActivityState state = (currentTimestamp - lastInputTimestamp < uint(m_inactivityInterval)) ? ActivityState::Active : ActivityState::Inactive;

    // Save the timestamp and the state
    m_lastInputEventTimestamp = lastInputTimestamp;
    m_activityState = state;
}

/**
 * @brief Initializes the timer to check for state updates.
 */
void ActivityMonitor::initTimer()
{
    m_activityTimer.setInterval(ACTIVITY_TIMER_INTERVAL);
    connect(&m_activityTimer, SIGNAL(timeout()), SLOT(checkStateChanged()));
    m_activityTimer.start();
}

/**
 * @brief Checks if the user’s state is changed and emits according signals if it is.
 */
void ActivityMonitor::checkStateChanged()
{
    // Retrieve the last input timestamp
    int lastInputTimestamp = getLastInputTickCount();
    int currentTimestamp = getCurrentTickCount();

    // Deside which state is user in now
    ActivityState state = (currentTimestamp - lastInputTimestamp < m_inactivityInterval) ? ActivityState::Active : ActivityState::Inactive;

    // Check and notify if the status was changed
    if (state != m_activityState) {
        emit activityStateChanged(state);

        if (state == ActivityState::Active) {
            emit becameActive();
        } else {
            emit becameInactive();
        }
    }

    // Save the timestamp and the state
    m_lastInputEventTimestamp = lastInputTimestamp;
    m_activityState = state;
}

