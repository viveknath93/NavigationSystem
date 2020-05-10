/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.H
* Author          : Viveknath Thulasi
* Description     : include file for CGPSSensor operating to get current location of user
*
*
****************************************************************************/
//System Include Files
#include<iostream>

//Own Include Files
#include "CGPSSensor.h"
#include "CWaypoint.h"

using namespace std;
//Method Implementations

CGPSSensor::CGPSSensor()
{

}

/**
 * Gets the current position of the input from user
 * @param	None
 * @returnvalue	returns the current position
 * */
CWaypoint CGPSSensor::getCurrentPosition()
{
	double current_lattitude, current_longitude;

	cout << "\n\n GPS Sensor : Enter current position Manually \n";
	cout << "Enter latitude: ";
	cin >> current_lattitude;
	cout << "Enter longitude: ";
	cin >> current_longitude;

	CWaypoint current_position("Current_Position_HrsMinSec", current_lattitude,current_longitude);

	return current_position;
}
