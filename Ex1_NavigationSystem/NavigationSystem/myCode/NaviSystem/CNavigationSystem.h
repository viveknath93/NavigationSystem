/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CNAVIGATIONSYSTEM.H
 * Author          : Viveknath Thulasi
 * Description     : Include file for CNavigationSystem
 *
 *
 ****************************************************************************/

#ifndef CNAVIGATIONSYSTEM_H
#define CNAVIGATIONSYSTEM_H
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"
class CNavigationSystem
{
private:
	void printDistanceCurPos();
	void printRoute();
	void enterRoute();
	void TC_addPOIDatabase();
	void TC_createRoute();
	CGPSSensor m_GPSSensor;
	CRoute m_route;
	CPoiDatabase m_pPoiDatabase;
public:

	CNavigationSystem();
	void run();

};
/********************
 **  CLASS END
 *********************/

#endif /* CNAVIGATIONSYSTEM_H */
