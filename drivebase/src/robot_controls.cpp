#include "robot_controls.h"

using namespace vex;

void usercontrol(void) {  
  brakeType driveBrake = coast; // ???
  //devices_check(); 
  Arm_State arm_state = intake;
  while (1) // keeps checking the controller in a loop to get updates on whether or not its being moved
  { // the drive_brake, voltDrive, and driveCurve methods are in drive.cpp
    arm_state = arm_controls(arm_state);
    if ((abs(Controller.Axis3.position(pct)) < 2) && (abs(Controller.Axis2.position(pct)) < 2)) {
      drive_brake(driveBrake);
    }
    else {
      if(arm_state == intake) {
        volt_drive(drive_curve(Controller.Axis3.position()), drive_curve(Controller.Axis2.position()), 0); // is wait time supposed to be 0??
      }
      else {
        volt_drive(-drive_curve(Controller.Axis3.position()), -drive_curve(Controller.Axis2.position()), 0);
      }
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
          Brain.Screen.print("switched to arm");
          return arm;
        }
        else if(Controller.ButtonR1.pressing()) {
          intake_wheels.spin(directionType::fwd, 50, velocityUnits::pct);
          conveyor.spin(directionType::fwd, 50, velocityUnits::pct);
        }
        else if(Controller.ButtonR2.pressing()) {
          intake_wheels.spin(directionType::fwd, -50, velocityUnits::pct);
          conveyor.spin(directionType::fwd, -50, velocityUnits::pct);
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
            intake_wheels.spinFor(fwd, 100, msec); // might need to reverse & adjust time
        }
        else {
          intake_arm.stop(vex::brakeType::hold);
          intake_wheels.stop(vex::brakeType::hold);
        }
        return intake;
    }
    else if(state == arm) {
        if(Controller.ButtonX.pressing()) {
          Brain.Screen.print("switched to intake");
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
            // left claw piston i dunno if .open will keep it open and then if its already open u have to run the close function?
            // going to research it more :|
        }
        else if(Controller.ButtonY.pressing()) {
            // right claw piston
        }
        else {                    
          right_arm.stop(vex::brakeType::hold);
          left_arm.stop(vex::brakeType::hold); // im assuming its okay to group them here :/
        }
        return arm;
    }
    else {
        Brain.Screen.print("how dare you >:C");
        return intake;
    }
}
