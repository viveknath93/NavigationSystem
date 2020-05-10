/*
 * CJsonPersistence.cpp
 *
 *  Created on: 22 Dec 2018
 *      Author: Viveknath Thulasi
 */

#include "CJsonPersistence.h"
#include <fstream>
#include "CJsonScanner.h"
#include "CWpDatabase.h"
#include "CPoiDatabase.h"
#include "CCSV.h"

#define NO_WP_ATTR 3
#define NO_POI_ATTR 5

#define UNDER_LIMIT 1;
#define LIMIT_MATCH 2;
#define EXCEEDED_LIMIT 0;

eparser_states parser_state;

using namespace APT;
CJsonPersistence::CJsonPersistence()
{
	// TODO Auto-generated constructor stub

}

/*
 * function to set the Media name
 * @param : name of the file including .json
 * @returnvalue none
 * */

void CJsonPersistence::setMediaName(std::string name)
{
	this->media_name = name;
}

/*
 * function to write database data into .json file
 * @param waypointDb reference to waypoint database
 * @param poiDb reference to poi database
 * @returnvalue fail or pass of the write function
 *  */
bool CJsonPersistence::writeData(const CWpDatabase& waypointDb,const CPoiDatabase& poiDb)
{
	cout<<"Writing data . . .  \n";

	ofstream myDBOutfileHandler;
	myDBOutfileHandler.open(media_name.c_str(),ios::out);

	myDBOutfileHandler<<"{\n";
	myDBOutfileHandler<<"\t\"waypoints\" : [\n";

	CWpDatabase::myWpMap_t myTemp_waypointdb ;
	CWpDatabase::myWpMap_t::iterator it;

	myTemp_waypointdb = waypointDb.getWpdatabase();
	unsigned int count = 0;
	for (it = myTemp_waypointdb.begin();it!= myTemp_waypointdb.end();++it )
	{
		count++;
		myDBOutfileHandler<<"\t\t{\n";
		myDBOutfileHandler<<"\t\t\t\"name\": \""<<it->second.getName()<<"\",\n";
		myDBOutfileHandler<<"\t\t\t\"latitude\": \""<<it->second.getLatitude()<<"\",\n";
		myDBOutfileHandler<<"\t\t\t\"longitude\": \""<<it->second.getLongitude()<<"\"\n";
		if(count != myTemp_waypointdb.size())
		{
			myDBOutfileHandler<<"\t\t},\n";
		}
		else
		{
			myDBOutfileHandler<<"\t\t}\n";
		}
	}
	myDBOutfileHandler<<"\t],\n";

	myDBOutfileHandler<<"\t\"pois\" : [\n";
	CPoiDatabase::myPoiMap_t temp_poi_db;
	CPoiDatabase::myPoiMap_t :: iterator it_poi;
	temp_poi_db = poiDb.getPoiDatabase();
	count =0;
	for(it_poi = temp_poi_db.begin();it_poi!= temp_poi_db.end();++it_poi)
	{
		myDBOutfileHandler<<"\t\t{\n";
		myDBOutfileHandler<<"\t\t\t\"name\": \""<<it_poi->second.getName()<<"\",\n";
		myDBOutfileHandler<<"\t\t\t\"latitude\": \""<<it_poi->second.getLatitude()<<"\",\n";
		myDBOutfileHandler<<"\t\t\t\"longitude\": \""<<it_poi->second.getLongitude()<<"\",\n";
		myDBOutfileHandler<<"\t\t\t\"type\": \""<<it_poi->second.getPoiType()<<"\",\n";
		myDBOutfileHandler<<"\t\t\t\"description\": \""<<it_poi->second.getPoiDescription()<<"\"\n";
		if(count != myTemp_waypointdb.size())
		{
			myDBOutfileHandler<<"\t\t},\n";
		}
		else
		{
			myDBOutfileHandler<<"\t\t}\n";
		}
	}
	myDBOutfileHandler<<"\t]\n}";
	myDBOutfileHandler.close();
	cout<<"Writing data . . . Completed in file "<< media_name<<endl;
	return true;
}

/*
 * function to read the database file and add data to database variables
 * @param master waypoint database reference
 * @param master poi database reference
 * @param Merging Mode replace or append
 * @return status of reading the json file
 * */
