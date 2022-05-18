#pragma once
#include"Network.h"
#include <QtWidgets/QMainWindow>
#include "ui_Point.h"
#include<qpushbutton.h>
#include<vector>
#include <QLabel>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

    void DrawPoint(int x, int y);
public Q_SLOTS:
    void Clear();
    void Identification();
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
private:
    Ui::PointClass ui;
    Network mNet;
    QPixmap mPixMap;
    QPoint mStartPoint,mEndPoint;
    std::vector<long double>mMat;
    QLabel mLabel;
};
