#ifndef VALUECALCULATORVISITOR_H
#define VALUECALCULATORVISITOR_H

#include "SensorVisitor.h"
#include "Model/Temperature.h"
#include "Model/Humidity.h"
#include "Model/Dust.h"

class ValueCalculatorVisitor : public SensorVisitor {
public:
    void visit(Temperature& tempSensor) override;
    void visit(Humidity& humSensor) override;
    void visit(Dust& dustSensor) override;
};

#endif // VALUECALCULATORVISITOR_H
