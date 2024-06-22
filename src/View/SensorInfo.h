#ifndef SENSORINFO_H
#define SENSORINFO_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include "../Model/Sensor.h"
#include "../Model/Temperature.h"
#include "../Model/Humidity.h"
#include "../Model/Dust.h"

class SensorInfo : public QWidget {
    Q_OBJECT

private:
    QLabel* sensor_name;
    QLabel* sensor_id;
    QLabel* sensor_type;
    QLabel* sensor_value;

    QPushButton* modifyButton;

public:
    explicit SensorInfo(QWidget* parent = nullptr);
    void update(Sensor* sensor);

signals:
    void modifyClicked();

private slots:
    void onModifyButtonClicked();

};

#endif // SENSORINFO_H
