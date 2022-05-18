#include "Point.h"
#include <QtWidgets/QApplication>
#include <QPixmap>
#include<qpainter.h>
#include <QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(QSize(1024, 720));

    QPushButton but2(&w);
    but2.setText("清除");
    but2.move(650, 300);

    QPushButton but(&w);
    but.setText("识别");
    but.move(650, 450);
    QObject::connect(&but, &QPushButton::clicked, &w, &MainWindow::Identification);
    QObject::connect(&but2, &QPushButton::clicked, &w, &MainWindow::Clear);

    w.show();
    return a.exec();
}
