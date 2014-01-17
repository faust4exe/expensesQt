#include "Product.h"

Product::Product(void)
{
	parameters << "productId" << "categoryId" << "productName";
}

Product::~Product(void)
{
}

int Product::id()
{
	return m_productId;
}

QString Product::name()
{
	return m_productName;
}

int Product::categoryId()
{
	return m_categoryId;
}

const QString Product::data(const QString &name) const
{
	if (!parameters.contains(name))
		return QString();

	const int index = paramIndex(name);
	switch(index){
		case 0:
			return QString::number(m_productId);
			break;
		case 1:
			return QString::number(m_categoryId);
			break;
		case 2:
			return m_productName;
			break;
	}

	return QString();
}

bool Product::setData(const QString &name, const QString &value)
{
	if (!parameters.contains(name))
		return false;

	const int index = paramIndex(name);
	switch(index){
		case 0:
			m_productId = value.toInt();
			break;
		case 1:
			m_categoryId = value.toInt();
			break;
		case 2:
			m_productName = value;
			break;
	}

	return true;
}