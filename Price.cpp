#include "Price.h"

Price::Price(void)
{
	parameters << "idProd" << "priceDate" << "priceValue";
}

Price::~Price(void)
{
}

const QString Price::data(const QString &name) const
{
	if (!parameters.contains(name))
		return QString();

	const int index = paramIndex(name);
	switch(index){
		case 0:
			return QString::number(m_prodId);
			break;
		case 1:
			return m_priceDate.toString(st_dateFormat);
			break;
		case 2:
			return QString::number(m_priceValue);
			break;
	}

	return QString();
}

bool Price::setData(const QString &name, const QString &value)
{
	if (!parameters.contains(name))
		return false;

	const int index = paramIndex(name);
	switch(index){
		case 0:
			m_prodId = value.toInt();
			break;
		case 1:
			m_priceDate = QDate::fromString(value, st_dateFormat);
			break;
		case 2:
			m_priceValue = value.toDouble();
			break;
	}

	return true;
}

