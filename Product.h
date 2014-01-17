#pragma once

#include <QString>
#include <QVariant>
#include "Item.h"

class Product : public Item
{
public:
	Product(void);

	virtual const QString data(const QString&) const;
	virtual bool setData(const QString&, const QString&);
public:
	~Product(void);

	int id();
	QString name();
	int categoryId();

	void setId(int id){m_productId = id;}
	void setName(QString name){m_productName = name;}
	void setCategoryId(int categId){m_categoryId = categId;}

private:
	int m_productId;
	int m_categoryId;
	QString m_productName;
};
