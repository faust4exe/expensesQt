#ifndef F4QDOUBLESPINBOXTOUCHABLE_H
#define F4QDOUBLESPINBOXTOUCHABLE_H

#include <QDoubleSpinBox>
#include <QMouseEvent>
#include <QLocale>
#include <QLineEdit>
#include <QString>

class f4QDoubleSpinBoxTouchable : public QDoubleSpinBox
{
	Q_OBJECT

public:
	f4QDoubleSpinBoxTouchable(QWidget *parent = 0);
	~f4QDoubleSpinBoxTouchable();

protected:
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	bool eventFilter(QObject *obj, QEvent *event);

private:
	// shows if currently mouse is pressed on spin box
	bool m_pressed;
	double m_baseValue;
	int m_commaPos;
	int m_cursPos;
};

#endif // F4QDOUBLESPINBOXTOUCHABLE_H
