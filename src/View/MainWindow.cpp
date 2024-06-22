#include "View/MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("Sensor Simulation"); //window title
    resize(1050,700); //size

    //menu bar creation
    QMenuBar *menuBar = new QMenuBar();
    menuBar->setGeometry(0,0,1270,21);
    QMenu *fileMenu = menuBar->addMenu("File");
    setMenuBar(menuBar);

    QAction *saveAction = new QAction("Save", this);
    QAction *openAction = new QAction("Open", this);
    fileMenu->addAction(openAction);

    //Keyboard shortcuts Actions
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    fileMenu->addAction(saveAction);

    openAction->setShortcut(QKeySequence("Ctrl+O"));
    fileMenu->addAction(openAction);

    QAction* removeAction = new QAction("Remove", this);
    removeAction->setShortcut(QKeySequence("Ctrl+X"));

    addAction(removeAction);


    //Widgets
    sensorManager = new SensorManager();
    sensorCreateDialog = new SensorCreateDialog(this);
    searchBar = new SearchBar(this);
    sensorList = new QListWidget(this);
    sensorInfo = new SensorInfo(this);
    sensorCharts = new SensorCharts(this);
    addButton = new QPushButton("Add", this);
    removeButton = new QPushButton("Remove", this);

    //ComboBox for simulation
    startSimulationButton = new QComboBox(this);
    startSimulationButton->addItem("Select Simulation");
    startSimulationButton->addItem("Start Temperature Simulation");
    startSimulationButton->addItem("Start Humidity Simulation");
    startSimulationButton->addItem("Start Dust Simulation");

    //main widget and layout
    QWidget *mainWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainWidget);

    //vertical widget for the search bar and sensor list
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(searchBar);
    leftLayout->addWidget(sensorList);

    //horizontal widget for the add and remove buttons under the sensor list
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    leftLayout->addLayout(buttonLayout);


    //vertical widget for the sensor info, sensor charts and simulation combo box
    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(sensorInfo);
    rightLayout->addWidget(sensorCharts);
    rightLayout->addWidget(startSimulationButton);

    //add the two layouts to the main layout and set the central widget
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 3);

    setCentralWidget(mainWidget);

    //connections
    connect(searchBar, &SearchBar::searchTextChanged, this, &MainWindow::onSearchBarTextChanged);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveButtonClicked);
    connect(startSimulationButton, &QComboBox::currentTextChanged, this, &MainWindow::startSimulation);
    connect(sensorList, &QListWidget::itemSelectionChanged, this, &MainWindow::onSensorSelected);
    connect(sensorInfo, &SensorInfo::modifyClicked, this, &MainWindow::onModifyButtonClicked);
    connect(sensorCharts, &SensorCharts::pointClicked, this, &MainWindow::onPointClicked);

    //file menu actions connections
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveSensors);
    connect(removeAction, &QAction::triggered, this, &MainWindow::onRemoveButtonClicked);
    connect(openAction, &QAction::triggered, this, &MainWindow::loadSensors);
}

//destructor
MainWindow::~MainWindow() {
    delete sensorManager;
}

//method to add a sensor
void MainWindow::addSensor(Sensor* sensor) {
    sensorList->addItem(QString::fromStdString(sensor->getName()));
}

//method to update the sensor list
void MainWindow::updateSensorList() {
    sensorList->clear();
    for (const auto& sensor : sensorManager->getSensors()) {
        sensorList->addItem(QString::fromStdString(sensor->getName()));
    }
}

//method to start the simulation
void MainWindow::startSimulation(const QString& type) {
    //clear previous data
    simulationSensors.clear();
    QVector<double> sensorData;

    //generate 7 sensors (1 per day for a week)
    for (int i = 0; i < 7; ++i) {
        std::unique_ptr<Sensor> sensor;
        double value = 0.0;

        if (type == "Start Temperature Simulation") {
            sensor = std::unique_ptr<Sensor>(sensorManager->createTempSensor(i + 1, "Temperature Sensor " + std::to_string(i + 1), 0));
        } else if (type == "Start Humidity Simulation") {
            sensor = std::unique_ptr<Sensor>(sensorManager->createHumSensor(i + 1, "Humidity Sensor " + std::to_string(i + 1), 0));
        } else if (type == "Start Dust Simulation") {
            sensor = std::unique_ptr<Sensor>(sensorManager->createDustSensor(i + 1, "Dust Sensor " + std::to_string(i + 1), 0));
        }

        if (sensor) {
            ValueCalculatorVisitor valueCalculator;
            sensor->accept(valueCalculator);

            if (Temperature* tempSensor = dynamic_cast<Temperature*>(sensor.get())) {
                value = tempSensor->getValue();
            } else if (Humidity* humSensor = dynamic_cast<Humidity*>(sensor.get())) {
                value = humSensor->getValue();
            } else if (Dust* dustSensor = dynamic_cast<Dust*>(sensor.get())) {
                value = dustSensor->getValue();
            }

            sensorData.push_back(value);

            // Add the sensor to the manager (optional)
            simulationSensors.push_back(std::move(sensor));
        }
    }

    //determine sensor type string
    QString sensorType = type.contains("Temperature") ? "Temperature" : (type.contains("Humidity") ? "Humidity" : "Dust");

    // update the graph with new data
    sensorCharts->updateChartData(sensorData, sensorType);
}

