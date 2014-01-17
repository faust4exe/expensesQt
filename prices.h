#ifndef PRICES_H
#define PRICES_H

#include "Items.h"
#include "Price.h"

class Prices : public Items
{
public:
	Prices();
	~Prices();

	void newPrice(int prodId, double price, QDate date = QDate::currentDate());
	void deletePricesOfProduct(int productId);

	int newId();
protected:
	virtual Item * newItem();

private:
	Price * getPrice(int prodId, QDate date);

private:
	
};

#endif // PRICES_H
