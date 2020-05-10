/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWAYPOINT.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>
#include<math.h> // For using floor funtions
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
	* insertion '<<' operator overloading to efficient printing for Waypoint objects.
	*
	* @param out the reference in which the output string is returned
	* @param wp_const the reference variable which data needs to be printed
	* @return output of insertion data
	*/
ostream & operator << (ostream &out, CWaypoint & wp_const)
{
	int deg, mm;
	double ss;
	wp_const.transformLatitude2degmmss(deg,mm,ss);
	out << wp_const.getName() << " on latitude = " << deg << "deg " << mm
						<< "min " << ss << "s ";


	wp_const.transformLongitude2degmmss(deg, mm, ss);
	out << "and longitude = " << deg << "deg " << mm << "min " << ss
						<< "s"<<endl;

    return out;
}
/**
 * getter function to get the value of
 * name of CWaypoint object
 * @returnvalue	string name (OUT)
 * */
string CWaypoint::getName() const
{
	return this->m_name;
}

/**
 * getter function to get the value of
 * Latitude of CWaypoint object
 * @returnvalue	Double latitude (OUT)
 * */
double CWaypoint::getLatitude()
{
	return this->m_latitude;
}

/**
 * getter function to get the value of
 * longitude of CWaypoint object
 * @returnvalue	Double longitude (OUT)
 * */
double CWaypoint::getLongitude(){
	return this->m_longitude;

}

/**
 *  function to print the CWayPoint data as per format
 * @param : format - Degree or minutes and seconds (IN)
 * @returnvalue	None
 * */
void CWaypoint::print(int format)
{
		if (format == DEGREE) // degree format
		{
			cout <<endl<< this->m_name << " on latitude = " << this->m_latitude
					<< " on longitude = " << this->m_longitude << endl;
		}
		else if (format == MMSS) // deg min sec format
		{
			cout<<*this;
			/*transformLatitude2degmmss(deg, mm, ss);
			cout <<endl<< this->m_name << " on latitude = " << deg << "deg " << mm
					<< "min " << ss << "s ";
			transformLongitude2degmmss(deg, mm, ss);
			cout << "and longitude = " << deg << "deg " << mm << "min " << ss
					<< "s"<<endl;*/
		}
		else
		{
			//Invalid format i.e 1 or 2
			cout <<"\nERROR in "<<__FUNCTION__<<" : Invalid format to print: valid format are : ( DEGREE/MMSS )";
		}
}


/**
 * setter function to set the value of each element
 *  of CWaypoint object
 *  @param : name - Name of Waypoint (IN)
 *  @param : latitude - latitude of Waypoint (IN)
 *  @param : longitude - longitude of Waypoint (IN)
 * @returnvalue	Double latitude (OUT)
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


void CWaypoint::getAllDataByReference(string& name, double & latitude,double & longitude)
{

#ifdef SHOWADDRESS
	cout << "Address of data from class parameters " << &name <<" "<< &latitude << " " << &longitude << "\n";
#endif

	name = this->m_name;
	latitude = this->m_latitude;
	longitude = this->m_longitude;
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

CWaypoint::~CWaypoint()
{
}
