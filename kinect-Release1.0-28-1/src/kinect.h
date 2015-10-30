/*
	Kinect CLNUI Sample Code
	Alex Olwal, Jan 2011 (olwal@mit.edu)
*/

#pragma once

#include <CLNUIDevice.h>

#include <string>
#include <iostream>

using namespace std;

class Kinect
{
public:
	
	int devices;
	string serial;

	bool initialized;

	bool init();
	bool start();
	void stop();

	Kinect();
	~Kinect();

	CLNUIMotor motor;
	CLNUICamera camera;

	static bool wasOK(bool ok);
	static void msg(char * text);

};