/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CWAYPOINT.CPP
 * Author          : Viveknath Thulasi
 * Description     : OPeration with elements of a Location are added to this file
 *
 *
 ****************************************************************************/

//System Include Files
#include <iostream>

//Own Include Files
#include "CWaypoint.h"

using namespace std;

// #define functions
// More the value of log_level, more detail the report becomes,
// here LOGLEVEL 0 -> lesser info
//      LOGLEVEL 1 -> more info
#define EARTH_RADIUS 6378.37
#define LOGLEVEL 0 //Exercise 1.1C Verbose

#if LOGLEVEL == 1
#define SHOWADDRESS 1
#endif

#define DEG2RAD 0.0174532 // (PI/180)

//Global variables
int variable_limit_flag = LATTITUDE_LONGITUDE_IN_LIMIT;

//Method Implementations
/**
 * Constructor to initialise and set the value of the
 * parameters of CWaypoint object
 * @param	string name 	Name of the waypoint (IN)
 * @param	double latitude	latitude of waypoint (IN)
 * @param	double longitude longitude of waypoint (IN)
 * */
CWaypoint::CWaypoint(string name, double latitude, double longitude)
{
	set(name, latitude, longitude);

#ifdef SHOWADDRESS
	cout << "Value of name : " << this->m_name << endl;
	cout << "Value of latitude : " << this->m_latitude << endl;
	cout << "Value of longitude : " << this->m_longitude << "\n\n";

	cout << "Address of the object : " << this << endl;
	cout << "address of name : " << &this->m_name << endl;
	cout << "address of latitude : " << &this->m_latitude << endl;
	cout << "address of longitude : " << &this->m_longitude << "\n\n";
#endif

}

/**
 * set function to initialise and set the value of the
 * parameters of CWaypoint object
 * @param	string name 	Name of the waypoint (IN)
 * @param	double latitude	latitude of waypoint (IN)
 * @param	double longitude longitude of waypoint (IN)
 * @returnvalue void
 * */

void CWaypoint::set(string name, double latitude, double longitude)
{

	variable_limit_flag = LATTITUDE_LONGITUDE_IN_LIMIT;
	this->m_name = name;
	if (latitude >= -90 && latitude <= 90)
	{
		this->m_latitude = latitude;
	}
	else
	{
		cout<<"\nERROR in "<<__FUNCTION__<<" : Latitude not in prescribed limits, resetting to 0!";
		this->m_latitude = 0;
		variable_limit_flag = LATTITUDE_LONGITUDE_NOT_IN_LIMIT;
	}

	if(longitude >= -180 && longitude <= 180)
	{
		this->m_longitude = longitude;
	}
	else
	{
		cout<<"\nERROR in "<<__FUNCTION__<<" : Longitude not in prescribed limits, resetting to 0!!";
		this->m_longitude = 0;
		variable_limit_flag = LATTITUDE_LONGITUDE_NOT_IN_LIMIT;
	}

}

/**
 * getter function to get the value of
 * name of CWaypoint object
 * @returnvalue	string name (OUT)
 * */

string CWaypoint::getName()
{
	return this->m_name;
}

/**
 * getter function to get the value of
 * latitude of CWaypoint object instance
 * @returnvalue	double m_latitude (OUT)
 * */

double CWaypoint::getLatitude()
{
	return this->m_latitude;
}

/**
 * getter function to get the value of
 * Longitude of CWaypoint object instance
 * @returnvalue	double m_longitude (OUT)
 * */

double CWaypoint::getLongitude()
{
	return this->m_longitude;
}


/**
 * Function to get all the data of waypoint and set the value of the
 * parameters of CWaypoint object
 * @param	string& name 	Name of the waypoint (OUT)
 * @param	double& latitude	latitude of waypoint (OUT)
 * @param	double& longitude longitude of waypoint (OUT)
 * @returnvalue void
 * */

void CWaypoint::getAllDataByReference(string& name, double & latitude,double & longitude)
{

#ifdef SHOWADDRESS
	cout << "Address of data from class parameters " << &name <<" "<< &latitude << " " << &longitude << "\n";
#endif

	name = this->m_name;
	latitude = this->m_latitude;
	longitude = this->m_longitude;
}

/*
 * Function to calculate distance between 2 points
 * @param	const CWaypoint &wp reference
 * @returnvalue distance	distance 2  */
double CWaypoint::calculateDistance(const CWaypoint& wp)
{
	double distance = 0.0, component;
	if (variable_limit_flag == LATTITUDE_LONGITUDE_IN_LIMIT)
	{
		component = acos(
				sin(DEG2RAD * this->m_latitude) * sin(DEG2RAD * wp.m_latitude)
						+ cos(DEG2RAD * this->m_latitude)
								* cos(DEG2RAD * wp.m_latitude)
								* cos(
										DEG2RAD * wp.m_longitude
												- DEG2RAD * this->m_longitude));
		distance = EARTH_RADIUS * component;

		cout << "\nDistance between " << this->m_name << " and " << wp.m_name<< " : " << distance;
	}
	else if (variable_limit_flag == LATTITUDE_LONGITUDE_NOT_IN_LIMIT)
	{
		cout<<"ERROR in "<<__FUNCTION__<<": Distance is not calculated as Latitude and longitude values are not in limits";
		return -1;
	}
	else
	{
		return 0;
	}
	return distance;
}

/*
 * funtion to print the CWaypoint values
 * @param int format	-format of printing deg or minutes and seconds (IN)
 * @returnvalue void
 * */
void CWaypoint::print(int format)
{
	int deg, mm;
	double ss;
	if (format == DEGREE) // degree format
	{
		cout <<endl<< this->m_name << " on latitude = " << this->m_latitude
				<< " on longitude = " << this->m_longitude << endl;
	}
	else if (format == MMSS) // deg min sec format
	{
		transformLatitude2degmmss(deg, mm, ss);
		cout <<endl<< this->m_name << " on latitude = " << deg << "deg " << mm
				<< "min " << ss << "s ";
		transformLongitude2degmmss(deg, mm, ss);
		cout << "and longitude = " << deg << "deg " << mm << "min " << ss
				<< "s"<<endl;
	}
	else
	{
		//Invalid format i.e 1 or 2
		cout <<"\nERROR in "<<__FUNCTION__<<" : Invalid format to print: valid format are : ( DEGREE/MMSS )";
	}

}

/**
 * Function to transform longitude value to degrees, minutes and seconds using reference
 * @param	int & deg 	degree value of longitude (OUT)
 * @param	int & mm	minutes value of longitude (OUT)
 * @param	double & ss longitude of longitude (OUT)
 * @returnvalue void
 * */
void CWaypoint::transformLongitude2degmmss(int & deg, int & mm, double & ss)
{
	deg = floor(this->m_longitude);
	mm = floor((this->m_longitude - deg) * 60);
	ss = ((this->m_longitude - deg) * 60 - mm) * 60;
}

/**
 * Function to transform latitude value to degrees, minutes and seconds using reference
 * @param	int & deg 	degree value of latitude (OUT)
 * @param	int & mm	minutes value of latitude (OUT)
 * @param	double & ss longitude of latitude (OUT)
 * @returnvalue void
 * */
void CWaypoint::transformLatitude2degmmss(int & deg, int & mm, double & ss)
{
	deg = floor(this->m_latitude);
	mm = floor((this->m_latitude - deg) * 60);
	ss = ((this->m_latitude - deg) * 60 - mm) * 60;
}
