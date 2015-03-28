#ifndef ACTIVITYLOGGER_H
#define ACTIVITYLOGGER_H

#include <QObject>
#include "common.h"

/**
 * @brief The ActivityLogger class logs the user’s activity changes.
 * The activity changes are provided by calling logActivityState() method.
 */
class ActivityLogger : public QObject
{
    Q_OBJECT
public:
    explicit ActivityLogger(QObject *parent = 0);

public slots:
    void updateActivityState(ActivityState state) const;
};

#endif // ACTIVITYLOGGER_H
