#include "robot_controls.h"

using namespace vex;

void usercontrol(void) {  
  brakeType driveBrake = coast; // ???
  devices_check(); 
  Arm_State arm_state = intake;
  while (1) // keeps checking the controller in a loop to get updates on whether or not its being moved
  { // the drive_brake, voltDrive, and driveCurve methods are in drive.cpp
    arm_state = arm_controls(arm_state);
    if ((abs(Controller.Axis3.position(pct)) < 2) && (abs(Controller.Axis2.position(pct)) < 2)) {
      drive_brake(driveBrake);
    }
    else {
      volt_drive(drive_curve(Controller.Axis3.position()), drive_curve(Controller.Axis2.position()), 0); // is wait time supposed to be 0??
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
        else if(Controller.ButtonR1.pressing()) {
          // not sure if 5.5 watt motors are considered normal motor objects or if they have their own class
          // gonna leave this alone until we find out
        }
        else if(Controller.ButtonR2.pressing()) {

        }
        else if(Controller.ButtonL1.pressing()) {
          intake_arm.spin(directionType::fwd, 50, velocityUnits::pct);
        }
        else if(Controller.ButtonL2.pressing()) {
          intake_arm.spin(directionType::fwd, -50, velocityUnits::pct);
        }
        else if(Controller.ButtonRight.pressing()) {
            // clamp piston
        }
        else if(Controller.ButtonY.pressing()) {
            // intake pistons + short eject with intake wheel motor
        }
        else {
          intake_arm.stop(vex::brakeType::hold);
        }
    }
    else if(state == arm) {
        if(Controller.ButtonX.pressing()) {
            return intake;
        }
        else if(Controller.ButtonR1.pressing()) {
            right_arm.spin(directionType::fwd, 50, velocityUnits::pct);//raises right arm??? I have no idea if any of this works.I copied this from a youtube tutorial made in 2020 :(
        }
        else if(Controller.ButtonR2.pressing()) {
            right_arm.spin(directionType::fwd, -50, velocityUnits::pct);//lowers right arm...maybe?
        }                                                               // im pretty sure its right
        else if(Controller.ButtonL1.pressing()) {
            left_arm.spin(directionType::fwd, 50, velocityUnits::pct); // okay either the left of right arm motor has to be reversed
        }                                                               // we'll know when we test physically
        else if(Controller.ButtonL2.pressing()) {
            left_arm.spin(directionType::fwd, -50, velocityUnits::pct);
        }
        else if(Controller.ButtonRight.pressing()) {
            // left claw piston
        }
        else if(Controller.ButtonY.pressing()) {
            // right claw piston
        }
        else {                    
          right_arm.stop(vex::brakeType::hold);
          left_arm.stop(vex::brakeType::hold); // im assuming its okay to group them here :/
        }
    }
    else {
        Brain.Screen.print("how dare you >:C");
    }
}