#ifndef ADDCATEGORY_H
#define ADDCATEGORY_H

#include <QDialog>
#include <QMessageBox>
#include "manager.h"
#include "ui_addcategory.h"

class AddCategory : public QDialog
{
	Q_OBJECT

public:
	AddCategory(QWidget *parent = 0);
	~AddCategory();

Q_SIGNALS:
	void addedCategory(QString);

public Q_SLOTS:
	void accept();

private:
	Ui::AddCategory ui;
};

#endif // ADDCATEGORY_H
