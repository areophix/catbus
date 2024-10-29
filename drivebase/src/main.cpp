/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       morga                                                     */
/*    Created:      2/10/2024, 4:16:46 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// highlight and right click any keywords that u dont recognize; u can click "go to definition" on the menu that
// pops up and you'll probably see what it's for.

// lots of keywords (probably not all tho) are listed in this website too:
// https://www.robotmesh.com/studio/content/docs/vexv5-cpp//html/index.html

// some other cool vex programming and mechanical stuff is in here but the programming stuff is mostly for autonomous 
// so it probably wont be in this program :/
// https://wiki.purduesigbots.com/

#include "vex.h"
#include "robot_config.h"
#include "robot_controls.h"

using namespace vex;

// A global instance of competition
competition Competition;

// these other functions  (aka methods) are left blank cause this program is only for a simple 4 motor driver controlled drivebase.
// the functions are used for actual competitions where they'll automatically run these. 

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.  
  Brain.Screen.print("hi!"); 

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
