#include "drive.h"

using namespace vex;

double drive_curve(double x) {
    return pow(x,2)/100 * (x/fabs(x));
}

void drive(double lSpeed, double rSpeed, double wt) {
    LF.spin(forward, lSpeed * 120, voltageUnits::mV);
    LB.spin(forward, lSpeed * 120, voltageUnits::mV);

    RF.spin(forward, rSpeed * 120, voltageUnits::mV);
    RB.spin(forward, rSpeed * 120, voltageUnits::mV);
    wait(wt, msec);
}

void drive_brake(vex::brakeType Brake) {
    LF.stop(Brake);
    RF.stop(Brake);
    LB.stop(Brake);
    RB.stop(Brake);
}