#include <QScopedPointer>
#include <QStringList>
#include <QProcess>
#include <QString>
#include <QRegExp>
#include "logic.h"

Logic::Logic(QObject *parent) : QObject(parent) {}

QString Logic::getVersion() const
{
    QScopedPointer<QObject> parent(new QObject(nullptr));
    QScopedPointer<QProcess> rpm(new QProcess(parent.data()));
    QStringList args;
    args << "-qa"
         << "--queryformat"
         << "'%{name}-%{version}-%{release}\n'";
    rpm->start("rpm", args);
    if (!rpm->waitForStarted()) {
        return QString();
    }
    if (!rpm->waitForFinished()) {
        return QString();
    }
    QString rpms(rpm->readAll());
    QString packageName = "harbour-unitconverter";
    if (rpms.contains(packageName, Qt::CaseInsensitive)) {
        QRegExp rx(packageName + "-" + "(\\d+\\.\\d+)");
        rx.setCaseSensitivity(Qt::CaseInsensitive);
        int pos = rx.indexIn(rpms);
        if (pos > -1) {
            return rx.cap(1);
        }
    }
    return QString();
}
