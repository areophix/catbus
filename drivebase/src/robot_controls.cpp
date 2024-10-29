#include "robot_controls.h"

using namespace vex;

void usercontrol(void) {  
  brakeType driveBrake = coast; // ???
  devices_check(); 
  Arm_State arm_state = intake;
  while (1) // keeps checking the controller in a loop to get updates on whether or not its being moved
  { // the drive_brake, voltDrive, and driveCurve methods are in drive.cpp
    arm_state = arm_controls(arm_state);
    if (Controller.ButtonA.pressing()) { 
      twirl();
      drive_brake(driveBrake);
    }
    if ((abs(Controller.Axis3.position(pct)) < 2) && (abs(Controller.Axis2.position(pct)) < 2)) {
      // sometimes the controller's joysticks will be slightly uncentered, which will return axis values slightly > 0, 
      // which will move the motors. (the farther from the center the joysticks are, the larger value they return)

      // this if statement says that if the joysticks are slightly misaligned so that they are returning a value less than
      // 2, then they are close enough to the center to be considered a value of 0, so we brake the motors
      // this tactic is called a deadzone
      // https://wiki.purduesigbots.com/software/robotics-basics/joystick-deadzones
      drive_brake(driveBrake);
    }
    else
    {
      volt_drive(drive_curve(Controller.Axis3.position()), drive_curve(Controller.Axis2.position()), 0);
    }
    this_thread::sleep_for(15); // wait so it doesn't burn out from constantly running poor lil guy

  }
}

void devices_check() {
  if (LF.installed() && RF.installed() && LB.installed() && RB.installed())
  {
    Controller.Screen.print("devices connected :D");
  }
  else
  {
    Controller.Screen.print("a device is disconnected D:");
  }
}

Arm_State arm_controls(Arm_State state) {
    if(state == intake) {
        if(Controller.ButtonX.pressing()) {
            return arm;
        }
    }
    else if(state == arm) {
        if(Controller.ButtonX.pressing()) {
            return intake;
        }
        // ajefboeawiuewf
    }
    else {
        Brain.Screen.print("how dare you >:C");
    }
}