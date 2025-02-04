#include "robot_config.h"
//using namespace vex;

brain Brain;

controller Controller = controller(primary); 
                                             
motor LF = motor(PORT4, ratio6_1, true); 
motor LB = motor(PORT5, ratio6_1, true);
motor RF = motor(PORT6, ratio6_1, false);
motor RB = motor(PORT7, ratio6_1, false);

motor left_arm = motor(PORT19, ratio36_1, false);
motor right_arm = motor(PORT20, ratio36_1, true);

motor intake_arm = motor(PORT2, ratio6_1, true);

motor intake_wheels = motor(PORT1, ratio6_1, false);
motor conveyor = motor(PORT11, ratio6_1, false);

pneumatics clamp = pneumatics(Brain.ThreeWirePort.A);
pneumatics arm_pistons = pneumatics(Brain.ThreeWirePort.B);

vision cam = vision(PORT20);