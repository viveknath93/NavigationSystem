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
using namespace std;

//Own Include Files
#include "CPOI.h"
//Method Implementations
const string poi_type_text[] = {"RESTAURANT","TOURISTIC","GASSTATION","UNIVERSITY","DEFAULT"};

/*
 * function to print out data of point of interests
 * @param format format of printing degree or min sec
 * @returnvalue	void
 * */
void CPOI::print(int format)
{
	if(format == 1)
	{
		cout << "Point of Interest of Type :";

		cout << getPoiType()<< " : " << this->m_description << "\n" << m_name << " on latitude : "<< m_latitude << " on longitude : " << m_longitude;
	}
	else
	{
		cout<<*this;
	}
}


/*
 * parameterised Constructor of CPOI to initialise the POI data
 * @param t_poi type	(IN)
 * @param string name	(IN)
 * @param string description (IN)
 * @param double latitude	(IN)
 * @param double longitude	(IN)
 * */
CPOI::CPOI(t_poi type, string name, string description, double latitude, double longitude)
{
	this->m_description = description;
	this->m_name = name;
	this->m_latitude = latitude;
	this->m_longitude = longitude;
	this->m_type = type;
}


/*
 * Overloaded insertion operator to print out the POI data
 * @param ostream &out ostream variable and return value
 * @param reference of Poi
 * @return ostream return reference object
 * */
ostream & operator << (ostream &out, CPOI & poi_ref)
{
	int deg, mm;
	double ss;

	out <<poi_ref.getName()<< " : " <<poi_type_text[poi_ref.m_type]<<" : "<< poi_ref.m_description ;

	poi_ref.transformLatitude2degmmss(deg,mm,ss);

	out <<" on latitude = "<<deg<<" deg "<<mm<< " min " << ss << "s ";

	poi_ref.transformLongitude2degmmss(deg, mm, ss);
	out << "and longitude = " << deg << " deg " << mm << " min " << ss<< "s"<<endl;
	return out;
}

/**
 * function to get the POI type
 * @return string corresponding to the POItype
 * */
string CPOI::getPoiType() const
{
	return poi_type_text[m_type];
}

/**
 * function to get the POI description
 * @return string of description of that instance of POI
 * */
string CPOI::getPoiDescription() const
{
	return m_description;
}
