#include "activityserver.h"

#include <QNetworkReply>
#include <QSettings>

const QMap<ActivityState, QString> stateStringMap = {
    std::make_pair(ActivityState::Active, "active"),
    std::make_pair(ActivityState::Inactive, "inactive")
};

ActivityServer::ActivityServer(QObject *parent) : QObject(parent)
{

}

/**
 * @brief Performs the post request, as described in the ActivityServer class description.
 * @param state New user’s activity state
 */
void ActivityServer::updateActivityState(ActivityState state)
{
    // Build request
    QNetworkRequest request;
    request.setUrl(m_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Build request body
    QString requestBody = buildRequestQuery(state).toString();

    // Send the request
    QNetworkReply *reply = m_networkManager.post(request, requestBody.toLatin1());

    // Write warning if the request fails
    // ...The signal is extracted in the following way because the QNetworkReply::error() method is overloaded
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(logError(QNetworkReply::NetworkError)));
}

/**
 * @brief Sets the URL to perform the post request to.
 */
void ActivityServer::setUrl(QString url)
{
    m_url = url;
}

/**
 * @brief Sets the “computerId” field of the post request.
 */
void ActivityServer::setComputerId(QString computerId)
{
    m_computerId = computerId;
}

/**
 * @brief Sets the “secretKey” field of the post request.
 */
void ActivityServer::setSecretKey(QString secretKey)
{
    m_secretKey = secretKey;
}

/**
 * @brief Builds the post request body.
 */
QUrlQuery ActivityServer::buildRequestQuery(ActivityState state) const
{
    QUrlQuery query;
    query.addQueryItem("computerId", m_computerId);
    query.addQueryItem("secretKey", m_secretKey);
    query.addQueryItem("state", stateStringMap[state]);
    return query;
}

/**
 * @brief Logs the network errors to the console.
 */
void ActivityServer::logError(QNetworkReply::NetworkError error) const
{
    QString warningMessage = QString("ActivityServer: Got an error %1 while performing request.").arg(error);
    qWarning(qPrintable(warningMessage));
}

