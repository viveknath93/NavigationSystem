/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : main.cpp
 * Author          : Viveknath Thulasi
 * Description     : starting point for execution of Navigation system
 *
 ****************************************************************************/
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>
#include "CNavigationSystem.h"

using namespace std;
int main (void)
{

	cout << "Navigation_System (Improved Design) gestarted." << endl << endl;
	CNavigationSystem m_myNavigationSystem;

	m_myNavigationSystem.run();
	return 0;
}
