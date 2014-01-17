#include "manager.h"

Manager::Manager(QObject *parent)
	: QObject(parent)
{
	createDataStorages();
	loadingDataStorages();
}

Manager::~Manager()
{
	saveingDataStorages();
}

void Manager::save()
{
	saveingDataStorages();
}


Manager *Manager::manager()
{
	if (!m_manager)
		m_manager = new Manager();
	return m_manager;
}

void Manager::createDataStorages()
{
	m_prices = new Prices();
	m_products = new Products();
	m_categories = new Categories();
	m_purchases = new Purchases();
}

void Manager::loadingDataStorages()
{
	m_prices->loadItems(pricesFile);
	m_products->loadItems(productsFile);
	m_categories->loadItems(categoriesFile);
	m_purchases->loadItems(purchasesFile);
}
 
void Manager::saveingDataStorages()
{
	m_prices->saveItems(pricesFile);
	m_products->saveItems(productsFile);
	m_categories->saveItems(categoriesFile);
	m_purchases->saveItems(purchasesFile);
}

QStringList Manager::categories()
{
	QStringList cats;
	for(int i=0;i<m_categories->itemsCount();i++){
		Item *it = m_categories->item(i);
		Category *cat = dynamic_cast<Category *>(it);
		if (!cat) 
			continue;

		cats << cat->name();
	}
	return cats;
}

int Manager::categoryId(QString catName)
{
	for(int i=0;i<m_categories->itemsCount();i++){
		Item *it = m_categories->item(i);
		Category *cat = dynamic_cast<Category *>(it);
		if (!cat)
			continue;

		if (cat->name() == catName)
			return cat->id();
	}
	return -1;
}

QString Manager::categoryName(int catId)
{
	for(int i=0;i<m_categories->itemsCount();i++){
		Item *it = m_categories->item(i);
		Category *cat = dynamic_cast<Category *>(it);
		if (!cat)
			continue;

		if (cat->id() == catId)
			return cat->name();
	}
        return "";
}

double Manager::expencesOnDate(QDate date)
{
	double sum = 0;

	QMap<int, double> map;

	for(int i=0;i<m_purchases->itemsCount();i++){
		Item *it = m_purchases->item(i);
		Purchase *purch = dynamic_cast<Purchase *>(it);
		if (!purch)
			continue;

		if (purch->date() != date)
			continue;

		int prodId = purch->id();

		double cantitaty = purch->cantitaty();
		// need price of product
		double price;
		if (map.contains(prodId))
			price = map.value(prodId);
		else { 
			price = priceOfProduct(purch->id());
			map.insert(prodId, price);
		}

		sum = sum + price * cantitaty;	
	}

	return sum;
}

double Manager::categoryExpences(QString categ, QDate minDateLimit)
{
	int categId = categoryId(categ);
	double sum = 0;

	QMap<int, double> map;

	// need to get products for category
	QList<int> productsIds = productsIdByCategory(categId);
	
	for(int i=0;i<m_purchases->itemsCount();i++){
		Item *it = m_purchases->item(i);
		Purchase *purch = dynamic_cast<Purchase *>(it);
		if (!purch)
			continue;

		if (!productsIds.contains(purch->id()))
			continue;

		if (!(purch->date() > minDateLimit))
			continue;

		int prodId = purch->id();

		double cantitaty = purch->cantitaty();
		// need price of product
		double price;
		if (map.contains(prodId))
			price = map.value(prodId);
		else { 
			price = priceOfProduct(purch->id());
			map.insert(prodId, price);
		}

		sum = sum + price * cantitaty;	
	}

	return sum;
}

double Manager::categoryExpencesOnDate(QString categ, QDate date)
{
	int categId = categoryId(categ);
	double sum = 0;

	QMap<int, double> map;

	// need to get products for category
	QList<int> productsIds = productsIdByCategory(categId);
	
	for(int i=0;i<m_purchases->itemsCount();i++){
		Item *it = m_purchases->item(i);
		Purchase *purch = dynamic_cast<Purchase *>(it);
		if (!purch)
			continue;

		if (!productsIds.contains(purch->id()))
			continue;

		if (purch->date() != date)
			continue;

		int prodId = purch->id();

		double cantitaty = purch->cantitaty();
		// need price of product
		double price;
		if (map.contains(prodId))
			price = map.value(prodId);
		else { 
			price = priceOfProduct(purch->id());
			map.insert(prodId, price);
		}

		sum = sum + price * cantitaty;	
	}

	return sum;
}

double Manager::productExpencesOnDate(QString prod, QDate date)
{
	double sum = 0;

	QMap<int, double> map;

	// need to get products for category
	int productsId = productId(prod);
	
	for(int i=0;i<m_purchases->itemsCount();i++){
		Item *it = m_purchases->item(i);
		Purchase *purch = dynamic_cast<Purchase *>(it);
		if (!purch)
			continue;

		if (productsId != purch->id())
			continue;

		if (purch->date() != date)
			continue;

		double cantitaty = purch->cantitaty();
		// need price of product
		double price = priceOfProduct(purch->id());

		sum = sum + price * cantitaty;	
	}

	return sum;
}

