#include "vex.h"
#include "drive.h"

using namespace vex;

extern controller Controller;

enum Arm_State {intake, arm};

void usercontrol(void);
Arm_State arm_controls(Arm_State state);