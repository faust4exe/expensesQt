#include "expenses.h"

#include <QMessageBox>

#include "Item.h"
#include "addcategory.h"
#include "addproduct.h"
#include "addprice.h"
#include "manager.h"
#include "summary.h"
#include "priceshistory.h"

eXpenses::eXpenses(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);

	// set current date
	ui.m_deDate->setDate(QDate::currentDate());
	ui.m_deDate->setDisplayFormat(st_dateFormat);

	init();

	connect(qManager, SIGNAL(newCategory(QString)), SLOT(onCategoryAdded(QString)));
	connect(qManager, SIGNAL(newProduct(QString)), SLOT(onProductAdded(QString)));
}

eXpenses::~eXpenses()
{
}

void eXpenses::init()
{
	// test init
	QStringList categ = qManager->categories();

	ui.m_cbCategory->clear();
	ui.m_cbCategory->addItems(categ);
	ui.m_cbCategory->setCurrentIndex(-1);

	ui.m_cbProduct->clear();

	ui.m_dsbPrice->setValue(0); 
	ui.m_dsbCantitaty->setValue(0);
	ui.m_dsbTotalPrice->setValue(0);
}

void eXpenses::onCategorySelected(const QString category)
{
	// get category id from name
	const int categoryId = qManager->categoryId(category);

	// need to get products for respective category
	const QStringList products = qManager->productsByCategory(categoryId);

	ui.m_cbProduct->clear();
	ui.m_cbProduct->addItems(products);
	ui.m_cbProduct->setCurrentIndex(-1);

	ui.m_dsbPrice->setValue(0); 
	ui.m_dsbCantitaty->setValue(0);
	ui.m_dsbTotalPrice->setValue(0);
}

void eXpenses::onCategoryAdded(const QString category)
{	
	QStringList categ = qManager->categories();

	ui.m_cbCategory->clear();
	ui.m_cbCategory->addItems(categ);
	int index = ui.m_cbCategory->findText(category);
	ui.m_cbCategory->setCurrentIndex(index);

	ui.m_cbProduct->clear();
	ui.m_dsbPrice->setValue(0); 
	ui.m_dsbCantitaty->setValue(0);
	ui.m_dsbTotalPrice->setValue(0);
}

void eXpenses::onProductSelected(const QString product)
{
	// get product id from name
	const int productId = qManager->productId(product);

	// need to get last price for product
	const double price = qManager->priceOfProduct(productId);
	double cantity = 1;

	// set price for product
	ui.m_dsbPrice->setValue(price); 

	// set default cantitaty , MAYBE last one ?
	ui.m_dsbCantitaty->setValue(cantity); // DOES this call for next slot ? adm we DIDNT need the next setting ?

	// set total price of perchase
	ui.m_dsbTotalPrice->setValue(price * cantity);
}

void eXpenses::onProductAdded(QString newProd)
{
	int categId = qManager->productCategoryId(newProd);
	QString categ = qManager->categoryName(categId);
	QStringList categories = qManager->categories();

	ui.m_cbCategory->clear();
	ui.m_cbCategory->addItems(categories);
	int indexC = ui.m_cbCategory->findText(categ);
	ui.m_cbCategory->setCurrentIndex(indexC);

	const QStringList products = qManager->productsByCategory(categId);

	int productId = qManager->productId(newProd);
	ui.m_cbProduct->clear();
	ui.m_cbProduct->addItems(products);
	int indexP = ui.m_cbProduct->findText(newProd);
	ui.m_cbProduct->setCurrentIndex(indexP);

	double price = qManager->priceOfProduct(productId);

	// set new price
	ui.m_dsbPrice->setValue(price);

	ui.m_dsbCantitaty->setValue(1); // DOES this call for next slot ? adm we DIDNT need the next setting ?

	// set total price of perchase
	ui.m_dsbTotalPrice->setValue(price);
}

