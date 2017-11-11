#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QVariantMap>
#include <QSharedPointer>

class Converter;
class QStringListModel;

class CustomModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CustomModel(QObject *parent = 0);

    Q_INVOKABLE void insertUnits(QString, QVariantMap);

    Q_INVOKABLE void setupModel();

    Q_INVOKABLE QString doCalculation(QString, QString) const;

    Q_INVOKABLE QString stripHTMLtags(QString) const;

    Q_INVOKABLE void updateCurrencies(QVariantMap);

    Q_INVOKABLE void filterModel(QString);

    Q_INVOKABLE bool isModelPopulated() const;

protected:
    QVariantMap unitdata;
    QStringListModel *_model;
    QSharedPointer<Converter> conv;
};

#endif // CUSTOMMODEL_H
