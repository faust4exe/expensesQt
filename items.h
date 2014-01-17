#ifndef ITEMS_H
#define ITEMS_H

#include <QFile>
#include <QTextStream>
#include <QList>
#include "Item.h"

class Items
{
public:
    Items();
	~Items();

    bool loadItems(const QString &filename);
	bool saveItems(const QString &filename);

	int itemsCount() const {return m_items.count();}
	Item * item(const int i) const {return m_items.at(i);}

protected:
	virtual Item * newItem() = 0;
	virtual int newId() = 0;

	bool createItem(const QString&);
	QString getItemData(const int);

	void addItem(Item *item) {m_items.append(item);}
	void deleteItem(Item *item);

protected:
	QList<Item*> m_items;
};

#endif // ITEMS_H
