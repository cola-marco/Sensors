#ifndef HUMIDITY_H
#define HUMIDITY_H

#include "Sensor.h"

class Humidity: public Sensor {
private:
    double value;
public:
    Humidity(const u_int id, const string& name, double value);

    double calculateHumValue() const;

    double getValue() const;
    void setValue(double newValue);

    virtual void accept(SensorVisitor& visitor) override;
};

#endif // HUMIDITY_H
