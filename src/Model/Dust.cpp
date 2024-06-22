#include "Dust.h"

//Dust constructor
Dust::Dust(const u_int id, const string& name, double value)
    : Sensor(id, name), value(value){}

//calculates the average PM10 concentrations in the air in µg/m³
double Dust::calculateDustValue() const {
    //non-deterministic random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    //interval between 0.0 and 50.0 µg/m³
    uniform_real_distribution<> dis(0.0,50.0);
    double value = dis(gen);

    return value;
}

//method that returns the Dust's value
double Dust::getValue() const {
    return value;
}

//method that sets the Dust's value
void Dust::setValue(double newValue) {
    value = newValue;
}


//method that accepts a SensorVisitor
void Dust::accept(SensorVisitor& visitor) {
    visitor.visit(*this); //calls the visit method calling himself as the parameter
}

