#pragma once
#define PLIST_PATH "static_data.plist" //默认在resources下了

#include "cocos2d.h"

using namespace std;
class StaticData : public cocos2d::CCObject
{
	CC_SYNTHESIZE_READONLY(string,_staticDataPath,StaticDataPath);
public:
	
	StaticData();////////////////////////把拷贝这这些写成私有
	~StaticData();
	static StaticData* sharedStaticData();
	bool init();
	const char* stringFromKey(std::string key);
	int intFromKey(std::string key);
	float floatFromKey (std::string key);
	bool booleanFromKey (std::string key);
	cocos2d::CCPoint pointFromKey(std::string key);
	cocos2d::CCRect rectFromKey(std::string key);
	cocos2d::CCSize sizeFromKey(std::string key);
	static void purge();

protected:
	cocos2d::CCDictionary *_dictionary;
	//string _staticDataPath;
};

#define STATIC_DATA_STRING(key) StaticData::sharedStaticData()->stringFromKey(key)
#define STATIC_DATA_INT(key) StaticData::sharedStaticData()->intFromKey(key)
#define STATIC_DATA_FLOAT(key) StaticData::sharedStaticData()->floatFromKey(key)