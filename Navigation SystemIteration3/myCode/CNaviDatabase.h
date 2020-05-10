/*
 * CNaviDatabase.h
 *
 *  Created on: 26 Dec 2018
 *      Author: Viveknath Thulasi
 */

#ifndef CNAVIDATABASE_H_
#define CNAVIDATABASE_H_
#include "CWaypoint.h"
#include "CPOI.h"
#include <map>

template <class KeyName, class DbType>
class CNaviDatabase
{

public:
	CNaviDatabase();

	virtual ~CNaviDatabase();

	DbType* getPointerToLocation(KeyName key);
	void addLocation(KeyName key,DbType const& Loc);
	void clear_LocationDB();
	void print_database();
	std::map<KeyName, DbType> getdatabase() const;
	void setdatabase(typename std::map<KeyName,DbType> &mymap);
private:
	std::map<KeyName, DbType> m_Location;
};

template<class KeyName, class DbType>
CNaviDatabase<KeyName,DbType>::CNaviDatabase()
{
	// TODO Auto-generated constructor stub
	//this->m_Location = NULL;
}


template<class KeyName, class DbType>
CNaviDatabase<KeyName,DbType>::~CNaviDatabase()
{
	// TODO Auto-generated destructor stub
}

/*
 * Template to get pointer to particular object from database
 * @param	name  input search string value 	(IN)
 * @returnvalue Pointer to object or null
 * */
template<class KeyName, class DbType>
inline DbType* CNaviDatabase<KeyName, DbType>::getPointerToLocation(KeyName key)
{
	typename std::map<KeyName,DbType>::iterator it ;
	it = m_Location.find(key);

	if(it != m_Location.end())
	{
		return &it->second;
	}
	else
	{
		return NULL;
	}
}

/*
 * Template to add the location to the generic database
 * @param	const reference to DB	(IN)
 * @returnvalue void */
template<class KeyName, class DbType>
inline void CNaviDatabase<KeyName, DbType>::addLocation(KeyName key,const DbType& Loc)
{

	if(this->m_Location.find(key) == this->m_Location.end())
	{
		typename std::map<KeyName, DbType>::iterator it = this->m_Location.end();
		this->m_Location.insert(it,std::pair<KeyName,DbType>(key,Loc));
	}
	else
	{
		cout<<__FUNCTION__<<": Error : Location already existing, skipping to add\n";
	}
}

/*
 * Template to clear the  database
 * @param	void
 * @returnvalue void */
template<class KeyName, class DbType>
inline void CNaviDatabase<KeyName, DbType>::clear_LocationDB()
{
	this->m_Location.clear();
}

/*
 * Template to print the contents of  database
 * @returnvalue void  */
template<class KeyName, class DbType>
inline void CNaviDatabase<KeyName, DbType>::print_database()
{
	cout<<endl;
	typename std::map<KeyName,DbType>::iterator it ;
	for(it = m_Location.begin();it != m_Location.end(); ++it)
	{
		cout<<"Key : "<<it->first<<"\tValue : "<<it->second;
	}
}

/*
 * getter Template for the  database
 * @returnvalue map of  name and object  */
template<class KeyName, class DbType>
inline std::map<KeyName, DbType> CNaviDatabase<KeyName, DbType>::getdatabase() const
{
	return m_Location;
}

/*
 * Setter Template to set the value of map
 * @param  map from other sourves
 * @returnvalue none
 * */
template<class KeyName, class DbType>
inline void CNaviDatabase<KeyName, DbType>::setdatabase(typename std::map<KeyName,DbType> &mymap)
{
	this->m_Location.insert(mymap.begin(),mymap.end());
}

typedef CNaviDatabase<int,CWaypoint>  CintegerWpDatabase;

typedef CNaviDatabase<int,CPOI>  CintegerPoiDatabase;

#endif /* CNAVIDATABASE_H_ */
