#include "View/MainWindow.h"

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

int main(int argc, char *argv[]) {

    QApplication Sensors(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return Sensors.exec();
}