//method to update the sensor list when the search bar text changes
void MainWindow::onSearchBarTextChanged(const QString& text) {
    updateSensorList(); //updating the list
    QStringList filteredList; //memorizzo i sensori filtrati
    bool isNumber; //verifico se il testo è un numero
    u_int searchID = text.toUInt(&isNumber);

    //verifico per ogni sensore della lista se il testo è contenuto nel nome del sensore
    for (const auto& sensor : sensorManager->getSensors()) {
        if ((isNumber && sensor->getId() == searchID) || QString::fromStdString(sensor->getName()).contains(text, Qt::CaseInsensitive)) {
            filteredList.append(QString::fromStdString(sensor->getName()));
        }
    }
    sensorList->clear();
    sensorList->addItems(filteredList);
}

//method to add a sensor
void MainWindow::onAddButtonClicked() {
    sensorCreateDialog->exec(); //execute the dialog
    if (sensorCreateDialog->result() == QDialog::Accepted) {
        QString selectedSensorType = sensorCreateDialog->getSelectedSensorType();
        QString sensorName = sensorCreateDialog->getSensorName();
        std::unique_ptr<Sensor> newSensor;
        static u_int nextId = 1;  //incremental ID for sensors
        try {
            if (selectedSensorType == "Temperature") {
                newSensor = std::unique_ptr<Sensor>(sensorManager->createTempSensor(nextId++, sensorName.toStdString(), 0)); //create a new temperature sensor
            } else if (selectedSensorType == "Humidity") {
                newSensor = std::unique_ptr<Sensor>(sensorManager->createHumSensor(nextId++, sensorName.toStdString(), 0)); //create a new humidity sensor
            } else if (selectedSensorType == "Dust") {
                newSensor = std::unique_ptr<Sensor>(sensorManager->createDustSensor(nextId++, sensorName.toStdString(), 0)); //create a new dust sensor
            }

            if (newSensor) {
                ValueCalculatorVisitor valueCalculator;
                newSensor->accept(valueCalculator);
                sensorManager->addSensor(std::move(newSensor));
                updateSensorList();
                sensorInfo->update(sensorManager->searchSensorByName(sensorName.toStdString()));
            }
        } catch (std::exception& exeption) {
            qWarning() << "Failed to add sensor:" << exeption.what();
        }
    }
}

//method to remove a sensor
void MainWindow::onRemoveButtonClicked() {
    QListWidgetItem* selectedItem = sensorList->currentItem();
    if (selectedItem) {
        QString sensorName = selectedItem->text();
        Sensor* sensor = sensorManager->searchSensorByName(sensorName.toStdString());
        if (sensor) {
            //removes the sensor from the sensor manager
            sensorManager->removeSensor(sensor->getId());
            //removes the sensor from the list
            delete sensorList->takeItem(sensorList->row(selectedItem));
            //updates the sensor info widget
            sensorInfo->update(nullptr);

            //solved problem of not showing info after removing
            updateSensorList();
            //automatically select the first item in the updated list
                if (sensorList->count() > 0) {
                sensorList->setCurrentRow(0);
                onSensorSelected();
            }
        }
    }
}

//method to start the simulation
void MainWindow::onSimulationTypeChanged(const QString& type) {
    if (type == "Select Simulation") {
        return;
    }

    startSimulation(type);
    startSimulationButton->setCurrentIndex(0); // Reset to the default option after selection
}

