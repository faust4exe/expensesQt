#include "products.h"

Products::Products()
	: Items()
{

}

Products::~Products()
{

}

Item * Products::newItem()
{
	Product * prod = new Product();
	return prod;
}

int Products::newId()
{
	if (itemsCount() == 0)
		return 1;
	else {
		Item * it = item(itemsCount()-1);
		Product *cat = dynamic_cast<Product *>(it);
		return (cat->id() + 1); 
	}
}

int Products::newProduct(QString newProdName, int catId)
{
	Product * prod = new Product();
	int newIndex = newId();

	prod->setId(newIndex);
	prod->setName(newProdName);
	prod->setCategoryId(catId);

	addItem(prod);
	return newIndex;
}

void Products::deleteProduct(int productId)
{
	for (int i=0; i<itemsCount(); i++) {
		Item *it = item(i);
		Product *prod = dynamic_cast<Product *>(it);
		if (!prod)
			continue;

		if (prod->id() == productId) {
			// removing item from list
			m_items.removeAll(it);

			delete it;
			return;
		}
	}
}