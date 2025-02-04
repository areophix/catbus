#include "autonomous.h"
using namespace vex;

void camera(float timeout) {
    cam.takeSnapshot(red, blue);
    Brain.resetTimer();
    if(cam.objectCount >= 1) {Brain.Screen.print("objects detected");}
    while(cam.objectCount < 1) {
        cam.takeSnapshot(red, blue);
        drive(35, 35, 75);
        if(Brain.timer(sec) >= timeout) {
            Brain.Screen.print("auto drive time out"); // why is it never seeing anything :C
            break;
        }
    }
}

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
    camera(1.5);
    intake_wheels.stop();
    drive_brake(coast);
    intake_wheels.spin(directionType::rev, 75, vex::velocityUnits::pct);
    this_thread::sleep_for(500);
    intake_wheels.stop();
    drive(-60, 60, 500);
    drive_brake(brake);
    this_thread::sleep_for(200);
    drive(60, 60, 1300);
    drive_brake(coast);
    
    // starting wall stake scoring
    // arm_pistons.open();
    // conveyor.spin(fwd, 50, pct);
    // intake_wheels.spin(directionType::fwd, 75, vex::velocityUnits::pct);
    // camera(1.5);
    // this_thread::sleep_for(1000);
    // conveyor.stop();
    // drive(-60, -60, 300);
    // this_thread::sleep_for(100);
    // drive(-60, 60, )
}
// get side goal
// score preset ring in goal
// collect 2 other rings (middle, corner) & score in goal
// touch ladder