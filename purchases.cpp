#include "purchases.h"

Purchases::Purchases()
	: Items()
{

}

Purchases::~Purchases()
{

}

Item * Purchases::newItem()
{
	Purchase * pur = new Purchase();
	return pur;
}

int Purchases::newId()
{
	return -1;
}

void Purchases::newPurchase(int prodId, double cantitaty, QDate date)
{
	Purchase * pur = new Purchase();

	pur->setIdProd(prodId);
	pur->setCantitaty(cantitaty);
	pur->setDate(date);

	addItem(pur);
}

void Purchases::deletePurchasesOfProduct(int productId)
{
	for(int i=0; i<itemsCount(); i++){
		Item *it = item(i);
		Purchase *purch = dynamic_cast<Purchase *>(it);
		if (!purch)
			continue;

		if (purch->id() == productId) {
			m_items.removeAll(it);
			delete it;
		}
	}
}