#include "Temperature.h"
#include<random>

//Temperature constructor
Temperature::Temperature(const u_int id, const string& name, double value) : Sensor(id, name), value(value) {}

//method that calculates the temperature value
double Temperature::calculateTempValue() const {
    //non-deterministic random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    //interval between -10.0 and 40.0
    uniform_real_distribution<> dis(-10.0,40.0);
    double value = dis(gen);

    return value;
}

//method that returns the temperature value
double Temperature::getValue() const {
    return value;
}

//method that sets the temperature value
void Temperature::setValue(double newValue) {
    value = newValue;
}


//method that accepts a SensorVisitor
void Temperature::accept(SensorVisitor& visitor) {
    visitor.visit(*this); // Chiama il metodo visit del visitor passando se stesso come parametro
}

