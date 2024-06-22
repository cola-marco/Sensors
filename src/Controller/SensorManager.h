#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include "Model/Sensor.h"
#include <Model/Sensor.h>
#include "Model/Temperature.h"
#include "Model/Humidity.h"
#include "Model/Dust.h"
#include <memory>
#include <vector>
#include<algorithm>


//Controller: manages the sensors
class SensorManager {
private:
    vector<std::unique_ptr<Sensor>> sensors;
public:
    SensorManager() = default;

    Temperature* createTempSensor(const u_int id, const string& name, double value);
    Humidity* createHumSensor(const u_int id, const string& name, double value);
    Dust* createDustSensor(const u_int id, const string& name, double value);

    void addSensor(std::unique_ptr<Sensor> sensor);
    void removeSensor(const u_int id);
    void updateSensor(const u_int id, const string& newName);

    Sensor* searchSensorById(const u_int id);
    Sensor* searchSensorByName(const string& name);
    const std::vector<std::unique_ptr<Sensor>>& getSensors() const;

    void clearSensors();//cleans the vector
};

#endif // SENSORMANAGER_H
