#include "Category.h"

Category::Category(void)
{
	parameters << "idCategory" << "categoryName";
}

Category::~Category(void)
{
}

int Category::id()
{
	return m_categoryId;
}

QString Category::name()
{
	return m_categoryName;
}

const QString Category::data(const QString &name) const
{
	if (!parameters.contains(name))
		return QString();

	const int index = paramIndex(name);
	switch(index){
		case 0:
			return QString::number(m_categoryId);
			break;
		case 1:
			return m_categoryName;
			break;
	}

	return QString();
}

bool Category::setData(const QString &name, const QString &value)
{
	if (!parameters.contains(name))
		return false;

	const int index = paramIndex(name);
	switch(index){
		case 0:
			m_categoryId = value.toInt();
			break;
		case 1:
			m_categoryName = value;
			break;
	}

	return true;
}
