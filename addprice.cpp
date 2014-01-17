#include "addprice.h"

AddPrice::AddPrice(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.m_deDate->setDate(QDate::currentDate());
	ui.m_deDate->setDisplayFormat(st_dateFormat);

	init();
}

AddPrice::~AddPrice()
{

}

void AddPrice::init()
{
	// test init
	QStringList categ = qManager->categories();

	ui.m_cbCategory->clear();
	ui.m_cbCategory->addItems(categ);
	ui.m_cbCategory->setCurrentIndex(-1);

	ui.m_cbProduct->clear();

	//ui.m_dsbPrice->setValue(0); 
	//ui.m_dsbCantitaty->setValue(0);
	//ui.m_dsbTotalPrice->setValue(0);
}

void AddPrice::onCategoryChanged(QString category)
{
	// get category id from name
	const int categoryId = qManager->categoryId(category);

	// need to get products for respective category
	const QStringList products = qManager->productsByCategory(categoryId);

	ui.m_cbProduct->clear();
	ui.m_cbProduct->addItems(products);
	ui.m_cbProduct->setCurrentIndex(-1);
}
void AddPrice::onProductChanged(QString product)
{
	// get product id from name
	const int productId = qManager->productId(product);

	// need to get last price for product
	const double price = qManager->priceOfProduct(productId);
	double cantity = 1;

	// set price for product
	ui.m_dsbOldPrice->setValue(price); 
}

void AddPrice::setParams(QString categ, QString product)
{
	int catInd = ui.m_cbCategory->findText(categ);
	ui.m_cbCategory->setCurrentIndex(catInd);

	const int categoryId = qManager->categoryId(categ);

	// need to get products for respective category
	const QStringList products = qManager->productsByCategory(categoryId);
	ui.m_cbProduct->clear();
	ui.m_cbProduct->addItems(products);

	int prodInd = ui.m_cbProduct->findText(product);
	ui.m_cbProduct->setCurrentIndex(prodInd);

	// get product id from name
	const int productId = qManager->productId(product);

	// need to get last price for product
	const double price = qManager->priceOfProduct(productId);

	// set price for product
	ui.m_dsbOldPrice->setValue(price); 
}

void AddPrice::onNewCategory()
{
	AddCategory * addCat = new AddCategory();
	connect (addCat, SIGNAL(addedCategory(QString)), SLOT(onCategoryAdded(QString)));
        addCat->show();//showMaximized();
}

void AddPrice::onNewProduct()
{
	AddProduct * addProd = new AddProduct();
	addProd->setCategory(ui.m_cbCategory->currentText());
	connect (addProd, SIGNAL(addedProduct(QString,QString,double)), SLOT(onProductAdded(QString,QString,double)));
        addProd->show();//showMaximized();
}

void AddPrice::accept()
{
	QString categ = ui.m_cbCategory->currentText();
	QString prodName = ui.m_cbProduct->currentText();
	double price = ui.m_dsbNewPrice->value();
	QDate date = ui.m_deDate->date();

	if (prodName.isEmpty() || price == 0 || categ.isEmpty()) {
		QString message;
		if (prodName.isEmpty())
			message = "Wrong Data : Product Name is Empty";
		else if (price == 0)
			message = "Wrong Data : Product Price is zero";
		else if (categ.isEmpty())
			message = "Wrong Data : Category Name is Empty";

		QMessageBox::critical(this, "Error", message);
		return;
	}

	qManager->addPrice(prodName, categ, price, date);

	emit addedPrice(prodName, categ, price);

	QDialog::accept();
}

void AddPrice::onCategoryAdded(const QString category)
{	
	QStringList categ = qManager->categories();

	ui.m_cbCategory->clear();
	ui.m_cbCategory->addItems(categ);
	int index = ui.m_cbCategory->findText(category);
	ui.m_cbCategory->setCurrentIndex(index);

	ui.m_cbProduct->clear();
	ui.m_dsbOldPrice->setValue(0); 
	ui.m_dsbNewPrice->setValue(0);
}

void AddPrice::onProductAdded(QString newProd, QString categ, double value)
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
	//ui.m_dsbPrice->setValue(value);

	//ui.m_dsbCantitaty->setValue(1); // DOES this call for next slot ? adm we DIDNT need the next setting ?

	// set total price of perchase
	//ui.m_dsbTotalPrice->setValue(value);

	ui.m_dsbOldPrice->setValue(0); 
	ui.m_dsbNewPrice->setValue(value);
}
