#ifndef _cvbibmanager_h_
#define _cvbibmanager_h_


class CVBIBManager
{
private:
	static CVBIBManager instance;

public: 
	static CVBIBManager * Get()
	{
		return &CVBIBManager::instance;
	}

	void EvictDefaultPoolResources() {}

};

#endif