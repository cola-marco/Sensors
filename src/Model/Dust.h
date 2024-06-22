#ifndef DUST_H
#define DUST_H

#include "Sensor.h"
#include <random>
#include <string>

class Dust: public Sensor {
private:
    double value; //PM10 medium concentration per day in µg/m³
public:
    Dust(const u_int id, const string& name, double value);

    double calculateDustValue() const;

    double getValue() const;
    void setValue(double newValue);

    virtual void accept(SensorVisitor& visitor) override;
};

#endif // DUST_H
