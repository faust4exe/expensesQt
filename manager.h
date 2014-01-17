#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "prices.h"
#include "categories.h"
#include "products.h"
#include "purchases.h"

static QString pricesFile = "data/prices.bin";
static QString productsFile = "data/prods.bin";
static QString purchasesFile = "data/purch.bin";
static QString categoriesFile = "data/categ.bin";

class Manager : public QObject
{
	Q_OBJECT

public:
	static Manager *manager();

	~Manager();

	void save();

	QStringList categories();
	int categoryId(QString);
	QString categoryName(int);
	double categoryExpences(QString categ, QDate minDateLimit);
	double categoryExpencesOnDate(QString categ, QDate date);

	double expencesOnDate(QDate date);

	QStringList products();
	QList<QDate> productPriceDates(int prodId);
	double productPriceOnDate(int prodId, QDate date);
	QStringList productsByCategory(int);
	QList<int> productsIdByCategory(int);
	int productId(QString);
	int productCategoryId(QString);
	double productExpencesOnDate(QString prod, QDate date);

	double priceOfProduct(int);

	void addCategory(const QString);
	void addProduct(QString, QString, double);
	void addPrice(QString prodName, QString categ, double price, QDate date = QDate::currentDate());
	void addPurchase(QString prodName, double price, double cantitaty, QDate date = QDate::currentDate());

	bool isUniqueCategoryName(const QString newCategoryName);
	bool isUniqueProductName(const QString newProdName);

	void deleteCategory(int categoryId);
	void deleteProduct(int productId);

Q_SIGNALS:
	void newCategory(QString);
	void newProduct(QString);
	void newPrice(QString,double);
	void newPurchase(QString,double);

private:
	Manager(QObject *parent = 0);

	void createDataStorages();
	void loadingDataStorages();
	void saveingDataStorages();

private:
	// data storages
	Prices * m_prices;
	Products * m_products;
	Categories * m_categories;
	Purchases * m_purchases;
	
};

static Manager *m_manager = 0;

#define qManager Manager::manager()

#endif // MANAGER_H
