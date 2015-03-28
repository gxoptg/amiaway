#ifndef COMMON_H
#define COMMON_H

// Includes are provided for stateStringMap.
#include <QMap>
#include <QString>
#include <utility>

/**
 * @brief The ActivityState enum represents the user’s activity state.
 * See ActivityMonitor class for more information about how states are set.
 */
enum class ActivityState { Inactive, Active };

/** @brief Maps activity states to their string names */
const QMap<ActivityState, QString> STATE_STRING_MAP = {
    std::make_pair(ActivityState::Active, "active"),
    std::make_pair(ActivityState::Inactive, "inactive")
};


#endif // COMMON_H

