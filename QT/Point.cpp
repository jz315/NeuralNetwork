#include "Point.h"
#include <QPixmap>
#include<qpainter.h>
#include<qevent.h>
#include<QDebug>
#include"Matrix.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
	mPixMap(QPixmap(28,28)),
	mMat(784),
	mLabel(this)
{
	mPixMap.fill(Qt::white);
	ui.setupUi(this);
	mNet.Load("model.json");
	mLabel.setText("识别的数字是:");
	mLabel.move(800,350);
}
    
	
	

void MainWindow::DrawPoint(int x, int y)
{
	QPainter painter(&mPixMap);
	painter.setPen(QPen(Qt::black, 2));
	painter.drawPoint(x,y);
}

void MainWindow::Clear()
{
	mPixMap.fill(Qt::white);
	std::fill(mMat.begin(),mMat.end(),0);
	update();
}

void MainWindow::Identification()
{
	auto mat = mNet.Eval(mMat);
	long double maxNum = 0;
	int pos = 0, realPos = 0;

	for (int i = 0; i < mat.GetCols(); i++)
	{
		if (mat.At(0, i) > maxNum)
		{
			pos = i;
			maxNum = mat.At(0, i);
		}
	}
	mLabel.setText("识别的数字是:" + QString::number(pos));
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.drawPixmap(256, 200, 270 ,270, mPixMap);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	auto point = (event->pos() - QPoint(256, 200)) / 10;
	mStartPoint = point;
	//qDebug() << point.y() * 28 + point.x();
	if (point.x() >= 0 && point.x() <= 27 && point.y() >= 0 && point.y() <= 27)
	{
		mMat[point.y() * 28 + point.x()] = 1;
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	//qDebug() << (event->pos() / 10) - QPoint(256, 200);
	QPainter* painter = new QPainter;

	auto point = (event->pos() - QPoint(256, 200)) / 10;

	painter->begin(&mPixMap);
	painter->setPen(QPen(Qt::black, 1));
	painter->drawLine(mStartPoint, point); //绘制开始点到移动点的位置
	painter->end();
	mStartPoint = point;
	//qDebug() << point.y() * 28 + point.x();
	if (point.x() >= 0 && point.x() <= 27 && point.y() >= 0 && point.y() <= 27)
	{
		mMat[point.y() * 28 + point.x()] = 1;
	}
	
	update();
	
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
	
}
