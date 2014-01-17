#include "items.h"

Items::Items()
{
}

Items::~Items()
{
}

bool Items::loadItems(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        createItem(line);
    }

	file.close();
	return true;
}

bool Items::saveItems(const QString &filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return false;

	QTextStream out(&file);
	for (int i=0; i< itemsCount(); i++){
		const QString line = getItemData(i);
		out << line;
		if (i != itemsCount()-1)
			out << "\n";
	}

	file.close();
	return true;
}

bool Items::createItem(const QString &data)
{
	Item * item = newItem();
	const bool ok = item->loadData(data);
	if (ok)
		addItem(item);
	else
		delete item;

	return ok;
}

QString Items::getItemData(const int i)
{
	const Item * it = item(i);
	const QString dt = it->saveData();
	return dt;
}

void Items::deleteItem(Item *item)
{
	m_items;
}
