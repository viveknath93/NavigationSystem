/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOI.CPP
 * Author          : Viveknath Thulasi
 * Description     : include file containing the information about Point of Interest (POI)
 *
 *
 ****************************************************************************/

#ifndef CPOI_H
#define CPOI_H

#include "CWaypoint.h"
#include <string>
class CPOI : public CWaypoint
{
public:
	enum poi_type
	{
			RESTAURANT, TOURISTIC, GASSTATION, UNIVERSITY, DEFAULT
	};
	typedef enum poi_type t_poi;
/*
 * function to print out data of point of interests
 * @param format format of printing degree or min sec
 * @returnvalue	void
 * */
    void print(int format);
/*
 * parameterised Constructor of CPOI to initialise the POI data
 * @param t_poi type	(IN)
 * @param string name	(IN)
 * @param string description (IN)
 * @param double latitude	(IN)
 * @param double longitude	(IN)
 * */
    CPOI(t_poi type, std::string name, std::string description, double latitude, double longitude);

    /*
     * Overloaded insertion operator to print out the POI data
     * @param ostream &out ostream variable and return value
     * @param reference of Poi
     * @return ostream return reference object
     * */
    friend std::ostream & operator << (std::ostream& out, CPOI& c);

/**
 * function to get the POI type
 * @return string corresponding to the POItype
 * */
    string getPoiType() const;

/**
 * function to get the POI description
 * @return string of description of that instance of POI
 * */
    string getPoiDescription() const;


private:
	std::string m_description;
	t_poi m_type;

};
/********************
**  CLASS END
*********************/
#endif /* CPOI_H */
