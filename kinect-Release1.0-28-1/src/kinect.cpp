/*
	Kinect CLNUI Sample Code
	Alex Olwal, Jan 2011 (olwal@mit.edu)
*/

#include "Kinect.h"

bool 
Kinect::init()
{
	msg("Initializing...");

//	LoadLibrary("CLNUIDevice.dll");
	int i = GetNUIDeviceCount();

	if (i >= 0)
	{
		serial = GetNUIDeviceSerial(0);
		PCHAR serial_pchar = (PCHAR)serial.c_str();

		motor = CreateNUIMotor(serial_pchar);
		camera = CreateNUICamera(serial_pchar);

		initialized = true;
	}

	wasOK( initialized );

	return initialized;
}

bool 
Kinect::start()
{
	if (!initialized || !camera)
		return false;

	msg("Starting camera...");
	return wasOK( StartNUICamera(camera) );
}

void 
Kinect::stop()
{
	if (motor)
	{	
		msg("Turning off motor LED...");	wasOK( SetNUIMotorLED(motor, 0) );	
		msg("Destroying motor...");			wasOK( DestroyNUIMotor(motor) );	
		motor = NULL;
	}

	if (camera)
	{
		msg("Stopping camera...");		wasOK( StopNUICamera(camera) );
		Sleep(500);
		msg("Destroying camera...");	wasOK( DestroyNUICamera(camera) );
		camera = NULL;
	}

	initialized = false;
}

Kinect::Kinect() : initialized(false)
{
	motor = NULL;
	camera = NULL;
}

Kinect::~Kinect()
{	stop();	}

bool 
Kinect::wasOK(bool ok)
{	cout << ( ok ? "[OK]" : "[NOK]" ) << endl;	return ok;	}

void 
Kinect::msg(char * text)
{	cout << "Kinect: " << text; } 