#include <iostream> 
#include <iterator> 
#include <map> 
#include <list>

#define MULTI

using namespace std; 

typedef struct
{
    uint32_t    slotId;
    uint32_t    onvifRange;
    uint32_t    rtspRange;
    std::string ipAddr;
}bridgeData;

class cServiceManager
{
  private:
	//cServiceManager();
	//virtual ~cServiceManager()=default;
    //std::map<uint64_t,std::list<std::string>> m_oDeviceSlotMap;
    //std::map<uint64_t, bridgeData> m_bridgeDataMap;
    std::map<uint64_t, std::list<bridgeData>> m_bridgeDataMap;

  public:
    static cServiceManager& GetInstance()
    {
        static cServiceManager obj;
        return obj;
    }
#ifdef MULTI
	uint32_t _GetBridgeCount(void);
    void AddNodeToMap(int devid, bridgeData bdata);
    void Print(int devid);
#else
    void AddNodeToMap(bridgeData bdata);
    void Print(void);
#endif
};

#ifdef MULTI
void cServiceManager::AddNodeToMap(int devid, bridgeData bdata)
{
    if(m_bridgeDataMap.find(devid) != m_bridgeDataMap.end())
    {
	    std::list<bridgeData> *bDataList;
		printf("Present\n");
		bDataList = &m_bridgeDataMap[devid];
		bDataList->emplace(bDataList->end(), bdata);
	}
	else
	{
		std::list<bridgeData> bDataList;
		bDataList.emplace(bDataList.end(), bdata);
		cServiceManager::m_bridgeDataMap.insert(std::make_pair(devid, bDataList));
		//cServiceManager::m_bridgeDataMap.insert(pair<uint64_t, std::list<bridgeData>>(devid, bDataList));
		printf("Empty\n");
	}
}

uint32_t cServiceManager::_GetBridgeCount(void)
{
    uint32_t    brCount = 0;
    std::map<uint64_t, std::list<bridgeData>>::iterator itr;

    for (itr = m_bridgeDataMap.begin(); itr != m_bridgeDataMap.end(); ++itr) { 
        if(m_bridgeDataMap.find(itr->first) != m_bridgeDataMap.end())
        {
            brCount += m_bridgeDataMap[itr->first].size();
        }
    }
    return brCount;
}

#else
int cServiceManager::AddNodeToMap(bridgeData bdata)
{
	static int idx = 0;
	cServiceManager::m_bridgeDataMap.insert(pair<uint64_t, bridgeData>(idx, bdata));
	return idx++;
}
#endif

#ifdef MULTI
void cServiceManager::Print(int devid)
{
	list<bridgeData>::iterator itr; 
	cout << "\nThe map  is : \n"; 
	cout << "\tKEY\tELEMENT\n"; 
	for (itr = m_bridgeDataMap[devid].begin(); itr != m_bridgeDataMap[devid].end(); ++itr) { 
		cout << '\t' << devid 
			<< '\t' << itr->slotId
			<< '\t' << itr->onvifRange
			<< '\t' << itr->rtspRange
			<< '\t' << itr->ipAddr << '\n'; 
	}

	cout << endl; 
}

#else

void cServiceManager::Print(void)
{ 
	map<uint64_t, bridgeData>::iterator itr; 
	cout << "\nThe map gquiz1 is : \n"; 
	cout << "\tKEY\tELEMENT\n"; 
	for (itr = m_bridgeDataMap.begin(); itr != m_bridgeDataMap.end(); ++itr) { 
		cout << '\t' << itr->first 
			<< '\t' << itr->second.slotId
			<< '\t' << itr->second.onvifRange
			<< '\t' << itr->second.rtspRange
			<< '\t' << itr->second.ipAddr << '\n'; 
	} 
	cout << endl; 
}

#endif


int main() 
{ 
    cServiceManager sm = cServiceManager::GetInstance();
	//map<int, bridgeData>::iterator itr;
	bridgeData data1 = {10, 40, 60, "11.12.13.14"};
	bridgeData data2 = {10, 40, 70, "14.11.13.14"};
	
#ifdef MULTI
    sm.AddNodeToMap(12132141, data1);
    sm.AddNodeToMap(12132141, data2);
    sm.AddNodeToMap(22312311, data1);
    sm.AddNodeToMap(22312311, data2);
    sm.AddNodeToMap(22312311, data2);
    sm.Print(12132141);
    sm.Print(22312311);
#else
    sm.AddNodeToMap(data1);
    sm.AddNodeToMap(data2);
    sm.Print();
#endif
	cout <<sm._GetBridgeCount() << '\n';
#if 0
	// assigning the elements from gquiz1 to gquiz2 
	map<int, bridgeData> gquiz2(sm.m_bridgeDataMap.begin(), sm.m_bridgeDataMap.end()); 

	// print all elements of the map gquiz2 
	cout << "\nThe map gquiz2 after"
		<< " assign from gquiz1 is : \n"; 
	cout << "\tKEY\tELEMENT\n"; 
	for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) { 
		cout << '\t' << itr->first 
			<< '\t' << itr->second.slotId
			<< '\t' << itr->second.onvifRange
			<< '\t' << itr->second.rtspRange
			<< '\t' << itr->second.ipAddr << '\n'; 
	} 
	cout << endl; 


	// remove all elements with key = 2
	int num; 
	num = gquiz2.erase(2); 
	cout << "\ngquiz2.erase(4) : "; 
	cout << num << " removed \n"; 
	cout << "\tKEY\tELEMENT\n"; 
	for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) { 
		cout << '\t' << itr->first 
			<< '\t' << itr->second.slotId
			<< '\t' << itr->second.onvifRange
			<< '\t' << itr->second.rtspRange
			<< '\t' << itr->second.ipAddr << '\n'; 
	} 

	cout << endl; 

	// lower bound and upper bound for map gquiz1 key = 2
	cout << "gquiz1.lower_bound(2) : "
		<< "\tKEY = "; 
	cout << gquiz1.lower_bound(2)->first << '\t'; 
	cout << "\tELEMENT = "
		<< gquiz1.lower_bound(2)->second << endl; 
	cout << "gquiz1.upper_bound(2) : "
		<< "\tKEY = "; 
	cout << gquiz1.upper_bound(2)->first << '\t'; 
	cout << "\tELEMENT = "
		<< gquiz1.upper_bound(2)->second << endl; 
#endif
	return 0; 
} 
