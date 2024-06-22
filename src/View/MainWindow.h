#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMenuBar>
#include <QString>
#include <QVector>
#include <QInputDialog>
#include <QMessageBox>

#include <fstream>
#include <QFileDialog>

#include "SensorCreateDialog.h"
#include "../Controller/SensorManager.h"
#include "ValueCalculatorVisitor.h"
#include "Model/Sensor.h"
#include "SearchBar.h"
#include "SensorInfo.h"
#include "SensorCharts.h"

class Sensor;
class SensorManager;

//View: main window of the application
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::vector<std::unique_ptr<Sensor>> simulationSensors; //list of sensors for simulation

    //keyboard shortcuts
    QAction* saveAction;
    QAction* removeAction;


    QMenuBar *menuBar;
    QMenu *fileMenu;

    QHBoxLayout* mainLayout;

    //dichiarazione widget e layout
    SearchBar* searchBar;
    QListWidget* sensorList;

    QLabel* sensorIdLabel; //label for sensor ID
    QLabel* sensorNameLabel; //label for sensor name
    QLabel* sensorValueLabel; //label for sensor value (and particle size for dust sensors)

    QPushButton* addButton;  //add button
    QPushButton* removeButton;  //remove button
    QComboBox* startSimulationButton;  //combo box Start Simulation

    ValueCalculatorVisitor *valueCalculator; //visitor for calculating sensor values
    SensorManager *sensorManager; //controller
    SensorCreateDialog *sensorCreateDialog; //dialog window for creating a new sensor
    SensorInfo *sensorInfo; //widget for showing sensor info
    SensorCharts *sensorCharts; //widget for showing sensor charts

    QWidget* widget;
    QVBoxLayout* layout;
    QGridLayout* chart;

    void addSensor(Sensor* sensor);
    void updateSensorList();
    void startSimulation(const QString& type);

    //data persistence
    void saveSensorToTxt(const Sensor* sensor, std::ofstream& outFile);
    void loadSensorFromTxt(std::ifstream& inFile);

//funzioni che vengono chiamate quando si verifica un evento
private slots:
    void onSearchBarTextChanged(const QString& text);
    void onAddButtonClicked();
    void onRemoveButtonClicked();
    void onSimulationTypeChanged(const QString& type);
    void onSensorSelected();
    void onModifyButtonClicked();
    void onPointClicked(int index);

    void saveSensors();
    void loadSensors();

};

#endif // MAINWINDOW_H
