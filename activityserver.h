#ifndef ACTIVITYSERVER_H
#define ACTIVITYSERVER_H

#include <QNetworkAccessManager>
#include <QObject>
#include <QUrlQuery>
#include <QNetworkReply>
#include "common.h"

/**
 * @brief The ActivityServer class sends the user’s activity updates to a server.
 * On each call to updateActivityState() method, the class performs the post request
 * to an url previously specified by setUrl().
 * The post request body looks like the following:
 * computerId=<a computer id set by setComputerId()>&secretKey=<a secret key set by setSecretKey()>&state=<(active|inactive)>
 *
 * The computer id could be used to distinguish several devises from each other.
 * The secret key could be used to prevent unathorized access.
 */
class ActivityServer : public QObject
{
    Q_OBJECT
public:
    explicit ActivityServer(QObject *parent = 0);

public slots:
    void updateActivityState(ActivityState state);

    void setUrl(QString url);
    void setComputerId(QString computerId);
    void setSecretKey(QString secretKey);

private /*methods*/:
    QUrlQuery buildRequestQuery(ActivityState state) const;

private slots:
    void logError(QNetworkReply::NetworkError error) const;

private /*variables*/:
    QString m_url;
    QString m_computerId;
    QString m_secretKey;

    QNetworkAccessManager m_networkManager;
};

#endif // ACTIVITYSERVER_H
