#ifndef SUMMARY_H
#define SUMMARY_H

#include <QDialog>
#include <QDate>

#include "ui_summary.h"

class Summary : public QDialog
{
	Q_OBJECT

public:
	Summary(QWidget *parent = 0);
	~Summary();

private slots:
	void update();
	void onShowSummaryGraph();

private:
	void loadData();
	QDate getDateLimit();

private:
	Ui::Summary ui;
};

#endif // SUMMARY_H
