/** @file mainwindow.cpp
 * @brief Contains implementation of Mainwindow, PaintParticles, WiggleTimer, and PaintParticle classes.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <vector>
#include <algorithm>
#include <QVBoxLayout>
#include <QHBoxLayout>


/** Constructor for MainWindow that creates all the GUI elements present in the app
 * @param parent is the parent widget
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // sets Title Window
    this->setWindowTitle("Particles on a Board");

    // creates particles
    particles = new PaintParticles;

    // sets welcome label
    welcome = new QLabel("Welcome to Particles on a Board!");
    welcome->setAlignment(Qt::AlignCenter);

    spacer = new QSpacerItem(100,100);
    QHBoxLayout* buttons = new QHBoxLayout;

    // creates color button that changes colors of particles when pressed
    color_button = new QPushButton;
    color_button->setText("Change colors");
    QObject::connect(color_button, SIGNAL(clicked(bool)), particles, SLOT (change_color()));

    // creates randomize button that randomizes positions of particles when pressed
    randomize_button = new QPushButton;
    randomize_button->setText("Randomize order");
    QObject::connect(randomize_button, SIGNAL(clicked(bool)), particles, SLOT(randomize_order()));

    // creates Timer that causes particles to wiggle
    timer = new WiggleTimer(this);
    timer->setInterval(75);
    QObject::connect(timer, SIGNAL(timeout()), particles, SLOT(wiggle()));

    // creates wiggle button that starts Timer when pressed
    wiggle_button = new QPushButton;
    wiggle_button->setText("Wiggle");
    QObject::connect(wiggle_button, SIGNAL(clicked(bool)), timer, SLOT(start_timer()));

    // creates reset button that resets all attributes of particles to default
    reset_button = new QPushButton;
    reset_button->setText("Reset");
    QObject::connect(reset_button, SIGNAL(clicked(bool)), particles, SLOT(reset_default()));
    QObject::connect(reset_button, SIGNAL(clicked(bool)), timer, SLOT(stop()));

    // adds buttons to layout
    buttons->addWidget(color_button);
    buttons->addWidget(randomize_button);
    buttons->addWidget(wiggle_button);
    buttons->addWidget(reset_button);

    // adds GUI elements to layout
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(welcome);
    layout->addLayout(buttons);
    layout->addSpacerItem(spacer);
    layout->addWidget(particles);

    // sets layout to central widget
    ui->centralWidget->setLayout(layout);

}


/** Destructor for MainWindow class
 */
MainWindow::~MainWindow()
{
    delete ui;
}


/** Creates a new MainWindow when "New Board" button on toolbar is pressed
 */
void MainWindow::on_actionNew_Board_triggered()
{
    new_window = new MainWindow;
    new_window->move(this->x()+50,this->y()+50);
    new_window->show();
}


/** Creates a dialog box that contains a bonus particle when "Click here" button on toolbar is pressed
 */
void MainWindow::on_actionClick_Here_triggered()
{
    // creates dialog and particle
    bonus_window = new QWidget;
    bonus_particle = new PaintParticle;
    bonus_label = new QLabel("Bonus particle!");

    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(bonus_label);
    layout->addWidget(bonus_particle);

    // sets layout and resizes window
    bonus_window->setLayout(layout);
    bonus_window->resize(120, 150);
    bonus_window->show();
}


/** Starts WiggleTimer if not currently active; otherwise stops timer
 */
void WiggleTimer::start_timer() {
    if (this->isActive())
        this->stop();
    else
        this->start();
}


/** Constructor for PaintParticles object. Sets initial locations, positions (number beneath particle), and color of particles.
 * @param parent is the parent widget
 */
PaintParticles::PaintParticles(QWidget *parent) : QWidget(parent), current_color(Qt::black) {
    for (int i = 0; i < 20; ++i) {
        positions.push_back(i-9);
        locations.push_back(30*i);
    }
}


/** Paintevent for PaintParticles object. Paints 20 square boxes in a line and labels each with a position.
 */
void PaintParticles::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(current_color);

    for (int i = 0; i < 20; ++i) {
        p.drawRect(locations[i], 0, 10, 10);
        QString s = QString::number(positions[i]);
        p.drawText(locations[i],30,s);
    }
}


/** Changes the color of the particles to a random color.
 */
void PaintParticles::change_color() {
    current_color = QColor(qrand()%255, qrand()%255, qrand()%255, 255);
    QCoreApplication::processEvents();
    repaint();
}


/** Randomly shuffles the positions of the particles
 */
void PaintParticles::randomize_order() {
    std::random_shuffle(positions.begin(), positions.end());
    QCoreApplication::processEvents();
    repaint();
}


/** Causes each particles to shift left or right a small random amount
 */
void PaintParticles::wiggle() {
    for (int i = 0; i < 20; ++i) {
        locations[i] = 30*i + qrand()%6 - 3;
    }
    QCoreApplication::processEvents();
    repaint();
}


/** Resets color, positions, and locations of particles to default
 */
void PaintParticles::reset_default() {
    current_color = Qt::black;
    for (int i = 0; i < 20; ++i) {
        positions[i] = i-9;
        locations[i] = 30*i;
    }
    QCoreApplication::processEvents();
    repaint();
}


/** Constructor for PaintParticle object. Sets initial color of particle. Also creates and starts a timer that will be used to rapidly change the color of the particle.
 */
PaintParticle::PaintParticle(QWidget *parent) : QWidget(parent), current_color(Qt::black) {
    timer = new QTimer(this);
    timer->setInterval(75);
    timer->start();

    // color of particle changes every 75 milliseconds
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(change_color()));

};


/** PaintEvent for PaintParticle object. Paints a single particle and label underneath.
 */
void PaintParticle::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(current_color);

    p.drawRect(40,15,10,10);
    p.drawText(27,45,"Bonus");
}


/** Changes color of PaintParticle to a random color
 */
void PaintParticle::change_color() {
    current_color = QColor(qrand()%255, qrand()%255, qrand()%255, 255);
    QCoreApplication::processEvents();
    repaint();
}


