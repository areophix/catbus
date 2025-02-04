#include "robot_config.h"

extern controller Controller;
struct Cyl_states;

enum Arm_State {intake, arm};

void usercontrol(void);
Arm_State arm_controls(Arm_State state, Cyl_states cyl);
Cyl_states clamp_controls(Cyl_states state);