void eXpenses::onPriceAdded(QString newProd, QString categ, double value)
{
	QStringList categories = qManager->categories();

	ui.m_cbCategory->clear();
	ui.m_cbCategory->addItems(categories);
	int indexC = ui.m_cbCategory->findText(categ);
	ui.m_cbCategory->setCurrentIndex(indexC);

	const int categoryId = qManager->categoryId(categ);
	const QStringList products = qManager->productsByCategory(categoryId);

	ui.m_cbProduct->clear();
	ui.m_cbProduct->addItems(products);
	int indexP = ui.m_cbProduct->findText(newProd);
	ui.m_cbProduct->setCurrentIndex(indexP);

	// set new price
	ui.m_dsbPrice->setValue(value);

	ui.m_dsbCantitaty->setValue(1); // DOES this call for next slot ? adm we DIDNT need the next setting ?

	// set total price of perchase
	ui.m_dsbTotalPrice->setValue(value);
}

void eXpenses::onCantitatyChanged(const double cantitaty)
{
	// get price for unit of product
	const double price = ui.m_dsbPrice->value();

	// set total price of perchase
	ui.m_dsbTotalPrice->setValue(price * cantitaty);
}

void eXpenses::newCategory()
{
	AddCategory * addCat = new AddCategory();
	//connect (addCat, SIGNAL(addedCategory(QString)), SLOT(onCategoryAdded(QString)));
        addCat->show();//showMaximized();
}

void eXpenses::newProduct()
{
	//QMessageBox::information ( this, "newProduct", "Here we Will Create New Product");
	AddProduct * addProd = new AddProduct();
	addProd->setCategory(ui.m_cbCategory->currentText());
        addProd->show();//showMaximized();
}

void eXpenses::newPrice()
{
	AddPrice * addPrice = new AddPrice();
	addPrice->setParams(ui.m_cbCategory->currentText(), 
		ui.m_cbProduct->currentText());
	connect (addPrice, SIGNAL(addedPrice(QString, QString, double)), SLOT(onPriceAdded(QString,QString,double)));
        addPrice->show();//showMaximized();
}

void eXpenses::onAddProductClicked()
{
	QString prodName = ui.m_cbProduct->currentText();
	double price = ui.m_dsbPrice->value();
	double cantitaty = ui.m_dsbCantitaty->value();
	QDate date = ui.m_deDate->date();

	if (prodName.isEmpty() || price == 0 || cantitaty == 0) {
		QString message;
		if (prodName.isEmpty())
			message = "Wrong Data : Product Name is Empty";
		else if (price == 0)
			message = "Wrong Data : Product Price is zero";
		else if (cantitaty == 0)
			message = "Wrong Data : Product Cantitaty is zero";

		QMessageBox::critical(this, "Error", message);
		return;
	}

	qManager->addPurchase(prodName, price, cantitaty, date);

	QMessageBox::information ( this, "New Purchase", "Information about new Purchase added.");

	init();
}

void eXpenses::close()
{
	qManager->save();
	QMainWindow::close();
}

void eXpenses::showSummary()
{
	Summary * sum = new Summary();
        sum->show();//showMaximized();
}

void eXpenses::showPrices()
{
	PricesHistory * hyst = new PricesHistory();
        hyst->show();//showMaximized();
}

void eXpenses::deleteCategory()
{
	QString categoryName = ui.m_cbCategory->currentText();
	int categoryId = qManager->categoryId(categoryName);

	if (categoryName.isEmpty() || categoryId == 0) {
		QString message;
		if (categoryName.isEmpty())
			message = "Wrong Data : Category Name is Empty";
		else if (categoryId == 0)
			message = "Wrong Data : Category is nonexistent";

		QMessageBox::critical(this, "Error", message);
		return;
	}

	qManager->deleteCategory(categoryId);
	init();
}

void eXpenses::deleteProduct()
{
	QString prodName = ui.m_cbProduct->currentText();
	int prodId = qManager->categoryId(prodName);

	if (prodName.isEmpty() || prodId == 0) {
		QString message;
		if (prodName.isEmpty())
			message = "Wrong Data : Product Name is Empty";
		else if (prodId == 0)
			message = "Wrong Data : Product is nonexistent";

		QMessageBox::critical(this, "Error", message);
		return;
	}

	qManager->deleteProduct(prodId);
	init();
}
