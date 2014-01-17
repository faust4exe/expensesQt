#include "prices.h"

Prices::Prices()
	: Items()
{

}

Prices::~Prices()
{

}

Item * Prices::newItem()
{
	Price * p = new Price();
	return p;
}

int Prices::newId()
{
	return -1;
}

void Prices::newPrice(int prodId, double price, QDate date)
{
	// lets check if price is existing for product for current day
	Price * oldPrice = getPrice(prodId, date);
	if (oldPrice) {
		oldPrice->setPrice(price);
		return;
	}

	Price * pr = new Price();

	pr->setIdProd(prodId);
	pr->setPrice(price);
	pr->setDate(date);

	addItem(pr);
}

void Prices::deletePricesOfProduct(int productId)
{
	for(int i=0;i<itemsCount();i++){
		Item *it = item(i);
		Price *price = dynamic_cast<Price *>(it);
		if (!price)
			continue;

		if (price->idProd() == productId) {
			m_items.removeAll(it);
			delete it;
		}
	}
}

Price * Prices::getPrice(int prodId, QDate date)
{
	for(int i=0;i<itemsCount();i++){
		Item *it = item(i);
		Price *l_price = dynamic_cast<Price *>(it);
		if (!l_price)
			continue;

		if ((l_price->idProd() == prodId) 
			&& (l_price->date() == date))
			return l_price;
	}

	return 0;
}