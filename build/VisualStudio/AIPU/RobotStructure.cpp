#include "RobotStructure.h"


RobotStructure::RobotStructure()
{

	Neck = new RobotNeck();
	LeftArm = new RobotLeftArm();
	RightArm = new RobotRightArm();
	Torso = new RobotTorso();
	MotionBase = new RobotMotionBase();
}


RobotStructure::~RobotStructure()
{
}


bool RobotStructure::setCurrentParameters()
{
	Neck->setCurrentParameters();
	LeftArm->setCurrentParameters();
	RightArm->setCurrentParameters();
	Torso->setCurrentParameters();
	MotionBase->setCurrentParameters();
	return true;
}