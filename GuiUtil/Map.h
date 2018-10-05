#ifndef _MAP_H
#define _MAP_H

#include <list>
#include <map>
using namespace std ;

//비교 함수 예제
/*struct Compare : public binary_function<AA, AA, bool>
{
	bool operator()(const AA &lhs, const AA &rhs)const
	{
		//앞에 오면 true
		//뒤면 false
		//같은 값이면 false..
	}
};*/

template <typename KEY, typename DATA, typename Pred = less<KEY> > class CMap
{
public:
	//(*itor).second 가 DATA
	//(*itor).first 가 KEY
	typedef map<KEY, DATA, Pred> ItemMap ;
	void Free()
	{
		ItemMap::iterator itor ;
		if(!m_Map.empty())
		{
			for(itor = m_Map.begin() ; itor != m_Map.end() ; )
			{
				m_Map.erase(itor++) ;
			}
		}
	}
	void FreePtr()
	{
		ItemMap::iterator itor ;
		if(!m_Map.empty())
		{
			for(itor = m_Map.begin() ; itor != m_Map.end() ; )
			{
				DATA t = (*itor).second ;
				m_Map.erase(itor++) ;
				delete t ;
			}
		}	
	}
	bool Remove(KEY key)
	{
		ItemMap::iterator itor ;
		if(!m_Map.empty())
		{
			itor = m_Map.find(key) ;
			if(itor != m_Map.end())
			{
				m_Map.erase(itor) ;
				return true;
			}
		}
		return false;
	}
	bool RemovePtr(KEY key)
	{
		ItemMap::iterator itor ;
		if(!m_Map.empty())
		{
			itor = m_Map.find(key) ;
			if(itor != m_Map.end())
			{
				DATA t = (*itor).second ;
				m_Map.erase(itor) ;
				delete t ;
				return true;
			}
		}
		return false;
	}	
	bool Pop(KEY key, DATA *ret)
	{
		ItemMap::iterator itor ;
		if(!m_Map.empty())
		{
			itor = m_Map.find(key) ;
			if(itor != m_Map.end())
			{
				*ret = (*itor).second ;
				m_Map.erase(itor) ;
				return true ;
			}
		}
		return false ;
	}
	bool Get(KEY key, DATA *ret)
	{
		ItemMap::iterator itor ;
		if(!m_Map.empty())
		{
			itor = m_Map.find(key) ;
			if(itor != m_Map.end())
			{
				*ret = (*itor).second ;
				return true ;
			}
		}
		return false ;
	}
	bool Exist(KEY key)
	{
		ItemMap::iterator itor ;
		if(!m_Map.empty())
		{
			itor = m_Map.find(key) ;
			if(itor != m_Map.end())
			{
				return true ;
			}
		}
		return false ;
	}
	bool Empty()
	{
		return m_Map.empty() ;
	}
	bool Add(KEY key, DATA item)
	{
		ItemMap::iterator itor ;
		if(!m_Map.empty())
		{
			itor = m_Map.find(key) ;
			if(itor != m_Map.end())
			{
				return false ;
			}
		}
		m_Map.insert(ItemMap::value_type(key, item)) ;
		return true ;
	}
	int Size()
	{
		return m_Map.size();
	}

	CMap(){}
	virtual ~CMap(){Free() ;}
	ItemMap m_Map ;
};
#endif