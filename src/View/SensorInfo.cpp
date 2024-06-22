#include "SensorInfo.h"

SensorInfo::SensorInfo(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* infoLayout = new QHBoxLayout();
    QVBoxLayout* labelsLayout = new QVBoxLayout();

    sensor_name = new QLabel("Name: ", this);
    sensor_id = new QLabel("ID: ", this);
    sensor_type = new QLabel("Type: ", this);
    sensor_value = new QLabel("Value: ", this);

    labelsLayout->addWidget(sensor_name);
    labelsLayout->addWidget(sensor_id);
    labelsLayout->addWidget(sensor_type);
    labelsLayout->addWidget(sensor_value);

    modifyButton = new QPushButton("Modify", this);

    infoLayout->addLayout(labelsLayout);
    infoLayout->addWidget(modifyButton);

    mainLayout->addLayout(infoLayout);

    setLayout(mainLayout);

    connect(modifyButton, &QPushButton::clicked, this, &SensorInfo::onModifyButtonClicked);
}

//update the sensor information
void SensorInfo::update(Sensor* sensor) {
    if (sensor) {
        sensor_name->setText("Name: " + QString::fromStdString(sensor->getName()));
        sensor_id->setText("ID: " + QString::number(sensor->getId()));

        //update with specific type and value
        if (dynamic_cast<Temperature*>(sensor)) {
            sensor_type->setText("Type: Temperature");
            sensor_value->setText("Value: " + QString::number(dynamic_cast<Temperature*>(sensor)->getValue()) + " °C");
        } else if (dynamic_cast<Humidity*>(sensor)) {
            sensor_type->setText("Type: Humidity");
            sensor_value->setText("Value: " + QString::number(dynamic_cast<Humidity*>(sensor)->getValue()) + " %");
        } else if (dynamic_cast<Dust*>(sensor)) {
            sensor_type->setText("Type: Dust");
            sensor_value->setText("Value: " + QString::number(dynamic_cast<Dust*>(sensor)->getValue()) + " mg/m³");
        }
    } else {
        sensor_name->setText("Name: ");
        sensor_id->setText("ID: ");
        sensor_type->setText("Type: ");
        sensor_value->setText("Value: ");
    }
}

//method that emits a signal when the modify button is clicked
void SensorInfo::onModifyButtonClicked() {
    emit modifyClicked(); //emit a signal to be caught by the MainWindow
}
