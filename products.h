#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "Items.h"
#include "Product.h"

class Products : public Items
{
public:
	Products();
	~Products();

	int newProduct(QString newProdName, int catId);
	void deleteProduct(int productId);

	int newId();

protected:
	virtual Item * newItem();

private:
	
};

#endif // PRODUCTS_H
