#include "priceshistory.h"

PricesHistory::PricesHistory(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	init();

	connect (ui.m_cbCategory, SIGNAL(activated(QString)), SLOT(onCategotyChange(QString)));
}

PricesHistory::~PricesHistory()
{

}

void PricesHistory::init()
{
	//QStringList prods;
	//prods = qManager->products();

	QStringList categories = qManager->categories();

	ui.m_cbCategory->clear();
	ui.m_cbCategory->addItems(categories);
	ui.m_cbCategory->setCurrentIndex(-1);
//
//	ui.m_cbProduct->addItems(prods);
//	ui.m_cbProduct->setCurrentIndex(-1);
}

void PricesHistory::onCategotyChange(QString category)
{
	const int categoryId = qManager->categoryId(category);

	// need to get products for respective category
	const QStringList products = qManager->productsByCategory(categoryId);

	ui.m_cbProduct->clear();
	ui.m_cbProduct->addItems(products);
	ui.m_cbProduct->setCurrentIndex(-1);
}

void PricesHistory::onProductSelected(QString prodName)
{
	int prodId = qManager->productId(prodName);
	int columns = 2;

	QList<QDate> dates = qManager->productPriceDates(prodId);
	
	ui.m_twTable->setColumnCount (columns);
	ui.m_twTable->setRowCount (dates.count());

	foreach(QDate date, dates) {
		int index = dates.indexOf(date);
		QTableWidgetItem *newItemCat = new QTableWidgetItem(date.toString(st_dateFormat));
		ui.m_twTable->setItem(index, 0, newItemCat);

		// need to get purchases summ for category
		double price = qManager->productPriceOnDate(prodId, date);
		QTableWidgetItem *newItemSum = new QTableWidgetItem(QString::number(price));
		ui.m_twTable->setItem(index, 1, newItemSum);
	}
}
