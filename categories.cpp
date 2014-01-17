#include "categories.h"

Categories::Categories()
	: Items()
{

}

Categories::~Categories()
{

}

Item * Categories::newItem()
{
	Category * cat = new Category();
	return cat;
}

int Categories::newId()
{
	if (itemsCount() == 0)
		return 1;
	else {
		Item * it = item(itemsCount()-1);
		Category *cat = dynamic_cast<Category *>(it);
		return (cat->id() + 1); 
	}
}	

int Categories::newCategory(QString categoryName)
{
	Category * cat = new Category();
	int newIndex = newId();
	cat->setId(newIndex);
	cat->setName(categoryName);
	addItem(cat);
	return newIndex;
}

void Categories::deleteCategory(int categId)
{
	for (int i=0; i<itemsCount(); i++) {
		Item *it = item(i);
		Category *cat = dynamic_cast<Category *>(it);
		if (!cat)
			continue;

		if (cat->id() == categId) {
			// removing item from list
			m_items.removeAll(it);

			delete it;
			return;
		}
	}
}
