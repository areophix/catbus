#include "robot_config.h"
#include "robot_controls.h"
#include "drive.h"

using namespace vex;

void autonomous() {
    clamp.open();
    drive(-80, -80, 700);
    drive_brake(coast);
    this_thread::sleep_for(150);
    clamp.close();
    this_thread::sleep_for(400);
    //  drive(60, 60, 100);
    //drive(-60, -60, 25);
    conveyor.spin(fwd, 125, vex::velocityUnits::pct);
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
        if(Brain.timer(sec) >= 2) {
            Brain.Screen.print("auto drive time out");
            break;
        }
    }
    intake_wheels.stop();
    drive_brake(coast);
    intake_wheels.spinFor(400, vex::timeUnits::msec, -75, vex::velocityUnits::pct);
    this_thread::sleep_for(175);
    drive(-60, 60, 550);
    drive_brake(brake);
    this_thread::sleep_for(200);
    drive(60, 60, 1000);
    drive_brake(coast);
}
// get side goal
// score preset ring in goal
// collect 2 other rings (middle, corner) & score in goal
// touch ladder