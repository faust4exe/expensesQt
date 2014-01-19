#ifndef SUMMARYGRAPH_H
#define SUMMARYGRAPH_H

#include <QDialog>

#include "ui_summarygraph.h"

class SummaryGraph : public QDialog
{
	Q_OBJECT

public:
	SummaryGraph(QWidget *parent = 0);
	~SummaryGraph();

private Q_SLOTS:
	void onProductSelected(QString prodName);
	void onCategotySelected(QString category);

private:
	void init();

private:
	Ui::SummaryGraph ui;
};

#endif // SUMMARYGRAPH_H
