#include "currencycache.h"

#include <QDate>
#include <QDebug>

const QUrl CurrencyCache::URL("http://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml");

CurrencyCache::CurrencyCache(QObject *parent) :
    QObject(parent),
    _xml(),
    _interval(),
    _settings(),
    _manager()
{
    _xml = _settings.value("xml", "").toString();
    _interval = static_cast<UpdateInterval>(_settings.value("interval", UpdateInterval::DAILY).toInt());

    QObject::connect(&_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getReply(QNetworkReply*)));

    checkUpdate();
}

QString CurrencyCache::XML()
{
    return _xml;
}

void CurrencyCache::setXML(QString xml)
{
    _xml = xml;
    _settings.setValue("xml", _xml);
    emit xmlChanged(_xml);
}

void CurrencyCache::checkUpdate()
{
    if(_xml == "" && _interval != NEVER)
    {
        updateNow();
        return;
    }
    qlonglong current_time = QDate::currentDate().toJulianDay();
    qlonglong last_update = _settings.value("update", 0).toLongLong();
    switch (_interval)
    {
    case DAILY:
        if(current_time - last_update >= 1)
        {
            updateNow();
        }
        break;
    case WEEKLY:
        if(current_time - last_update >= 7)
        {
            updateNow();
        }
        break;
    case MONTHLY:
        if(current_time - last_update >= 30)
        {
            updateNow();
        }
        break;
    case ALWAYS:
        updateNow();
        break;
    case NEVER:
        break;
    default:
        qDebug() << "Unknown update rate" << _interval;
        break;
    }
}

void CurrencyCache::updateNow()
{
    qDebug() << "Sending request for xml";

    QNetworkRequest request(URL);
    _manager.get(request);
}

CurrencyCache::UpdateInterval CurrencyCache::interval()
{
    return _interval;
}

void CurrencyCache::setInterval(CurrencyCache::UpdateInterval interval)
{
    _interval = interval;
    _settings.setValue("interval", interval);
    checkUpdate();;
}

void CurrencyCache::getReply(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Error while downloading xml:" << reply->errorString();
        return;
    }

    qDebug() << "Updating xml";

    setXML(reply->readAll());
    reply->deleteLater();
    _settings.setValue("update", QDate::currentDate().toJulianDay());
}
