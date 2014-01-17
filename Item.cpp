#include "Item.h"

Item::Item(void)
{
}

Item::~Item(void)
{
}

bool Item::loadData(const QString &data)
{
	const QStringList params = data.split(st_paramsSeparator);
	if (params.count() != parameters.count())
		return false;

	foreach(QString paramName, parameters){
		const int index = paramIndex(paramName);
		const QString paramValue = params.at(index);
		const bool isOk = setData(paramName, paramValue);

		if (!isOk)
			return false;
	}

	return true;
}

const QString Item::saveData() const
{
	QStringList params;

	foreach(QString paramName, parameters){
		const int index = paramIndex(paramName);

		const QString paramValue = data(paramName);

		params << paramValue;
	}

	return params.join(st_paramsSeparator);
}

int Item::paramIndex(const QString &paramName) const
{
	return parameters.indexOf(paramName);
}