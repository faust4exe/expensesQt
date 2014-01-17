#pragma once

#include <QString>
#include <QVariant>
#include <QDate>
#include "Item.h"

class Purchase : public Item
{
public:
	Purchase(void);

	virtual const QString data(const QString&) const;
	virtual bool setData(const QString&, const QString&);

	int id() {return m_prodId;}
	double cantitaty() {return  m_purchaseCantity;}
	QDate date() {return m_purchaseDate;}

	void setIdProd(int prodId) {m_prodId = prodId;}
	void setCantitaty(double cantitaty) { m_purchaseCantity = cantitaty;}
	void setDate(QDate date) {m_purchaseDate = date;}

public:
	~Purchase(void);

private:
	int m_prodId;
	double m_purchaseCantity;
	QDate m_purchaseDate;
};
