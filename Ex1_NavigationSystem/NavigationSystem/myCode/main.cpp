// GIT-Labor
// main.h

////////////////////////////////////////////////////////////////////////////////
// Header-Dateien
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>

using namespace std;

#include "CWaypoint.h"
#include "CNavigationSystem.h"

void TC_CWaypoint();					//Function to collect the test cases 1.1

int main(void)
{
	/*
	 * Test cases AND answers to questions for 1.1 are added here to this function*/
	TC_CWaypoint();

	cout<<"\n\n ********************** TCs until CWaypoint Ends ********************** \n\n";
	CNavigationSystem obj_Navigation_system;
	obj_Navigation_system.run();

	return 0;
}

void TC_CWaypoint()
{
	/*1.1b
	 2 types of calling objects
	 1. Default
	 2. invalid parameters*/

	CWaypoint Test_obj;
	Test_obj.print(1);

	CWaypoint Test_Obj_1("Random_Name_and_incorrect_latitude_mentioned", 91,181);
	Test_Obj_1.print(1);

	CWaypoint Test_Obj_2("Random_Name_latitude_mentioned", -484, -565);
	Test_Obj_2.print(1);

	/*1.1c and 1.1d
	 *  Set verbose mode and check Log level -> Toggle SHOWADRESS
	 *  print address of object and member attributes
	 *  print value of attributes
	 * 1. address of object -> always took the address of longitude
	 * 						-> implies starting of allocation with first attribute in class
	 * 2. value of each attribute and value of each address
	 * 3. Data occupied by each attribute
	 * 		name		: String 32bytes
	 * 		latitude	: Double 8bytes
	 * 		longitude	: Double 8bytes
	 */

	/* 1.1e and 1.1f
	 * Declaration
	 * it is better to declare #define in CWaypoint.h as this can be accessed by
	 * both main function as well as the Class definition file
	 */
	CWaypoint amsterdam("amsterdam", 52.379189, 4.899431), darmstadt(
			"darmstadt", -49.878708, 8.646927), Berlin("Berlin", 52.520008,
			13.404954), newWaypoint;				//object without parameter

	Berlin.print(MMSS);
	Berlin.print(DEGREE);

	/*
	 * 1.1g Test the getter functions*/
	cout << darmstadt.getName() << " " << darmstadt.getLatitude() << " "
			<< darmstadt.getLongitude() << endl;
	cout << amsterdam.getName() << " " << amsterdam.getLatitude() << " "
			<< amsterdam.getLongitude() << endl;
	cout << Berlin.getName() << " " << Berlin.getLatitude() << " "
			<< Berlin.getLongitude() << endl;

	/*
	 * 1.1h Compare the address of reference and local variables
	 * parameter addresses and local variables correspond to same addresses
	 * implies reference is basically a second variable name pointing to same location
	 * avoids generating memory location for calling function parameters*/

	string name;
	double latitude;
	double longitude;
	CWaypoint Tokyo("Tokyo", 35.652832, 139.839478);
	Tokyo.getAllDataByReference(name, latitude, longitude);

	cout << "Tokyo values in main: " << name << " " << latitude << " "
			<< longitude << endl;
	cout << "Tokyo addresses of data in main(): " << &name << " " << &latitude
			<< " " << &longitude << endl;

	/*
	 * 1.1i : implement calculate Distance between places
	 * */
	amsterdam.calculateDistance(Berlin);
	Berlin.calculateDistance(Tokyo);

}

