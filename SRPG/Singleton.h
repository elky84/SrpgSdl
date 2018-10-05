#ifndef _SINGLETONE_H
#define _SINGLETONE_H

template<typename T> 
class CSingleton
{ 
private: 
	static T* m_pSingleton; 

public: 
	CSingleton() 
	{ 
		__int64 offset = (__int64)(T*)1 - (__int64)(CSingleton<T>*)(T*)1;  //T�� ��ӹ��� Ŭ������ �ǹ��ϰ�, CSingleton<T>�� �̱��� Ŭ������ �ǹ��Ѵ�.
		m_pSingleton = (T*)((__int64)this + offset); 
	} 

	virtual ~CSingleton() 
	{  
		m_pSingleton = 0;  
	} 

	static T& GetInstance(void) 
	{  
		return (*m_pSingleton);  
	} 

	static T* GetInstancePtr(void) 
	{  
		return (m_pSingleton); 
	} 
}; 

template<typename T> T* CSingleton<T>::m_pSingleton = 0; 

#endif