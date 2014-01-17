#include "addcategory.h"

AddCategory::AddCategory(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

AddCategory::~AddCategory()
{

}

void AddCategory::accept()
{
	const QString newCategoryName = ui.m_leNewName->text();

	if (newCategoryName.isEmpty()) {
		QString message = "Wrong Data : Category Name is Empty";

		QMessageBox::critical(this, "Error", message);
		return;
	}

	if (!qManager->isUniqueCategoryName(newCategoryName)) {
		QString message = "Error : Category Name is existent.";
		QMessageBox::critical(this, "Error", message);
		return;
	}

	qManager->addCategory(newCategoryName);

	emit addedCategory(newCategoryName);

	QDialog::accept();
}