double Manager::productPriceOnDate(int prodId, QDate date)
{
	for(int i=0;i<m_prices->itemsCount();i++){
		Item *it = m_prices->item(i);
		Price *l_price = dynamic_cast<Price *>(it);
		if (!l_price)
			continue;

		if (l_price->idProd() != prodId)
			continue;

		if (l_price->date() != date)
			continue;

		return l_price->price();
	}
	return 0;
}

QList<QDate> Manager::productPriceDates(int prodId)
{
	QList<QDate> datesList;

	for(int i=0;i<m_prices->itemsCount();i++){
		Item *it = m_prices->item(i);
		Price *l_price = dynamic_cast<Price *>(it);
		if (!l_price)
			continue;

		if (l_price->idProd() != prodId)
			continue;

		datesList << l_price->date();
	}
	return datesList;
}

QStringList Manager::products()
{
	QStringList prods;
	for(int i=0;i<m_products->itemsCount();i++){
		Item *it = m_products->item(i);
		Product *prod = dynamic_cast<Product *>(it);
		if (!prod)
			continue;

		prods << prod->name();
	}
	return prods;
}

QStringList Manager::productsByCategory(int categ)
{
	QStringList prods;
	for(int i=0;i<m_products->itemsCount();i++){
		Item *it = m_products->item(i);
		Product *prod = dynamic_cast<Product *>(it);
		if (!prod)
			continue;

		if (categ == prod->categoryId())
			prods << prod->name();
	}
	return prods;
}

QList<int> Manager::productsIdByCategory(int categ)
{
	QList<int> prods;
	for(int i=0;i<m_products->itemsCount();i++){
		Item *it = m_products->item(i);
		Product *prod = dynamic_cast<Product *>(it);
		if (!prod)
			continue;

		if (categ == prod->categoryId())
			prods << prod->id();
	}
	return prods;
}

int Manager::productId(QString prodName)
{
	for(int i=0;i<m_products->itemsCount();i++){
		Item *it = m_products->item(i);
		Product *prod = dynamic_cast<Product *>(it);
		if (!prod)
			continue;

		if (prodName == prod->name())
			return prod->id();
	}

	return -1;
}

int Manager::productCategoryId(QString prodName)
{
	for(int i=0;i<m_products->itemsCount();i++){
		Item *it = m_products->item(i);
		Product *prod = dynamic_cast<Product *>(it);
		if (!prod)
			continue;

		if (prodName == prod->name())
			return prod->categoryId();
	}

	return -1;
}

double Manager::priceOfProduct(int prodId)
{
	double priceVal = 0;
	QDate lastDate(2000,1,1);

	for(int i=0;i<m_prices->itemsCount();i++){
		Item *it = m_prices->item(i);
		Price *l_price = dynamic_cast<Price *>(it);
		if (!l_price)
			continue;

		if (l_price->idProd() != prodId)
			continue;

		if (l_price->date() <= lastDate)
			continue;

		lastDate = l_price->date();
		priceVal = l_price->price();
	}
	return priceVal;
}

bool Manager::isUniqueCategoryName(const QString newCategoryName)
{
	int catId = categoryId(newCategoryName);
	// if name is new we will get -1 as Id
	if (catId == -1)
		return true;
	return false;
}

bool Manager::isUniqueProductName(const QString newProdName)
{
	int prodId = productId(newProdName);
	// if name is new we will get -1 as Id
	if (prodId == -1)
		return true;
	return false;
}

void Manager::addCategory(QString category)
{
	m_categories->newCategory(category);
	emit newCategory(category);
}

void Manager::deleteCategory(int categoryId)
{
	m_categories->deleteCategory(categoryId);
}

void Manager::deleteProduct(int productId)
{
	m_products->deleteProduct(productId);
	m_prices->deletePricesOfProduct(productId);
	m_purchases->deletePurchasesOfProduct(productId);
}

void Manager::addProduct(QString newProdName, QString categ, double price)
{
	int catId = categoryId(categ);
	int prodId = m_products->newProduct(newProdName, catId);
	m_prices->newPrice(prodId, price);

	emit newProduct(newProdName);
}

void Manager::addPrice(QString prodName, QString categ, double price, QDate date)
{
	const int prodId = productId(prodName);
	m_prices->newPrice(prodId, price, date);

	emit newPrice(prodName, price);
}

void Manager::addPurchase(QString prodName, double price, double cantitaty, QDate date)
{
	const int prodId = productId(prodName);
	m_purchases->newPurchase(prodId, cantitaty, date);

	emit newPurchase(prodName, cantitaty);
}
