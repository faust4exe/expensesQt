#include "expenses.h"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	eXpenses w;

#ifdef USING_QT5
    // TODO : set screen orientation
#else
    w.setAttribute(Qt::WA_AutoOrientation, true);
#endif

    w.show();//Maximized();

	return a.exec();
}
