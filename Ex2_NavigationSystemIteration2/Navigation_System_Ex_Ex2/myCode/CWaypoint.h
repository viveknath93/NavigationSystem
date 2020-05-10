/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWAYPOINT.H
* Author          : T VIVEKNATH
* Description     : include file for Waypoint class
*
*
****************************************************************************/

#ifndef CWAYPOINT_H
#define CWAYPOINT_H

#include <iostream>
#include <string>

using namespace std;

//Pre-processor for unit of measurement of Latitude and longitude
#define DEGREE 1
#define MMSS 2
#define LATTITUDE_LONGITUDE_IN_LIMIT 1
#define LATTITUDE_LONGITUDE_NOT_IN_LIMIT 0

extern int variable_limit_flag ;
class CWaypoint {
protected:
    std::string m_name;
    double m_latitude;
    double m_longitude;

public:
    // Added the default values for constructor
    CWaypoint(std::string name = "DUMMY_LOCATION" , double latitude= 0.0 , double longitude= 0.0 );

/**
	* insertion '<<' operator overloading to efficient printing for Waypoint objects.
	*
	* @param out the reference in which the output string is returned
	* @param wp_const the reference variable which data needs to be printed
	* @return output of insertion data
	*/
    friend std::ostream & operator << (std::ostream& out, CWaypoint& c);
/**
 * getter function to get the value of
 * name of CWaypoint object
 * @returnvalue	string name (OUT)
 * */
    std::string getName() const;
/**
 * getter function to get the value of
 * Latitude of CWaypoint object
 * @returnvalue	Double latitude (OUT)
 * */
    double getLatitude();
/**
 * getter function to get the value of
 * longitude of CWaypoint object
 * @returnvalue	Double longitude (OUT)
 * */
    double getLongitude();
/**
 *  function to print the CWayPoint data as per format
 * @param : format - Degree or minutes and seconds (IN)
 * @returnvalue	None
 * */
    void print(int format);
/**
 * setter function to set the value of each element
 *  of CWaypoint object
 *  @param : name - Name of Waypoint (IN)
 *  @param : latitude - latitude of Waypoint (IN)
 *  @param : longitude - longitude of Waypoint (IN)
 * @returnvalue	Double latitude (OUT)
 * */
    void set(std::string name,double latitude,double longitude);

    void getAllDataByReference(std::string& name, double & latitude,double & longitude);
/**
 * Function to transform latitude value to degrees, minutes and seconds using reference
 * @param	int & deg 	degree value of latitude (OUT)
 * @param	int & mm	minutes value of latitude (OUT)
 * @param	double & ss longitude of latitude (OUT)
 * @returnvalue void
 * */
	void transformLatitude2degmmss(int & deg, int & mm, double & ss);
/**
 * Function to transform longitude value to degrees, minutes and seconds using reference
 * @param	int & deg 	degree value of longitude (OUT)
 * @param	int & mm	minutes value of longitude (OUT)
 * @param	double & ss longitude of longitude (OUT)
 * @returnvalue void
 * */
	void transformLongitude2degmmss(int & deg, int & mm, double & ss);

	virtual ~CWaypoint();
};
/********************
**  CLASS END
*********************/
#endif /* CWAYPOINT_H */
