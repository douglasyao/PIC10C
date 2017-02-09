/** @file mainwindow.h
 * @brief Contains declarations for variables, slots, and constructors
 *
 * Declares all the functionality for the app to run.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QSpacerItem>
#include <QLabel>


/** @namespace Ui
 *  @brief GUI namespace
 */
namespace Ui {
class MainWindow;
}

// forward declarations
class PaintParticles;
class PaintParticle;
class WiggleTimer;


/** @class MainWindow
 * @brief Main object of the app that creates and manages GUI
 *
 * This class stores all the variables that will be present when running the app. Also contains functions for the toolbar buttons.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_Board_triggered(); // when "New Board" is selected on toolbar
    void on_actionClick_Here_triggered(); // when "Click Here" is selected on toolbar

private:
    Ui::MainWindow *ui;
    PaintParticles* particles; // paints particles
    WiggleTimer* timer; // timer for wiggle function
    QLabel* welcome; // welcome label
    QSpacerItem* spacer; // spacer item between buttons/label and particles

    // four main buttons to perform actions on buttons
    QPushButton* color_button;
    QPushButton* randomize_button;
    QPushButton* wiggle_button;
    QPushButton* reset_button;

    MainWindow* new_window; // new window that appears when "New Board" is selected on toolbar
    QWidget* bonus_window; // dialog that appears when "Click Here" is selected on toolbar
    PaintParticle* bonus_particle; // paints bonus particle
    QLabel* bonus_label; // bonus label
};


/** @class PaintParticles
 * @brief Custom Widget that paints a line of 20 particles labelled with positions
 *
 * This class derives from the QWidget class and draws 20 particles in a line. It contains various functions that change the properties of the particles.
 */
class PaintParticles : public QWidget {
    Q_OBJECT

public:
    PaintParticles(QWidget * parent = 0);

public slots:
    void change_color();
    void randomize_order();
    void wiggle();
    void reset_default();

private:
    void paintEvent(QPaintEvent *);
    QColor current_color;
    std::vector<int> positions;
    std::vector<int> locations;

};


/** @class WiggleTimer
 * @brief Custom timer used for wiggle function
 *
 * This class derives from the QTimer class and is used for the wiggle function of PaintParticles.
 */
class WiggleTimer : public QTimer {
    Q_OBJECT

public:
    WiggleTimer(QWidget* parent = 0) : QTimer(parent) {};

public slots:
    void start_timer();
};


/** @class PaintParticle
 * @brief Custom Widget that paints a single particle
 *
 * This class is similar to the PaintParticles class, except it paints only one particle and stores a timer used to change the color of the particle.
 */
class PaintParticle : public QWidget {
    Q_OBJECT

public:
    PaintParticle(QWidget * parent = 0);

public slots:
    void change_color();

private:
    void paintEvent(QPaintEvent *);
    QColor current_color;
    QTimer* timer;

};

#endif // MAINWINDOW_H
