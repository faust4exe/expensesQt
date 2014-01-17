#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>
#include "addcategory.h"
#include "Item.h"
#include "ui_addproduct.h"

class AddProduct : public QDialog
{
	Q_OBJECT

public:
	AddProduct(QWidget *parent = 0);
	~AddProduct();

	void setCategory(QString);

public Q_SLOTS:
	void accept();
	void onDeleteCategory();

Q_SIGNALS:
	void addedProduct(QString,QString,double);

private Q_SLOTS:
	void onNewCategory();
	void onCategoryAdded(QString category);

private:
	Ui::AddProduct ui;
};

#endif // ADDPRODUCT_H
