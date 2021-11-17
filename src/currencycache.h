#ifndef CURRENCYCACHE_H
#define CURRENCYCACHE_H

#include <QObject>
#include <QString>
#include <QSettings>
#include <QStandardPaths>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

class CurrencyCache : public QObject
{
    Q_OBJECT
    Q_ENUMS(UpdateInterval)

    Q_PROPERTY(QString xml READ XML WRITE setXML NOTIFY xmlChanged)
public:
    explicit CurrencyCache(QObject *parent = 0);

    enum UpdateInterval {
        DAILY = 0,
        WEEKLY = 1,
        MONTHLY = 2,
        ALWAYS = 3,
        NEVER = 4
    };

    Q_INVOKABLE QString XML();
    Q_INVOKABLE void setXML(QString xml);
    Q_INVOKABLE void checkUpdate();
    Q_INVOKABLE void updateNow();
    Q_INVOKABLE UpdateInterval interval();
    Q_INVOKABLE void setInterval(UpdateInterval interval);

signals:
    void xmlChanged(QString xml);

private slots:
    void getReply(QNetworkReply *reply);

private:
    static const QUrl URL;

    QString _xml;
    UpdateInterval _interval;
    QSettings *_settings;
    QNetworkAccessManager _manager;
    void showNotification(QString body, QString summary);
    void removeNotification();

    quint32 m_notificationId = 0;
};

#endif // CURRENCYCACHE_H
