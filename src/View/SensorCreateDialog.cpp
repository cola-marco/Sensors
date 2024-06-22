#include "SensorCreateDialog.h"

SensorCreateDialog::SensorCreateDialog(QWidget *parent) : QDialog(parent) {

    QLabel *nameLabel = new QLabel("Enter Sensor Name:", this);
    sensorNameLineEdit = new QLineEdit(this);

    tempRadioButton = new QRadioButton("Temperature Sensor", this);
    humRadioButton = new QRadioButton("Humidity Sensor", this);
    dustRadioButton = new QRadioButton("Dust Sensor", this);

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(sensorNameLineEdit);
    mainLayout->addWidget(tempRadioButton);
    mainLayout->addWidget(humRadioButton);
    mainLayout->addWidget(dustRadioButton);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &SensorCreateDialog::onOkButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

//get the sensor type
QString SensorCreateDialog::getSelectedSensorType() const {
    if (tempRadioButton->isChecked()) {
        return "Temperature";
    } else if (humRadioButton->isChecked()) {
        return "Humidity";
    } else if (dustRadioButton->isChecked()) {
        return "Dust";
    }
    return "";
}

//get the sensor name
QString SensorCreateDialog::getSensorName() const {
    return sensorNameLineEdit->text();
}

//function that checks if the sensor name is empty
void SensorCreateDialog::onOkButtonClicked() {
    if (!sensorNameLineEdit->text().isEmpty()) {
        accept();
    }
}

