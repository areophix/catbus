#include "vex.h"
#include "drive.h"
#include <vector>

using namespace vex;
using namespace std;

extern controller Controller;

enum Arm_State {intake, arm};

void usercontrol(void);
Arm_State arm_controls(Arm_State state);
vector<int> clamp_controls(vector<int> state);