/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       morga                                                     */
/*    Created:      2/10/2024, 4:16:46 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "robot_controls.h"
#include "autonomous.h"
using namespace vex;
competition Competition;

void pre_auton(void) {}

int main() {
  // Set up callbacks for autonomous and driver control periods.  

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
