#include "ValueCalculatorVisitor.h"

void ValueCalculatorVisitor::visit(Temperature& tempSensor) {
    tempSensor.setValue(tempSensor.calculateTempValue());
}

void ValueCalculatorVisitor::visit(Humidity& humSensor) {
    humSensor.setValue(humSensor.calculateHumValue());
}

void ValueCalculatorVisitor::visit(Dust& dustSensor) {
    dustSensor.setValue(dustSensor.calculateDustValue());
}
