#ifndef _cvrammanager_h_
#define _cvrammanager_h_


class CVRAMManager
{
private:
	static CVRAMManager instance;

public: 
	static CVRAMManager * Get()
	{
		return &CVRAMManager::instance;
	}

	void EvictDefaultPoolResources() {}

};

#endif