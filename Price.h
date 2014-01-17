#pragma once

#include <QString>
#include <QVariant>
#include <QDate>
#include "Item.h"

class Price : public Item
{
public:
	Price(void);

	virtual const QString data(const QString&) const;
	virtual bool setData(const QString&, const QString&);
public:
	~Price(void);

	int idProd() const {return m_prodId;}
	double price() const {return m_priceValue;}
	QDate date() const {return m_priceDate;}

	void setIdProd(int prodId) {m_prodId = prodId;}
	void setPrice(double pr) {m_priceValue = pr;}
	void setDate(QDate dt) {m_priceDate = dt;}

private:
	int m_prodId;
	double m_priceValue;
	QDate m_priceDate;
};
