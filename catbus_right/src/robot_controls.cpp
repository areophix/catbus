#include "robot_controls.h"
#include <vector>
#include <iostream>

using namespace vex;
using namespace std;

struct Cyl_states {
  int clamp;
  int arm;
  int adj_spd;
};

void usercontrol(void) {  
  brakeType driveBrake = brake;
  //devices_check(); 
  Arm_State arm_state = intake;
  Cyl_states cyl_state;
  cyl_state.clamp = 0;
  cyl_state.arm = 0;
  cyl_state.adj_spd = 125;
 //closed  
  while (1) // keeps checking the controller in a loop to get updates on whether or not its being moved
  { // the drive_brake, voltDrive, and driveCurve methods are in drive.cpp
    arm_state = arm_controls(arm_state, cyl_state);
    cyl_state = clamp_controls(cyl_state);
    if ((abs(Controller.Axis3.position(pct)) < 2) && (abs(Controller.Axis2.position(pct)) < 2)) {
      drive_brake(driveBrake);
    }
    else {
      if(arm_state == intake) {
        drive(drive_curve(Controller.Axis3.position()), drive_curve(Controller.Axis2.position()), 0);
      }
      else {
        drive(-drive_curve(Controller.Axis3.position()), -drive_curve(Controller.Axis2.position()), 0);
      }
    }
    this_thread::sleep_for(20); 
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

Cyl_states clamp_controls(Cyl_states state) {
  if(Controller.ButtonRight.pressing()) {
    if (state.clamp) { 
      clamp.close();
      state.clamp = 0;
    }
    else {
      clamp.open();
      state.clamp = 1;
    }
  }
  else if(Controller.ButtonY.pressing()) {
    if (state.arm) { // if arm cyl is open
      arm_pistons.close();
      state.arm = 0;
      state.adj_spd = 125;
      this_thread::sleep_for(150);
      drive(-50, -50, 250); // drive back 1/2 spd for 250ms
      drive_brake(brake);
    }
    else {
      arm_pistons.open();
      state.arm = 1;
      state.adj_spd = 50;
    }
  } 
    //hey stupid, no button control must maintain state
  this_thread::sleep_for(100);
  return state;
}

Arm_State arm_controls(Arm_State state, Cyl_states cyl) {
    if(state == intake) {
        if(Controller.ButtonX.pressing()) {
          Brain.Screen.print("switched to climb");
          return arm;
        }
        else if(Controller.ButtonR1.pressing()) {
          intake_wheels.spin(directionType::fwd, 75, velocityUnits::pct);
          conveyor.spin(directionType::fwd, cyl.adj_spd, velocityUnits::pct);
        }
        else if(Controller.ButtonR2.pressing()) {
          intake_wheels.spin(directionType::fwd, -75, velocityUnits::pct);
          conveyor.spin(directionType::fwd, -cyl.adj_spd, velocityUnits::pct);
        }
        else if(Controller.ButtonL1.pressing()) {
          intake_arm.spin(directionType::fwd, 25, velocityUnits::pct);
        }
        else if(Controller.ButtonL2.pressing()) {
          intake_arm.spin(directionType::fwd, -25, velocityUnits::pct);
        }
        else {
          intake_arm.stop(vex::brakeType::hold);
          intake_wheels.stop(vex::brakeType::hold);
          conveyor.stop(vex::brakeType::hold);
        }
        return intake;
    }
    else if(state == arm) {
        if(Controller.ButtonX.pressing()) {
          Brain.Screen.print("switched to intake");
          return intake;
        }
        else if(Controller.ButtonR1.pressing()) {
            right_arm.spin(directionType::fwd, 50, velocityUnits::pct);
            left_arm.spin(directionType::fwd, 50, velocityUnits::pct);//raises right arm??? I have no idea if any of this works.I copied this from a youtube tutorial made in 2020 :(
        }
        else if(Controller.ButtonR2.pressing()) {
            right_arm.spin(directionType::fwd, -50, velocityUnits::pct);
            left_arm.spin(directionType::fwd, -50, velocityUnits::pct);//lowers right arm...maybe?
        }
        else if(Controller.ButtonL1.pressing()) {
          intake_arm.spin(directionType::fwd, 25, velocityUnits::pct);
        }
        else if(Controller.ButtonL2.pressing()) {
          intake_arm.spin(directionType::fwd, -25, velocityUnits::pct);
        }
        else if(Controller.ButtonY.pressing()) {
            // arm adjustment piston(s)
        }
        else {                    
          right_arm.stop(vex::brakeType::hold);
          left_arm.stop(vex::brakeType::hold);
          intake_arm.stop(vex::brakeType::hold);
        }
        return arm;
    }
    else {
        Brain.Screen.print("how dare you >:C");
        return intake;
    }
}
