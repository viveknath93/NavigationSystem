/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CWAYPOINT.H
 * Author          : Viveknath Thulasi
 * Description     : Include file for CWAYpoint class
 *
 *
 ****************************************************************************/

#ifndef CWAYPOINT_H
#define CWAYPOINT_H

#include<string>
#include<math.h>


//Pre-processor for unit of measurement of Latitude and longitude
#define DEGREE 1
#define MMSS 2
#define LATTITUDE_LONGITUDE_IN_LIMIT 1
#define LATTITUDE_LONGITUDE_NOT_IN_LIMIT 0

extern int variable_limit_flag ;
class CWaypoint
{
protected:
	double m_longitude;
	std::string m_name;
	double m_latitude;

public:

	double calculateDistance(const CWaypoint& wp);
	void print(int format);
	void getAllDataByReference(std::string& name, double & latitude,double & longitude);
	double getLongitude();
	double getLatitude();
	std::string getName();
	void set(std::string name,double latitude,double longitude);
	CWaypoint(std::string name = "DUMMY_LOCATION" , double latitude= 0.0 , double longitude= 0.0 );// Added the default values for constructor


private:
	void transformLatitude2degmmss(int & deg, int & mm, double & ss);
	void transformLongitude2degmmss(int & deg, int & mm, double & ss);
};
/********************
 **  CLASS END
 *********************/
#endif /* CWAYPOINT_H */
