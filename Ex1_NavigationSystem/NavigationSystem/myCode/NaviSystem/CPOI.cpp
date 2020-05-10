/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOI.CPP
 * Author          : Viveknath Thulasi
 * Description     : Class containing the information about Point of Interest (POI)
 *
 *
 ****************************************************************************/
//System Include Files
#include <iostream>

//Own Include Files
#include"CPOI.h"

using namespace std;
//Method Implementations

/*
 * function to print out data of point of interests
 * @returnvalue	void
 * */
void CPOI::print()
{
	t_poi current_type;
	current_type = this->m_type;
	cout << "Point of Interest\n of Type :";
	print_type(current_type);
	cout << " : " << this->m_description << "\n" << m_name << " on latitude : "<< m_latitude << " on longitude : " << m_longitude; // Calling invoked base class functions in derived class

}

/*
 * parameterised Constructor of CPOI to initialise the POI data
 * @param t_poi type	(IN)
 * @param string name	(IN)
 * @param string description (IN)
 * @param double latitude	(IN)
 * @param double longitude	(IN)
 * */
CPOI::CPOI(t_poi type, string name, string description, double latitude,double longitude)
{
	this->m_description = description;
	this->m_name = name;
	this->m_latitude = latitude;
	this->m_longitude = longitude;
	this->m_type = type;
}


/*
 * Getter function to get the data by reference
 * @param t_poi& type	(OUT)
 * @param string& name	(OUT)
 * @param string& description (OUT)
 * @param double& latitude	(OUT)
 * @param double& longitude	(OUT)
 * */
void CPOI::getAllDataByReference(string& name, double & latitude,
		double & longitude, t_poi & type, string & description)

{
	name = this->m_name;
	latitude = this->m_latitude;
	longitude = this->m_longitude;
	type = this->m_type;
	description = this->m_description;
}

/*
 * Local Setter function for printing
 * @returnvalue	void
 * */
void print_type(t_poi & mtype_value)
{
	//TODO: operator overloading instead ??
	switch (mtype_value)
	{
	case RESTAURANT:
		cout << " RESTAURANT ";
		break;
	case TOURISTIC:
		cout << " TOURISTIC ";
		break;
	case GASSTATION:
		cout << " GASSTATION ";
		break;
	case UNIVERSITY:
		cout << " UNIVERSITY ";
		break;
	default:
		break;

	}
}
