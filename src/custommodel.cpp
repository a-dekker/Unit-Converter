#include <QStringList>
#include <QStringListModel>
#include "custommodel.h"
#include "converter.h"

CustomModel::CustomModel(QObject *parent)
    : QSortFilterProxyModel(parent), _model(new QStringListModel(this))
{
    conv = QSharedPointer<Converter>(new Converter{});
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void CustomModel::insertUnits(QString type, QVariantMap map_)
{
    if (!map_.isEmpty())
        unitdata[type] = map_;
}

void CustomModel::setupModel()
{
    auto iter = unitdata.constBegin();
    QStringList tmp;
    while (iter != unitdata.constEnd()) {
        QVariantMap map = iter.value().toMap();
        auto iter_2 = map.constBegin();
        while (iter_2 != map.constEnd()) {
            tmp.append(iter_2.key());
            ++iter_2;
        }
        ++iter;
    }
    _model->setStringList(tmp);
    setSourceModel(_model);
}

QString CustomModel::doCalculation(QString unit1, QString unit2) const
{
    auto iter = unitdata.constBegin();
    QString from = "";
    QString to = "";
    QString unittype = "";
    while (iter != unitdata.constEnd()) {
        QVariantMap map = iter.value().toMap();
        auto iter_2 = map.constBegin();
        while (iter_2 != map.constEnd()) {
            if (iter_2.key() == unit1) {
                from = iter_2.value().toString();
            } else if (iter_2.key() == unit2) {
                to = iter_2.value().toString();
            }
            ++iter_2;
        }
        if (!from.isEmpty() && !to.isEmpty()) {
            unittype = iter.key();
            break;
        } else if (!from.isEmpty() || !to.isEmpty()) {
            break;
        }
        ++iter;
    }
    if (!unittype.isEmpty() && !from.isEmpty() && !to.isEmpty()) {
        if (unittype.toUpper() == "NUMBERS") {
            return conv->convert2Numbers(from, to, "1");
        } else {
            return conv->convert2(from, to, "1", unittype.toUpper());
        }
    } else {
        return QString::number(-1e30);
    }
}

QString CustomModel::stripHTMLtags(QString str) const
{
    return str.remove(QRegExp("<[^>]*>"));
}

void CustomModel::updateCurrencies(QVariantMap cur)
{
    if (!cur.isEmpty()) {
        conv->getCurrencies(cur);
    }
}

void CustomModel::filterModel(QString unit)
{
    QStringList tmp;
    QVariantMap map = unitdata.find(unit.toLower()).value().toMap();
    auto iter = map.constBegin();
    while (iter != map.constEnd()) {
        tmp.append(iter.key());
        ++iter;
    }
    _model->setStringList(tmp);
    setSourceModel(_model);
}

bool CustomModel::isModelPopulated() const { return _model->rowCount() > 0; }
