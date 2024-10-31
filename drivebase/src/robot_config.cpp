#include "vex.h"

using namespace vex;

// a separate file for defining devices. at some point there will be so much code that u cant put organize it all in one file
// so u can make a bunch of catagories but thats later.

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

controller Controller = controller(primary); // device names are usually capitilized cause lowercase ones are keywords
                                             // and the compiler will freak out cause it cant tell them apart
                                             
motor LF = motor(PORT1, ratio6_1, true); // brain port the device is plugged into, cartridge ratio (different 
                                         // motors have diff cartridges for speed or strength), true = reversed, false = normal
motor LB = motor(PORT2, ratio6_1, true);
motor RF = motor(PORT3, ratio6_1, false);
motor RB = motor(PORT4, ratio6_1, false);

motor left_arm = motor(PORT5, ratio36_1, true);
motor right_arm = motor(PORT6, ratio36_1, true);
motor intake_arm = motor(PORT7, ratio6_1, true);

motor intake_wheels = motor(PORT8, ratio6_1, true);
motor conveyor = motor(PORT9, ratio6_1, true);

pneumatics clamp = pneumatics(Brain.ThreeWirePort.A);
pneumatics left_claw = pneumatics(Brain.ThreeWirePort.B);
pneumatics right_claw = pneumatics(Brain.ThreeWirePort.C);
pneumatics intake_ramp = pneumatics(Brain.ThreeWirePort.D);