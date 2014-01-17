#pragma once

#include <QString>
#include <QVariant>
#include "Item.h"

class Category : public Item
{
public:
	Category(void);

	virtual const QString data(const QString&) const;
	virtual bool setData(const QString&, const QString&);

	int id();
	QString name();
	void setId(int id){m_categoryId = id;}
	void setName(QString name){m_categoryName = name;}

public:
	~Category(void);

private:
	int m_categoryId;
	QString m_categoryName;
};
