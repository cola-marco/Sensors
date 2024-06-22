#ifndef SENSORVISITOR_H
#define SENSORVISITOR_H

class Temperature;
class Humidity;
class Dust;

class SensorVisitor {
public:
    virtual void visit(Temperature& tempSensor) = 0;
    virtual void visit(Humidity& humSensor) = 0;
    virtual void visit(Dust& dustSensor) = 0;

    virtual ~SensorVisitor() = default;
};

#endif // SENSORVISITOR_H