bool CJsonPersistence::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,MergeMode mode)
{
	//Parsing Jason DB file starts here . . .
	string filename;
	bool api_return;
	ifstream myDBfhandler;

	//other support variables
	string db_name,WporPoiname,attr_name,description,poitype;

	CPoiDatabase::myPoiMap_t temp_poi_map_db;
	CPoiDatabase::myPoiMap_t :: iterator it_poi;

	CWpDatabase::myWpMap_t temp_waypoint_map_db;
	CWpDatabase::myWpMap_t::iterator it;


	temp_waypoint_map_db = waypointDb.getWpdatabase();
	temp_poi_map_db = poiDb.getPoiDatabase();
	if(mode == REPLACE)
	{
		temp_waypoint_map_db.clear();
		temp_poi_map_db.clear();
	}

	CPOI::t_poi poi_type;
	double lat_val,long_val;
	CJsonScanner myscanner(myDBfhandler);

	CJsonToken *pjsonToken ;
	//Counts and flags
	int att_count = 0, entered_object = 0,first_token = 0,entered_array = 0,last_token = 0;

	myDBfhandler.open(media_name.c_str(),ifstream::in);
	if(myDBfhandler.is_open())
	{
		try
		{
		while(myDBfhandler.peek() != EOF)
		{
			pjsonToken = myscanner.nextToken();
			switch(parser_state)
			{
			case wait_for_object_begin://Also Waiting for first token
				{
					if(pjsonToken->getType() != CJsonToken::BEGIN_OBJECT)
					{
						throw EXPECTED_BEGIN_OBJECT;
					}
					else
					{
						if(first_token == 0)
						{
							first_token = 1;
							parser_state=wait_for_db_name;

						}
						else
						{
							parser_state=wait_for_attr_name;
							entered_object = 1;
						}
					}
				}
			break;

			case wait_for_db_name://Waiting for db name
				{

					if(pjsonToken->getType() == CJsonToken::STRING)
					{
						db_name = dynamic_cast<CJsonStringToken*>(pjsonToken)->getValue();
						parser_state=wait_for_name_seperator;
						cout<<db_name<<endl;
					}
					else
					{
						throw EXPECTED_STRING;
					}
				}
				break;

			case wait_for_name_seperator://": name seperator"
				{
					if(pjsonToken->getType() == CJsonToken::NAME_SEPARATOR)
					{
						if(entered_object == 0)
						{
							//Not yet into any of object
							parser_state = wait_for_array_begin;
						}
						else
						{
							//Into object- between name and value
							parser_state = wait_for_attr_value;
						}
					}
					else
					{throw EXPECTED_NAME_SEPERATOR;}

				}
			break;
			case wait_for_array_begin:// wait for array begin
				{
					if(pjsonToken->getType() == CJsonToken::BEGIN_ARRAY)
					{
						parser_state = wait_for_object_begin;
						entered_array = 1;
					}
					else
					{
						throw EXPECTED_ARRAY_BEGIN;
					}

				}
				//goto wait for begin object
				break;
			case wait_for_attr_name://waiting for attribute name
				if(pjsonToken->getType() == CJsonToken::STRING)
				{
					att_count++;
					if(underlimits(db_name,att_count) == 0)//if count is becoming more that 3 or 5
					{
						throw TOO_MANY_FIELDS;
					}
					else
					{
						//check for valid attributes
						attr_name = dynamic_cast<CJsonStringToken*>(pjsonToken)->getValue();
						checkValidAttributeName(attr_name,db_name);
						//check if it is either valid attribute
						parser_state = wait_for_name_seperator;
					}
				}
				else
				{throw EXPECTED_STRING;}
				break;
			case wait_for_attr_value: //wait for value
				if(pjsonToken->getType() == CJsonToken::STRING)
				{
					if(attr_name == "name")
					{WporPoiname = dynamic_cast<CJsonStringToken*>(pjsonToken)->getValue();}
					else if(attr_name == "description")
					{description = dynamic_cast<CJsonStringToken*>(pjsonToken)->getValue();}
					else if(attr_name == "type")
					{poitype = dynamic_cast<CJsonStringToken*>(pjsonToken)->getValue();}
				}
				else if(pjsonToken->getType() == CJsonToken::NUMBER)
				{
					if(attr_name == "latitude")
					{lat_val = dynamic_cast<CJsonNumberToken*>(pjsonToken)->getValue();}
					else if(attr_name == "longitude")
					{long_val = dynamic_cast<CJsonNumberToken*>(pjsonToken)->getValue();}
				}
				else if(pjsonToken->getType() == CJsonToken::JSON_NULL)
				{
					//set warning that this attribute name seems to be empty or error
					throw FIELD_EMPTY;
				}
				else
				{
					throw EXPECTED_VALUE;
				}
				parser_state = wait_for_value_seperator;
				break;
			case wait_for_value_seperator:
				// wait for value separator or
				// here next maybe string or }
				if( pjsonToken->getType() == CJsonToken::VALUE_SEPARATOR )
				{
					if(entered_object == 1)
					{
						parser_state = wait_for_attr_name;
					}
					else if(entered_object == 0 && entered_array ==1 )
					{
						parser_state  = wait_for_object_begin;
					}
					else if(entered_array == 0)
					{
						parser_state  = wait_for_db_name;
					}
				}
				else if(pjsonToken->getType() == CJsonToken::END_OBJECT && entered_object == 0 && entered_array ==0)
				{
					//Igonore
					// This indicates end of file
					// The next JSON call will lead to EOF
					last_token = 1;
				}
				else if(pjsonToken->getType() == CJsonToken::END_OBJECT)
				{
					if(underlimits(db_name,att_count) == 1)//if count is becoming more that 3 or 5
					{
						throw TOO_FEW_FIELDS;
					}
					entered_object = 0;
					att_count = 0;
					parser_state = wait_for_value_seperator;
					if(db_name == "waypoints")
					{
						CWaypoint obj(WporPoiname,lat_val,long_val);

						it = temp_waypoint_map_db.end();
						temp_waypoint_map_db.insert(it,std::make_pair(WporPoiname,obj));
						cout<< "Read OK : "<<WporPoiname<<" "<<lat_val<<" "<<long_val<<endl;
					}
					else
					{
						CCSV::setPoiType(poitype,poi_type);
						CPOI poi_obj(poi_type,WporPoiname,description,lat_val,long_val);
						it_poi = temp_poi_map_db.end();
						temp_poi_map_db.insert(it_poi,std::make_pair(WporPoiname,poi_obj));

						cout<<"Read OK : "<<WporPoiname<<" "<<lat_val<<" "<<long_val<<" "<<description<<" "<<poitype<<endl;
					}
				}
				else if(pjsonToken->getType() == CJsonToken::END_ARRAY)
				{
					entered_array = 0;
					parser_state = wait_for_value_seperator;
				}
				else{throw UNEXPECTED_TOKEN;}
				break;
			default:
			throw "UNKNOWN_TOKEN";
				break;

			}
		}
		if(first_token == 0 )
		{
			throw FIRST_TOKEN_NOT_PARSED;
		}
		if(last_token == 0 )
		{
			throw END_TOKEN_NOT_PARSED;
		}
		if(myDBfhandler.peek() == EOF)
		{
			// If it is entering here everything is fine...

			waypointDb.setdatabase(temp_waypoint_map_db);
			poiDb.setpoidatabase(temp_poi_map_db);

			cout<<"Reading data completed . . "<<endl;

		}
		else
		{
			cout<<"skipping reading file "<<endl;
		}

		}// End of Try block
		catch(enum error_codes &e)
		{
			cout<<endl<<getErrorText(e)<<" in line number "<<myscanner.scannedLine()<<endl;
		}
		catch(char const* invalidchar)
		{
			cout<<"Invalid Character in JSON file : '" << invalidchar << "' in line no "<<myscanner.scannedLine()<<endl;
		}

	}
	else
	{
		cout<<__FUNCTION__ << " : "<<filename<<" FILE_OPEN_ERROR ";
		api_return = false;
	}
	myDBfhandler.close();
	return api_return;
}


