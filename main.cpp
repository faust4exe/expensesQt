#include "expenses.h"
#include <QtGui/QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	eXpenses w;

        w.setAttribute(Qt::WA_AutoOrientation, true);

        w.show();//Maximized();

	return a.exec();
}
