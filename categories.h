#ifndef CATEGORIES_H
#define CATEGORIES_H

#include "Items.h"
#include "Category.h"

class Categories : public Items
{
public:
	Categories();
	~Categories();

	int newCategory(QString);

	void deleteCategory(int);

	int newId();
protected:
	virtual Item * newItem();

private:
	
};

#endif // CATEGORIES_H
