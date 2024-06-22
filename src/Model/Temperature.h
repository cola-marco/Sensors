#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "Sensor.h"

class Temperature: public Sensor {
private:
    double value;
public:
    Temperature(const u_int id, const string& name, double value);

    double calculateTempValue() const;

    double getValue() const;
    void setValue(double newValue);

    virtual void accept(SensorVisitor& visitor) override;
};

#endif // TEMPERATURE_H
