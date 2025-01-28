#include "robot_config.h"
#include "robot_controls.h"
#include "drive.h"

using namespace vex;

void autonomous() {
    clamp.open();
    drive(-80, -80, 675);
    drive_brake(coast);
    this_thread::sleep_for(150);
    clamp.close();
    this_thread::sleep_for(300);
    //drive(60, 60, 100);
    //drive(-60, -60, 25);
    this_thread::sleep_for(300);
    conveyor.spinFor(350, msec, 150, vex::velocityUnits::pct);
    this_thread::sleep_for(300);
    // drive(60, 60, 200);
    drive(60, -60, 575);
    drive_brake(brake);
}
// get side goal
// score preset ring in goal
// collect 2 other rings (middle, corner) & score in goal
// touch ladder