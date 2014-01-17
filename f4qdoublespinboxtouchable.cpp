#include "f4qdoublespinboxtouchable.h"
#include <QDebug>
#include <math.h>

f4QDoubleSpinBoxTouchable::f4QDoubleSpinBoxTouchable(QWidget *parent)
	: QDoubleSpinBox(parent)
	, m_pressed(false)
	,m_baseValue(0)
	,m_commaPos(0)
	,m_cursPos(0)
{
	lineEdit()->installEventFilter(this);
}

f4QDoubleSpinBoxTouchable::~f4QDoubleSpinBoxTouchable()
{

}

void f4QDoubleSpinBoxTouchable::mousePressEvent(QMouseEvent *ev)
{
	// need to get position of the mouse in text
	const QPoint pos = ev->pos();

	QLineEdit * le = lineEdit();
	const QChar point = QLocale::system().decimalPoint();

	m_cursPos = le->cursorPositionAt(pos);
	m_commaPos = le->text().indexOf(point);

	if (m_cursPos != m_commaPos + 1)
		m_pressed = true;

	m_baseValue = value();

	// Exemple 
	// cur : 0  1  2  3  4  5
	// pos :   0  1  2  3  4
	// val :   0  ,  0  0  0

	qDebug() << "commaAt : "<< m_commaPos << "  ----  cursPos : " << m_cursPos;

	QDoubleSpinBox::mousePressEvent(ev);
}

void f4QDoubleSpinBoxTouchable::mouseReleaseEvent(QMouseEvent *ev)
{
	m_pressed = false;
	QDoubleSpinBox::mouseReleaseEvent(ev);
}

void f4QDoubleSpinBoxTouchable::mouseMoveEvent(QMouseEvent *ev)
{
	// here need to handle move up and down
	if (m_pressed) {
		// get the value of increment
		const QPoint pos = ev->pos();
		const QRect rect = lineEdit()->rect();

		int y = pos.y();
		int yMin = rect.top();
		int yMax = rect.bottom();
		int height = rect.height();
		int diff;
		if (y < yMin)
			diff = yMax - y;
		else 
			diff = yMin - y;

		int increment = (double)((1.0 * diff) / (double)(height));

		double incBase;
		if (m_cursPos < m_commaPos + 1)
                        incBase = pow(10, m_commaPos - m_cursPos);
		else
                        incBase = pow(10, m_commaPos - m_cursPos + 1);

		setValue(m_baseValue + increment * incBase);

	}
	QDoubleSpinBox::mouseMoveEvent(ev);
}

bool f4QDoubleSpinBoxTouchable::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonPress) {
		QMouseEvent *mouseEv = static_cast<QMouseEvent *>(event);
		mousePressEvent(mouseEv);
		return true;
	} else if (event->type() == QEvent::MouseButtonRelease){
		QMouseEvent *mouseEv = static_cast<QMouseEvent *>(event);
		mouseReleaseEvent(mouseEv);
		return true;
	} else if (event->type() == QEvent::MouseMove){
		QMouseEvent *mouseEv = static_cast<QMouseEvent *>(event);
		mouseMoveEvent(mouseEv);
		return true;
	} else {
		 // standard event processing
		return QObject::eventFilter(obj, event);
	}
}
