#include "StaticData.h"


static StaticData *g_sharedStaticData = NULL;


StaticData::StaticData()
{
	_staticDataPath = PLIST_PATH;
}

StaticData::~StaticData()
{
	CC_SAFE_RELEASE_NULL(_dictionary);
}

StaticData* StaticData::sharedStaticData()
{
	if(g_sharedStaticData == NULL)
	{
		g_sharedStaticData = new StaticData();
		g_sharedStaticData->init();
	}

	return g_sharedStaticData;
}

bool StaticData::init()
{
	do
	{
		_dictionary = cocos2d::CCDictionary::createWithContentsOfFile(_staticDataPath.c_str());
		if(_dictionary == NULL)
			return false;
		CC_SAFE_RETAIN(_dictionary);
	} while (0);
	return true;
}

const char* StaticData::stringFromKey( std::string key )
{
	return _dictionary->valueForKey(key)->getCString();	
}

int StaticData::intFromKey( std::string key )
{
	return _dictionary->valueForKey(key)->intValue();
}

float StaticData::floatFromKey( std::string key )
{
	return _dictionary->valueForKey(key)-> floatValue ();
}

bool StaticData::booleanFromKey( std::string key )
{
	return _dictionary->valueForKey(key)-> boolValue ();
}

cocos2d::CCPoint StaticData::pointFromKey( std::string key )
{
	const char *temp = _dictionary->valueForKey(key)->getCString();
	return cocos2d::CCPointFromString(temp);
}

cocos2d::CCRect StaticData::rectFromKey( std::string key )
{
	const char *temp = _dictionary->valueForKey(key)->getCString();
	return cocos2d::CCRectFromString(temp);
}

cocos2d::CCSize StaticData::sizeFromKey( std::string key )
{
	const char *temp = _dictionary->valueForKey(key)->getCString();
	return cocos2d::CCSizeFromString(temp);
}

void StaticData::purge()//���� �Ǿ�̬��Ա���ñ������ض�������ԣ�һ��ʼû���������static���޷���direction������������һ���
{
	CC_SAFE_RELEASE_NULL(g_sharedStaticData);
}

