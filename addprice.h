#ifndef ADDPRICE_H
#define ADDPRICE_H

#include <QDialog>
#include <QDate>
#include <QMessageBox>
#include "Item.h"
#include "addcategory.h"
#include "addproduct.h"
#include "ui_addprice.h"

class AddPrice : public QDialog
{
	Q_OBJECT

public:
	AddPrice(QWidget *parent = 0);
	~AddPrice();

	void setParams(QString, QString);

public Q_SLOTS:
	void accept();


Q_SIGNALS:
	void addedPrice(QString, QString, double);

private Q_SLOTS:
	void onCategoryChanged(QString);
	void onCategoryAdded(const QString category);
	void onProductChanged(QString);
	void onProductAdded(QString newProd, QString categ, double value);
	void onNewCategory();
	void onNewProduct();

private:
	void init();
private:
	Ui::AddPrice ui;
};

#endif // ADDPRICE_H
