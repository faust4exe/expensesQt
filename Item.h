#pragma once

#include <QString>
#include <QStringList>
#include <QVariant>

static QString st_paramsSeparator = ";";
static QString st_dateFormat = "dd.MM.yyyy";

class Item
{
public:
    Item(void);
    virtual ~Item();

    virtual bool loadData(const QString&);
    virtual const QString saveData() const;

    virtual const QString data(const QString&) const = 0;
    virtual bool setData(const QString&, const QString&) = 0;

protected:
    int paramIndex(const QString&) const;

protected:
    QStringList parameters;
};
