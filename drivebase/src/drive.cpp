#include "drive.h"

using namespace vex;

double drive_curve(double x) {
    return pow(x,2)/100 * (x/fabs(x)); // apparently "makes joysticks less sensitive at lower values" iunno i asked the guy who 
                                       // used the formula and who am i to question :D
}

void volt_drive(double lSpeed, double rSpeed, double wt) {
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

void twirl() {
    LF.spinFor(2, sec, 100, rpm); // spins for two secs
    LB.spinFor(2, sec, 100, rpm); // time, time units, velocity, velocity units

    RF.spinFor(2, sec, -100, rpm); // spins the right side's motors in the opposite direction    
    RB.spinFor(2, sec, -100, rpm); // (hence the negative velocity)
  
    // technically u could just ask the motors to go in reverse but that gets hard
    // to keep track of so normally ppl just give a negative velocity when they wanna go backward

    wait(100, msec);
}