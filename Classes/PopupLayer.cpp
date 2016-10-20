#include "PopupLayer.h"
USING_NS_CC;

// 构造函数中变量设初值
PopupLayer::PopupLayer()
{
	m_contentPadding = 0;
	m_contentPaddingTop = 0;
	m_pMenu = NULL;
	m_callbackListener = NULL;
	m_callback = NULL;
	m_sfBackGround = NULL;
	m_s9BackGround = NULL;
	m_ltContentText = NULL;
	m_ltTitle = NULL;
}

//释放
PopupLayer::~PopupLayer()
{

	CC_SAFE_RELEASE(m_pMenu);
	CC_SAFE_RELEASE(m_sfBackGround);
	CC_SAFE_RELEASE(m_s9BackGround);
	CC_SAFE_RELEASE(m_ltContentText);
	CC_SAFE_RELEASE(m_ltTitle);
}

PopupLayer* PopupLayer::create( const char* backgroundImage ){
	PopupLayer* popup = new PopupLayer();
	popup->init(backgroundImage);
	popup->autorelease();
	return popup;
}
//初始化

bool PopupLayer::init(const char* backgroundImage)
{
	if ( !CCLayer::init() ){
		return false;
	}
	CCSprite *backgroud = CCSprite::create(backgroundImage);
	addChild(backgroud);
	CCMenu* menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	setMenuButton(menu);  //set()方法
	setTouchEnabled(true);  //开启触摸响应

	setTitle("Copyright@2015,fzj", 30);
	std::string text = WStrToUTF8(L"1、天苍苍野茫茫感谢猴子派来逗B坑爹队友一双\n\n2、感谢图书馆两本书：\n        Cocos2d-x入门经典，冯立鹏\n        Cocos2D-X游戏开发技术精解，刘剑桌\n\n3、最后感谢池之标老师带我进入cocos2dx的世界");
	setContentText(text.c_str(), 15, 50, 150);
	addButton("botton_defray_back_001.png", "botton_defray_back_002.png", "Ok", 0);
	return true;
}


//重写触摸注册函数，重新给定触摸级别

void PopupLayer::registerWithTouchDispatcher(){
	// 这里的触摸优先级设置为-128，与CCMenu同级，保证了屏蔽下方的触摸
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}


//触摸函数ccTouchBegan，返回true

bool PopupLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent ){
	return true;
}

//给标题变量赋值

void PopupLayer::setTitle( const char* title, int fontsize ){
	CCLabelTTF* ltfTitle = CCLabelTTF::create(title, "American Typewriter", fontsize);
	ltfTitle->setColor(ccc3(0, 0, 0));
	setLabelTitle(ltfTitle);
}


//给文本变量赋值

void PopupLayer::setContentText( const char* text, int fontsize, int padding, int paddingTop ){
	CCLabelTTF* content = CCLabelTTF::create(text, "Marker Felt", fontsize);
	content->setColor(ccc3(0, 0, 0));
	setLabelContentText(content);
	content->setDimensions(CCSizeMake(30, 0));
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}


//给下层层变量和回调函数变量赋值
void PopupLayer::setCallBackFunc( CCObject* target, SEL_CallFuncN callfun ){
	m_callbackListener = target;
	m_callback = callfun;
}


//给menu菜单变量添加Item

bool PopupLayer::addButton( const char* normalImage, const char* selectedImage, const char* title, int tag ){

	// 创建图片菜单按钮
	CCMenuItemImage* menuImage = CCMenuItemImage::create(
		normalImage, selectedImage, this, menu_selector(PopupLayer::buttonCallBack));
	menuImage->setTag(tag);
	//menuImage->setPosition(ccp(50,-225.0f));


	/* 添加文字说明并设置位置
	CCSize menuSize = menuImage->getContentSize();
	CCLabelTTF* ttf = CCLabelTTF::create(title, "Arial", 15);
	ttf->setColor(ccc3(0, 0, 0));
	ttf->setPosition(ccp(menuSize.width/2, menuSize.height/2));
	menuImage->addChild(ttf);*/
	getMenuButton()->addChild(menuImage);
	return true;
}


//销毁弹出框，传递参数node给下层

void PopupLayer::buttonCallBack( CCObject* pSender ){
	CCNode* node = (CCNode*)pSender;
	CCLog("touch tag: %d", node->getTag());
	if (m_callback && m_callbackListener)
	{

		//执行HelloWorld层的回调函数，传递node参数
		(m_callbackListener->*m_callback)(node);
	}
	this->removeFromParentAndCleanup(true);
}


//全部参数都设定好后，在运行时动态加载

void PopupLayer::onEnter(){
	CCLayer::onEnter();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint center = ccp(winSize.width/2, winSize.height/2);
	CCSize contentSize;

	getMenuButton()->setPosition(ccp(50,-180));
	this->addChild(getMenuButton());

	// 显示对话框标题
	if (getLabelTitle()){
		getLabelTitle()->setPosition(ccp(50, 180));
		this->addChild(getLabelTitle());
	}

	//显示文本内容
	if (getLabelContentText()){
		CCLabelTTF* ltf = getLabelContentText();
		ltf->setPosition(ccp(70, 80));
		ltf->setDimensions(ccp(25*15, 8*15));
		ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
		this->addChild(ltf);
	}

	setPosition(center);

	//弹出效果
	CCSequence *popupActions = CCSequence::create(
		CCScaleTo::create(0.0, 0.0), 
		CCScaleTo::create(0.06, 1.05),
		CCScaleTo::create(0.08, 0.95),
		CCScaleTo::create(0.08, 1.0), NULL);
	this->runAction(popupActions);

}

//退出
void PopupLayer::onExit(){
	CCLayer::onExit();
}
/************************************************************************/
/* 摘至 http://blog.itpub.net/14466241/viewspace-752027/                */
/************************************************************************/

void PopupLayer::WStrToUTF8( std::string& dest, const wstring& src )
{
	dest.clear();
	for (size_t i = 0; i < src.size(); i++){
		wchar_t w = src[i];
		if (w <= 0x7f)
			dest.push_back((char)w);
		else if (w <= 0x7ff){
			dest.push_back(0xc0 | ((w >> 6)& 0x1f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (w <= 0xffff){
			dest.push_back(0xe0 | ((w >> 12)& 0x0f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff){
			dest.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation
			dest.push_back(0x80| ((w >> 12) & 0x3f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
}

std::string PopupLayer::WStrToUTF8( const std::wstring& str )
{
	std::string result;
	WStrToUTF8(result, str);
	return result;
}
