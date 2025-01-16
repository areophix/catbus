#include "robot_controls.h"
#include <vector>
#include <iostream>

using namespace vex;
using namespace std;

vector<int> clamp_state = {0, 0};
int adj_spd;

void usercontrol(void) {  
  brakeType driveBrake = coast; // ???
  //devices_check(); 
  Arm_State arm_state = intake;
 //closed  
  while (1) // keeps checking the controller in a loop to get updates on whether or not its being moved
  { // the drive_brake, voltDrive, and driveCurve methods are in drive.cpp
    arm_state = arm_controls(arm_state);
    clamp_state = clamp_controls(clamp_state);
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

std::vector<int> clamp_controls(std::vector<int> state) {
  if(Controller.ButtonRight.pressing()) {
    if (state[0]) { 
      clamp.close();
      state.insert(state.begin(), 0);
      state.erase(state.begin()+1);
    }
    else {
      clamp.open();
      state.insert(state.begin(), 1);
      state.erase(state.begin()+1);
    }
  }
  else if(Controller.ButtonY.pressing()) {
    if(state[1]) {
      arm_pistons.close();
      state.insert(state.begin()+1, 0);
      state.erase(state.begin()+2);
    }
    else {
      arm_pistons.open();
      state.insert(state.begin()+1, 1);
      state.erase(state.begin()+2);
    }
  } 
    //hey stupid, no button control must maintain state
  this_thread::sleep_for(100);
  return state;
}

Arm_State arm_controls(Arm_State state) {
    if(clamp_state[1]) {
      adj_spd = 50;
    } else {
      adj_spd = 100;
    }
    if(state == intake) {
        if(Controller.ButtonX.pressing()) {
          Brain.Screen.print("switched to climb");
          return arm;
        }
        else if(Controller.ButtonR1.pressing()) {
          intake_wheels.spin(directionType::fwd, 75, velocityUnits::pct);
          conveyor.spin(directionType::fwd, adj_spd, velocityUnits::pct);
        }
        else if(Controller.ButtonR2.pressing()) {
          intake_wheels.spin(directionType::fwd, -75, velocityUnits::pct);
          conveyor.spin(directionType::fwd, -adj_spd, velocityUnits::pct);
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