//method to show sensor info when a sensor is selected
void MainWindow::onSensorSelected() {
    QListWidgetItem* selectedItem = sensorList->currentItem(); //current selected item
    if (selectedItem) {
        QString sensorName = selectedItem->text(); //obtain the sensor name
        Sensor* sensor = sensorManager->searchSensorByName(sensorName.toStdString());
        if (sensor) {
            sensorInfo->update(sensor); //if found update sensor info with the current selected sensor
        }
    }
}

//method to modify a sensor name
void MainWindow::onModifyButtonClicked() {
    QListWidgetItem* selectedItem = sensorList->currentItem();
    if(selectedItem) {
        QString sensorName = selectedItem->text();
        Sensor* sensor = sensorManager->searchSensorByName(sensorName.toStdString());
        if(sensor) {
            bool ok;
            QString newName = QInputDialog::getText(this, tr("Modify Sensor Name"),
                                                    tr("New Sensor Name:"), QLineEdit::Normal,
                                                    QString::fromStdString(sensor->getName()), &ok);
            if(ok && !newName.isEmpty()) {
                sensorManager->updateSensor(sensor->getId(), newName.toStdString());
                updateSensorList();
                sensorInfo->update(sensor);
            }
        }
    }
}

//method to show sensor info when a point is clicked on the chart
void MainWindow::onPointClicked(int index) {
    if (index >= 0 && static_cast<size_t>(index) < simulationSensors.size()) {
        Sensor* sensor = simulationSensors[static_cast<size_t>(index)].get();
        sensorInfo->update(sensor); // Aggiorna le informazioni del sensore cliccato
    }
}


//method to save sensors in txt file
void MainWindow::saveSensors() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Sensor Data"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty()) return;

    if (fileName.endsWith(".txt")) {
        std::ofstream outFile(fileName.toStdString());
        if (outFile.is_open()) {
            for (const auto& sensor : sensorManager->getSensors()) {
                saveSensorToTxt(sensor.get(), outFile);
            }
            outFile.close();
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Unable to open file for writing."));
        }
    }
}

//method to load sensors from txt file
void MainWindow::loadSensors() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sensor Data"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty()) return;

    sensorManager->clearSensors();
    sensorList->clear();

    if (fileName.endsWith(".txt")) {
        std::ifstream inFile(fileName.toStdString());
        if (inFile.is_open()) {
            loadSensorFromTxt(inFile);
            inFile.close();
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Unable to open file for reading."));
        }
    }

    updateSensorList();
}

//method to save sensors in txt file
void MainWindow::saveSensorToTxt(const Sensor* sensor, std::ofstream& outFile) {
    outFile << "ID: " << sensor->getId() << "\n";
    outFile << "Name: " << sensor->getName() << "\n";

    if (const Temperature* temp = dynamic_cast<const Temperature*>(sensor)) {
        outFile << "Type: Temperature\n";
        outFile << "Value: " << temp->getValue() << "\n";
    } else if (const Humidity* hum = dynamic_cast<const Humidity*>(sensor)) {
        outFile << "Type: Humidity\n";
        outFile << "Value: " << hum->getValue() << "\n";
    } else if (const Dust* dust = dynamic_cast<const Dust*>(sensor)) {
        outFile << "Type: Dust\n";
        outFile << "Value: " << dust->getValue() << "\n";
    }
    outFile << "----\n";
}


//method to load sensors from txt file
void MainWindow::loadSensorFromTxt(std::ifstream& inFile) {
    std::string line;
    u_int id = 0;
    std::string name;
    std::string type;
    double value = 0.0;

    while (std::getline(inFile, line)) {
        if (line.find("ID:") != std::string::npos) {
            id = std::stoi(line.substr(4));
        } else if (line.find("Name:") != std::string::npos) {
            name = line.substr(6);
        } else if (line.find("Type:") != std::string::npos) {
            type = line.substr(6);
        } else if (line.find("Value:") != std::string::npos) {
            value = std::stod(line.substr(7));
        } else if (line.find("----") != std::string::npos) {
            Sensor* sensor = nullptr;
            if (type == "Temperature") {
                sensor = sensorManager->createTempSensor(id, name, value);
            } else if (type == "Humidity") {
                sensor = sensorManager->createHumSensor(id, name, value);
            } else if (type == "Dust") {
                sensor = sensorManager->createDustSensor(id, name, value);
            }

            if (sensor) {
                sensorManager->addSensor(std::unique_ptr<Sensor>(sensor));
            }

            //reset variables for the next sensor
            id = 0;
            name = "";
            type = "";
            value = 0.0;
        }
    }
}
