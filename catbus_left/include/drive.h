#ifndef _MY_DRIVE_HEADER_DEFINED_YEAH_ 
#define _MY_DRIVE_HEADER_DEFINED_YEAH_
#include "robot_config.h"

double drive_curve(double x);
void drive(double lSpeed, double rSpeed, double wt);
void drive_brake(vex::brakeType Brake);

#endif