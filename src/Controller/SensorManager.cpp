#include "Controller/SensorManager.h"

//creates a Temperature Sensor and adds it to the vector
Temperature* SensorManager::createTempSensor(const u_int id, const string& name, double value) {
    return new Temperature(id, name, value);
}

//creates a Humidity Sensor and adds it to the vector
Humidity* SensorManager::createHumSensor(const u_int id, const string& name, double value) {
    return new Humidity(id, name, value);
}

//creates a Dust Sensor and adds it to the vector
Dust* SensorManager::createDustSensor(const u_int id, const string& name, double value) {
    return new Dust(id, name, value);
}

//Add a Sensor
void SensorManager::addSensor(std::unique_ptr<Sensor> sensor) {
    //std::move because we can't copy unique_ptr only transfer it's ownership
    sensors.push_back(std::move(sensor));
}

//Remove a Sensor
void SensorManager::removeSensor(const u_int id) {
    //remove_if returns an iterator to the new end of the vector
    //[id].. lambda function that checks if the id of the sensor is equal to the id passed as parameter
    auto it = std::remove_if(sensors.begin(), sensors.end(),
                             [id](const std::unique_ptr<Sensor>& sensor) {
                                 return sensor->getId() == id; });
    sensors.erase(it, sensors.end());
}

//Update a Sensor
void SensorManager::updateSensor(const u_int id, const string& newName) {
    for (const auto& sensor : sensors) {
        if (sensor->getId() == id) {
            sensor->setName(newName); // Assicurati di avere un metodo setName nella classe Sensor
            break;
        }
    }
}

//search by ID
Sensor* SensorManager::searchSensorById(const u_int id) {
    for (const auto& sensor : sensors) {
        if (sensor->getId() == id) {
            return sensor.get();
        }
    }
    return nullptr;
}

//search by name
Sensor* SensorManager::searchSensorByName(const string& name) {
    for (const auto& sensor : sensors) {
        if (sensor->getName() == name) {
            return sensor.get();
        }
    }
    return nullptr;
}

//return the vector of sensors
const std::vector<std::unique_ptr<Sensor>>& SensorManager::getSensors() const {
    return sensors;
}

//clear the vector
void SensorManager::clearSensors() {
    sensors.clear();
}

