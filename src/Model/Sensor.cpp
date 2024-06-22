#include "Sensor.h"

//sensor constructor
Sensor::Sensor(const u_int id, const string& name) :
    name(name), id(id){}

//method that returns the Sensor's ID
u_int Sensor::getId() const {
    return id;
}

//method that returns the Sensor's Name
string Sensor::getName() const {
    return name;
}

//method that sets the Sensor's Name
void Sensor::setName(const string& newName) {
    name = newName;
}
