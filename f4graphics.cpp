#include "f4graphics.h"

f4Graphics::f4Graphics(QWidget *parent)
	: QWidget(parent)
{
	clear();
	setFixedWidth(400);
}

f4Graphics::~f4Graphics()
{

}

void f4Graphics::addValue(QDate dt, double val)
{
	m_values[dt] = val;

	// need to update values
	if (m_min == QDate())
		m_min = dt;

	if (m_max == QDate())
		m_max = dt;

	if (dt < m_min) {
		m_min = dt;
		int days = m_min.daysTo(m_max);
		setFixedWidth(days / m_daysPerPixel + m_frame * 2);
	}

	if (dt > m_max) {
		m_max = dt;
		int days = m_min.daysTo(m_max);
		setFixedWidth(days / m_daysPerPixel + m_frame * 2);
	}

	if (m_maxValue < val) {
		m_maxValue = val;
		int hg = height() - m_frame * 2;
		m_valPerPixel = m_maxValue /(double)(hg);
		m_height = hg;
	}
}

void f4Graphics::resizeEvent(QResizeEvent *ev)
{
	int newHg = size().height() - m_frame * 2;
	m_valPerPixel = m_valPerPixel  * m_height / newHg;
	m_height = newHg;
}

void f4Graphics::mouseMoveEvent(QMouseEvent *ev)
{
	QWidget::mouseMoveEvent(ev);

	QObject * obj = parent();
	QScrollArea * scroll = qobject_cast<QScrollArea*>(obj);

	if (scroll) {
		QPoint pos = ev->pos();
		int diff = m_pos.x() - pos.x();
		int sliderPos = scroll->horizontalScrollBar()->value();
		QScrollBar *bar = scroll->horizontalScrollBar();
		bar->setValue(m_sliderPos + diff);
	}
}

void f4Graphics::mousePressEvent(QMouseEvent *ev)
{
	QObject * obj = parent();
	QScrollArea * scroll = qobject_cast<QScrollArea*>(obj);

	if (scroll) {
		m_pos = ev->pos();
		m_sliderPos = scroll->horizontalScrollBar()->value();
	}
}

void f4Graphics::clear()
{
	m_values.clear();
	m_maxValue = 0;
	m_min = QDate();
	m_max = QDate();
	m_valPerPixel = 10;
	m_daysPerPixel = 0.05;
	m_frame = 5; 
}

void f4Graphics::zoomInDays()
{
	zoomDays(0.75);
}

void f4Graphics::zoomOutDays()
{
	zoomDays(1.25);
}

void f4Graphics::zoomDays(double inc)
{	
	int days = m_min.daysTo(m_max);
	m_daysPerPixel *= inc;
	setFixedWidth(days / m_daysPerPixel + m_frame * 2);	
}



void f4Graphics::paintEvent(QPaintEvent* ev)
{
	QPainter p(this);

	p.fillRect(rect(), QBrush(Qt::white));

	p.setPen(Qt::black);

	//p.drawRect(12,12,100,100);

	int val = 50;

	QList<QDate> keys = m_values.keys();
	qSort(keys);

	double precValPix = 0;
	double precDayPix = 0;

	for (int i=0; i< keys.count(); i++){
		QDate dt = keys[i];
		double val = m_values.value(dt);

		int day = m_min.daysTo(dt);

		QString date = dt.toString("dd.MM");
		QFontMetrics f(p.font());
		QRect rect = f.boundingRect(date);
		int x0 = rect.width();

		// updating the resolition
		int newHg = size().height() - m_frame * 2 - x0;
		m_valPerPixel = m_valPerPixel  * m_height / newHg;
		m_height = newHg;

		int dayPix = m_frame + day / m_daysPerPixel;
		int valPix = val / m_valPerPixel;

		

		int hg = height() - m_frame * 2 - x0;
		int hgDates = height() - m_frame * 2;
		
		rect.moveCenter(QPoint(- hgDates + m_frame, dayPix));
		//rect.moveCenter(QPoint(- hg + m_frame + rect.width()/2.0, dayPix));
		//rect.moveLeft(m_frame);

		p.rotate(-90);

		p.fillRect(rect, QBrush(Qt::yellow));
		p.drawText(rect, Qt::AlignCenter, date);
		//p.drawText(QPoint(- hg, dayPix), date);

		p.rotate(90);

		p.setPen(Qt::SolidLine);

		

		if (i != 0){
			p.drawLine(precDayPix, hg - precValPix + m_frame,
				dayPix, hg - valPix + m_frame);
		}

		p.setPen(Qt::DotLine);

		p.drawLine(dayPix, hg - valPix + m_frame,
				dayPix, hg + m_frame);

		p.drawEllipse(QPoint(dayPix, hg - valPix + m_frame),
			3,3);

		

		if (val>0) {
			QString valueText = QString::number(val);
			QRect valueRect = f.boundingRect(valueText);
			valueRect.moveCenter(QPoint(dayPix + valueRect.width() + 3, hg - valPix + m_frame));
			p.drawText(valueRect, valueText);
		}

		//p.scale(0.1,0.1);
		
		precValPix = valPix;
		precDayPix = dayPix;
	}

	if (keys.isEmpty())
		p.drawText(rect().center(), "Please Choose Options");

}
