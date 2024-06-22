#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include "SensorVisitor.h"

using namespace std;

typedef unsigned int u_int;

//Model: data rappresentation of a sensor
class Sensor {
protected:
    string name;
    const u_int id;
public:
    Sensor(const u_int id, const string& name);

    u_int getId() const;
    string getName() const;
    void setName(const string& newName);

    virtual void accept(SensorVisitor& visitor) = 0;

    virtual ~Sensor() = default;
};

#endif // SENSOR_H
