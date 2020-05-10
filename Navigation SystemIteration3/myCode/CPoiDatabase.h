/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOIDATABASE.CPP
 * Author          : Viveknath Thulasi
 * Description     : including file contains the class and function declaration of operations in Database of POIs
 *
 *
 ****************************************************************************/

#ifndef CPOIDATABASE_H
#define CPOIDATABASE_H


#include "CPOI.h"
#include "CNaviDatabase.h"
#include<map>

#include<string>

class CPoiDatabase : public CNaviDatabase<string,CPOI>
{

public:

	typedef std::map<std::string,CPOI> myPoiMap_t;
    CPoiDatabase();
/*
 * function to add the POIs to the generic database
 * @param	t_poi type type of POI	(IN)
 * @param	string name name of POI	(IN)
 * @param	string description of POI	(IN)
 * @param	double latitude		(IN)
 * @param	double longitude	(IN)
 * @returnvalue void */
    void addPoi(CPOI const& poi);

/*
 * Function to clear the Poi database
 * @param None
 * @returnvalue	void
 * */

    void clear_PoiDatabase();
/*
 * Function gets the pointer to the POI of the input POI name
 * @param None
 * @returnvalue	void
 * */
    CPOI* getPointerToPoi(std::string name);

/*
 * Function to print all the Poi's in database
 * @param None
 * @returnvalue	void
 * */
    void print();
/*
 * Function to get POI database
 * @param None
 * @returnvalue	the map variable containing the database
 * */
    myPoiMap_t getPoiDatabase() const;

    /*
     * Setter function to set the value of poi map
     * @param poi map from other sourves
     * @returnvalue none
     * */
    void setpoidatabase(myPoiMap_t mypoimap);
private:
    //myPoiMap_t m_CPOI;

};
/********************
**  CLASS END
*********************/
#endif /* CPOIDATABASE_H */
