// pragma for processing the drive.h one time (if it notices if it's already processed this it wont do it again :D)
#ifndef _MY_DRIVE_HEADER_DEFINED_YEAH_ 
#define _MY_DRIVE_HEADER_DEFINED_YEAH_

#include "vex.h"
#include "robot_config.h"

using namespace vex;

double drive_curve(double x);
void volt_drive(double lSpeed, double rSpeed, double wt);
void drive_brake(vex::brakeType Brake);
void twirl();

#endif