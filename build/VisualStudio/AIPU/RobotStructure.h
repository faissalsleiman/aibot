#include "RobotNeck.h"
#include "RobotLeftArm.h"
#include "RobotRightArm.h"
#include "RobotTorso.h"
#include "RobotMotionBase.h"

#pragma once
class RobotStructure
{
public:
	RobotNeck * Neck;
	RobotLeftArm * LeftArm;
	RobotRightArm * RightArm;
	RobotTorso * Torso;
	RobotMotionBase * MotionBase;



	RobotStructure();
	~RobotStructure();
	bool setCurrentParameters(); //Sets all the parameters of the servos to their current parameters (polled) so they can be retrieved directly

};

