#ifndef PURCHASES_H
#define PURCHASES_H

#include "Items.h"
#include "Purchase.h"

class Purchases : public Items
{
public:
	Purchases();
	~Purchases();

	int newId();

	void newPurchase(int prodId, double cantitaty, QDate date = QDate::currentDate());
	void deletePurchasesOfProduct(int productId);

protected:
	virtual Item * newItem();

private:
	
};

#endif // PURCHASES_H
