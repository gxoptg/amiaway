#include "activitylogger.h"
#include <QDateTime>
#include <QMap>
#include <iostream>

ActivityLogger::ActivityLogger(QObject *parent) : QObject(parent)
{

}

/**
 * @brief Logs the current date and the new activity state to the console.
 * @param newState New activity state
 */
void ActivityLogger::updateActivityState(ActivityState state) const
{
    std::string currentDateTime = QDateTime::currentDateTime().toString().toStdString();
    std::string stateString = stateStringMap[state].toStdString();
    std::cout
        << currentDateTime
        << " "
        << stateString
        << std::endl;
}