/*
 * Inbuilt private funtion to check the count of attributes corresponding to a particular database type
 * @param dbtype database type
 * @param referecne to count no of attributes in particular databse type
 * @returnvalue : EXCEEDED_LIMIT 0 if count exceeds limit
 * 				  UNDER_LIMIT 1 if count is under limit
 * 				  LIMIT_MATCH 2 if limit matches
 **/
int CJsonPersistence::underlimits(string& dbtype, int& count)
{
	if(dbtype == "waypoints")
		{
			if(count < NO_WP_ATTR)
				{ return UNDER_LIMIT;}
			else if(count == NO_WP_ATTR)
				{return LIMIT_MATCH;}
			else
			{return EXCEEDED_LIMIT;}
		}
		else if(dbtype == "pois")
		{
			if(count < NO_POI_ATTR)
			{ return UNDER_LIMIT ;}
			else if(count == NO_POI_ATTR)
			{return LIMIT_MATCH;}
			else
			{ return EXCEEDED_LIMIT;}
		}
		else
		{
			//Throw exeception of invalid db type
			throw INVALID_DB_TYPE;
			return 0;
		}

}


/*
 * function to return the error code corresponding to enum value
 * @param error_code error code types of enum
 * @returnvalue error text corresponding to the error code
 * */
string CJsonPersistence::getErrorText(enum error_codes temp_err_code)
{
	string error_txt;
	error_txt = error_code_JSON_description[temp_err_code];
	return error_txt;
}

/*
 * function to check the validity of attribute name
 * @param attr_name attribute name extracted from file
 * @param db_type database type
 * @returnvalue none
 * */
void CJsonPersistence::checkValidAttributeName(string attr_name, string db_type)
{
	if(db_type == "waypoints" )
	{
		if(!(attr_name == "name"|| attr_name == "latitude" || attr_name == "longitude"))
		{
			throw INVALID_ATTR_NAME;
		}
	}
	else if(db_type == "pois")
	{
		if(!(attr_name == "name"|| attr_name == "latitude" || attr_name == "longitude"|| attr_name == "type" || attr_name == "description"))
		{
			throw INVALID_ATTR_NAME;
		}
	}
	else
	{
		//Throw exeception of invalid db type
		throw INVALID_DB_TYPE;
	}
	return;
}
