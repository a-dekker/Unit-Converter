#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>

class Logic : public QObject
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent = 0);

    Q_INVOKABLE QString getVersion() const;
};

#endif // LOGIC_H
