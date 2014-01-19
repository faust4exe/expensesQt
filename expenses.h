#ifndef EXPENSES_H
#define EXPENSES_H

#include <QMainWindow>

#include "ui_expenses.h"

class eXpenses : public QMainWindow
{
	Q_OBJECT

public:
    eXpenses(QWidget *parent = 0);

	~eXpenses();

public Q_SLOTS:
	void close();

private Q_SLOTS:
	void onCategorySelected(const QString);
	void onCategoryAdded(const QString);
	void onProductSelected(const QString);
	void onProductAdded(QString);
	void onCantitatyChanged(double);
	void onPriceAdded(QString,QString,double);
	void newCategory();
	void newProduct();
	void newPrice();
	void deleteCategory();
	void deleteProduct();
	void onAddProductClicked();

	void showSummary();
	void showPrices();

	void init();

private:
	Ui::eXpensesClass ui;
};

#endif // EXPENSES_H
