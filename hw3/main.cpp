/** @mainpage Particles on a Board
 * @author Douglas Yao
 * @date April 14, 2016
 *
 * This app creates a line of particles, represented by black boxes, in a window and contains several buttons that can be pressed to change the properties of the particles.
 */

/** @file main.cpp
 * @brief standard Qt main
 */

#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
