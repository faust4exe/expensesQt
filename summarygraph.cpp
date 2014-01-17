#include "summarygraph.h"
#include <QDebug>

SummaryGraph::SummaryGraph(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	init();

	ui.m_graph->setParent(ui.scrollArea);

	connect(ui.m_tbZoomIn, SIGNAL(clicked()), ui.m_graph, SLOT(zoomInDays()));
	connect(ui.m_tbZoomOut, SIGNAL(clicked()), ui.m_graph, SLOT(zoomOutDays()));
}

SummaryGraph::~SummaryGraph()
{

}

void SummaryGraph::init()
{
	//QStringList prods;
	//prods = qManager->products();

	QStringList categories = qManager->categories();

	ui.m_cbCategory->clear();
	ui.m_cbCategory->addItem("ALL");
	ui.m_cbCategory->addItems(categories);
	ui.m_cbCategory->setCurrentIndex(-1);

	ui.m_graph->clear();
//
//	ui.m_cbProduct->addItems(prods);
//	ui.m_cbProduct->setCurrentIndex(-1);
}

void SummaryGraph::onCategotySelected(QString category)
{
	const int categoryId = qManager->categoryId(category);

	// need to get products for respective category
	const QStringList products = qManager->productsByCategory(categoryId);

	ui.m_cbProduct->clear();
	ui.m_cbProduct->addItem("ALL");
	ui.m_cbProduct->addItems(products);
	ui.m_cbProduct->setCurrentIndex(-1);

	ui.m_graph->clear();

	if(category == "ALL")
		onProductSelected("ALL");
}

void SummaryGraph::onProductSelected(QString product)
{
	QString category = ui.m_cbCategory->currentText();

	QMap<QDate, double> map;

	for(QDate date = QDate::currentDate().addDays(-14); date < QDate::currentDate(); date = date.addDays(1)) {

		// need to get purchases summ for category
		int expence;
		if (category == "ALL")
			expence = qManager->expencesOnDate(date);
		else if (product == "ALL")
			expence = qManager->categoryExpencesOnDate(category, date);
		else 
			expence = qManager->productExpencesOnDate(product, date);

		if (map.contains(date))
			map[date] = map[date] + expence;
		else
			map[date] = expence;
	}

	// loading values to graphic
	QList<QDate> dates = map.keys();
	ui.m_graph->clear();

	foreach(QDate date, dates) {
		//qDebug() << "Date: " << date << " Value: " << map[date];
		ui.m_graph->addValue(date, map[date]);
	}
}

