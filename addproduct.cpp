#include "addproduct.h"

#include <QMessageBox>

#include "addcategory.h"
#include "Item.h"
#include "manager.h"

AddProduct::AddProduct(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.m_deDate->setDate(QDate::currentDate());
	ui.m_deDate->setDisplayFormat(st_dateFormat);

	QStringList cats = qManager->categories();
	ui.m_cbCategory->addItems(cats);
}

AddProduct::~AddProduct()
{

}

void AddProduct::onNewCategory()
{
	AddCategory * addCat = new AddCategory();
	connect (addCat, SIGNAL(addedCategory(QString)), SLOT(onCategoryAdded(QString)));
        addCat->show();//showMaximized();
}

void AddProduct::onCategoryAdded(QString category)
{	
	QStringList categ = qManager->categories();

	ui.m_cbCategory->clear();
	ui.m_cbCategory->addItems(categ);
	int index = ui.m_cbCategory->findText(category);
	ui.m_cbCategory->setCurrentIndex(index);
}

void AddProduct::setCategory(QString category)
{
	int index = ui.m_cbCategory->findText(category);
	ui.m_cbCategory->setCurrentIndex(index);
}

void AddProduct::accept()
{
	QString categ = ui.m_cbCategory->currentText();
	QString newProdName = ui.m_leNewProduct->text();
	double price = ui.m_dsbNewPrice->value();

	if (newProdName.isEmpty() || price == 0 || categ.isEmpty()) {
		QString message;
		if (newProdName.isEmpty())
			message = "Wrong Data : Product Name is Empty";
		else if (price == 0)
			message = "Wrong Data : Product Price is zero";

		else if (categ.isEmpty() == 0)
			message = "Wrong Data : Category Name is Empty";

		QMessageBox::critical(this, "Error", message);
		return;
	}

	if (!qManager->isUniqueProductName(newProdName)) {
		QString message = "Error : Product Name is existent.";
		QMessageBox::critical(this, "Error", message);
		return;
	}

	qManager->addProduct(newProdName, categ, price);

	emit addedProduct(newProdName, categ, price);

	QDialog::accept();
}

void AddProduct::onDeleteCategory()
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
	
	QStringList categ = qManager->categories();

	ui.m_cbCategory->clear();
	ui.m_cbCategory->addItems(categ);
	ui.m_cbCategory->setCurrentIndex(-1);
}
