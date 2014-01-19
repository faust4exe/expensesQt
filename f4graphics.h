#ifndef F4GRAPHICS_H
#define F4GRAPHICS_H

#include <QWidget>
#include <QDate>
#include <QMap>
#include <QPoint>

class f4Graphics : public QWidget
{
	Q_OBJECT

public:
	f4Graphics(QWidget *parent = 0);
	~f4Graphics();

	void clear();

	void addValue(QDate dt, double val);

public slots:
	void zoomInDays();
	void zoomOutDays();

protected:
	virtual void paintEvent(QPaintEvent*);
	virtual void resizeEvent( QResizeEvent *);
	virtual void mouseMoveEvent(QMouseEvent*);
	virtual void mousePressEvent(QMouseEvent*);

private:
	void zoomDays(double inc);

private:
	QDate m_min, m_max;
	double m_maxValue;
	QMap<QDate, double> m_values;
	
	double m_valPerPixel;
	double m_daysPerPixel;
	int m_height;
	int m_frame;

	QPoint m_pos;
	int m_sliderPos;
};

#endif // F4GRAPHICS_H

