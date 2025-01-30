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
    //  drive(60, 60, 100);
    //drive(-60, -60, 25);
    this_thread::sleep_for(300);
    conveyor.spin(fwd, 150, vex::velocityUnits::pct);
    this_thread::sleep_for(300);
    // drive(60, 60, 200);
    drive(60, -60, 600);
    drive_brake(brake);
    this_thread::sleep_for(150);
    intake_wheels.spin(fwd, 75, vex::velocityUnits::pct);
    drive(70, 70, 575);
    cam.takeSnapshot(red, blue);
    Brain.resetTimer();
    if(cam.objectCount >= 1) {Brain.Screen.print("objects detected");}
    while(cam.objectCount < 1) {
        cam.takeSnapshot(red, blue);
        drive(20, 20, 75);
        this_thread::sleep_for(50);
        if(Brain.timer(sec) >= 3) {
            Brain.Screen.print("auto drive time out");
            break;
        }
    }
    intake_wheels.stop();
    drive_brake(coast);
    this_thread::sleep_for(300);
    conveyor.stop();
    intake_wheels.spinFor(200, vex::timeUnits::msec, -75, vex::velocityUnits::pct);
}
// get side goal
// score preset ring in goal
// collect 2 other rings (middle, corner) & score in goal
// touch ladder