#include "summary.h"

#include <QTableWidgetItem>

#include "manager.h"
#include "summarygraph.h"

Summary::Summary(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	loadData();

	connect(ui.comboBox, SIGNAL(activated (int)), SLOT(update()));
}

Summary::~Summary()
{

}

void Summary::loadData()
{
	QDate summaryDateLimit;
	summaryDateLimit = getDateLimit();
	int columns = 2;
	
	QStringList categories = qManager->categories();

	//ui.m_twTable->clear();
	ui.m_twTable->setColumnCount (columns);
	ui.m_twTable->setRowCount (categories.count());

	double totalExpence = 0;

	foreach(QString categ, categories) {
		int index = categories.indexOf(categ);
		QTableWidgetItem *newItemCat = new QTableWidgetItem(categ);
		ui.m_twTable->setItem(index, 0, newItemCat);

		// need to get purchases summ for category
		double summ = qManager->categoryExpences(categ, summaryDateLimit);
		QTableWidgetItem *newItemSum = new QTableWidgetItem(QString::number(summ));
		ui.m_twTable->setItem(index, 1, newItemSum);

		totalExpence = totalExpence + summ;
	}

	ui.m_dsbTotal->setValue(totalExpence);
}

void Summary::update()
{
	loadData();
}

void Summary::onShowSummaryGraph()
{
	SummaryGraph * summGraph = new SummaryGraph();

        summGraph->show();//showMaximized();
}

QDate Summary::getDateLimit()
{
	QDate date = QDate::currentDate();

	if(ui.comboBox->currentText() == "Last Year")
		date = date.addDays(-date.daysInYear());

	if(ui.comboBox->currentText() == "This Year")
		date = date.addDays(-date.dayOfYear());

	if(ui.comboBox->currentText() == "Last Month")
		date = date.addDays(-date.daysInMonth());

	if(ui.comboBox->currentText() == "This Month")
		date = date.addDays(-date.day());

	if(ui.comboBox->currentText() == "Last Week")
		date = date.addDays(- 7);

	if(ui.comboBox->currentText() == "This Week")
		date = date.addDays(- date.dayOfWeek());

	// this no changes required
	if(ui.comboBox->currentText() == "Today")
		date = date.addDays(- 1);
			
	QString dateStr = date.toString();

	return date;
}
