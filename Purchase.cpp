#include "Purchase.h"

Purchase::Purchase(void)
{
	parameters << "productId" << "purchaseDate" << "purchaseCantitaty";
}

Purchase::~Purchase(void)
{
}

const QString Purchase::data(const QString &name) const
{
	if (!parameters.contains(name))
		return QString();

	const int index = paramIndex(name);
	switch(index){
		case 0:
			return QString::number(m_prodId);
			break;
		case 1:
			return m_purchaseDate.toString(st_dateFormat);
			break;
		case 2:
			return QString::number(m_purchaseCantity);
			break;
	}

	return QString();
}

bool Purchase::setData(const QString &name, const QString &value)
{
	if (!parameters.contains(name))
		return false;

	const int index = paramIndex(name);
	switch(index){
		case 0:
			m_prodId = value.toInt();
			break;
		case 1:
			m_purchaseDate = QDate::fromString(value, st_dateFormat);
			break;
		case 2:
			m_purchaseCantity = value.toDouble();
			break;
	}

	return true;
}