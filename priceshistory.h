#ifndef PRICESHISTORY_H
#define PRICESHISTORY_H

#include <QDialog>
#include "manager.h"
#include "ui_priceshistory.h"

class PricesHistory : public QDialog
{
	Q_OBJECT

public:
	PricesHistory(QWidget *parent = 0);
	~PricesHistory();

private Q_SLOTS:
	void onProductSelected(QString prodName);
	void onCategotyChange(QString category);

private:
	void init();

private:
	Ui::PricesHistory ui;
};

#endif // PRICESHISTORY_H
