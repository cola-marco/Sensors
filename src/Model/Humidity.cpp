#include "Humidity.h"
#include <random>

//Humidity constructor
Humidity::Humidity(const u_int id, const string& name, double value)
    : Sensor(id, name), value(value) {}

//method that calculates the humidity's value
double Humidity::calculateHumValue() const {
    //non-deterministic random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    //generates a casual value between 0.0 and 100.0 to represent the humidity's percentage
    uniform_real_distribution<> dis(0.0,100.0);
    double value = dis(gen); //generates the value

    return value;
}

//method that returns the humidity's value
double Humidity::getValue() const {
    return value;
}

//method that sets the humidity's value
void Humidity::setValue(double newValue) {
    value = newValue;
}

//method that accepts a SensorVisitor
void Humidity::accept(SensorVisitor& visitor) {
    visitor.visit(*this); // Chiama il metodo visit del visitor passando se stesso come parametro
}

