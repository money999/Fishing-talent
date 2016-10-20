#include "PopupLayer.h"
USING_NS_CC;

// ���캯���б������ֵ
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

//�ͷ�
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
//��ʼ��

bool PopupLayer::init(const char* backgroundImage)
{
	if ( !CCLayer::init() ){
		return false;
	}
	CCSprite *backgroud = CCSprite::create(backgroundImage);
	addChild(backgroud);
	CCMenu* menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	setMenuButton(menu);  //set()����
	setTouchEnabled(true);  //����������Ӧ

	setTitle("Copyright@2015,fzj", 30);
	std::string text = WStrToUTF8(L"1����Բ�Ұãã��л����������B�ӵ�����һ˫\n\n2����лͼ��������飺\n        Cocos2d-x���ž��䣬������\n        Cocos2D-X��Ϸ�����������⣬������\n\n3������л��֮����ʦ���ҽ���cocos2dx������");
	setContentText(text.c_str(), 15, 50, 150);
	addButton("botton_defray_back_001.png", "botton_defray_back_002.png", "Ok", 0);
	return true;
}


//��д����ע�ắ�������¸�����������

void PopupLayer::registerWithTouchDispatcher(){
	// ����Ĵ������ȼ�����Ϊ-128����CCMenuͬ������֤�������·��Ĵ���
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}


//��������ccTouchBegan������true

bool PopupLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent ){
	return true;
}

//�����������ֵ

void PopupLayer::setTitle( const char* title, int fontsize ){
	CCLabelTTF* ltfTitle = CCLabelTTF::create(title, "American Typewriter", fontsize);
	ltfTitle->setColor(ccc3(0, 0, 0));
	setLabelTitle(ltfTitle);
}


//���ı�������ֵ

void PopupLayer::setContentText( const char* text, int fontsize, int padding, int paddingTop ){
	CCLabelTTF* content = CCLabelTTF::create(text, "Marker Felt", fontsize);
	content->setColor(ccc3(0, 0, 0));
	setLabelContentText(content);
	content->setDimensions(CCSizeMake(30, 0));
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}


//���²������ͻص�����������ֵ
void PopupLayer::setCallBackFunc( CCObject* target, SEL_CallFuncN callfun ){
	m_callbackListener = target;
	m_callback = callfun;
}


//��menu�˵��������Item

bool PopupLayer::addButton( const char* normalImage, const char* selectedImage, const char* title, int tag ){

	// ����ͼƬ�˵���ť
	CCMenuItemImage* menuImage = CCMenuItemImage::create(
		normalImage, selectedImage, this, menu_selector(PopupLayer::buttonCallBack));
	menuImage->setTag(tag);
	//menuImage->setPosition(ccp(50,-225.0f));


	/* �������˵��������λ��
	CCSize menuSize = menuImage->getContentSize();
	CCLabelTTF* ttf = CCLabelTTF::create(title, "Arial", 15);
	ttf->setColor(ccc3(0, 0, 0));
	ttf->setPosition(ccp(menuSize.width/2, menuSize.height/2));
	menuImage->addChild(ttf);*/
	getMenuButton()->addChild(menuImage);
	return true;
}


//���ٵ����򣬴��ݲ���node���²�

void PopupLayer::buttonCallBack( CCObject* pSender ){
	CCNode* node = (CCNode*)pSender;
	CCLog("touch tag: %d", node->getTag());
	if (m_callback && m_callbackListener)
	{

		//ִ��HelloWorld��Ļص�����������node����
		(m_callbackListener->*m_callback)(node);
	}
	this->removeFromParentAndCleanup(true);
}


//ȫ���������趨�ú�������ʱ��̬����

void PopupLayer::onEnter(){
	CCLayer::onEnter();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint center = ccp(winSize.width/2, winSize.height/2);
	CCSize contentSize;

	getMenuButton()->setPosition(ccp(50,-180));
	this->addChild(getMenuButton());

	// ��ʾ�Ի������
	if (getLabelTitle()){
		getLabelTitle()->setPosition(ccp(50, 180));
		this->addChild(getLabelTitle());
	}

	//��ʾ�ı�����
	if (getLabelContentText()){
		CCLabelTTF* ltf = getLabelContentText();
		ltf->setPosition(ccp(70, 80));
		ltf->setDimensions(ccp(25*15, 8*15));
		ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
		this->addChild(ltf);
	}

	setPosition(center);

	//����Ч��
	CCSequence *popupActions = CCSequence::create(
		CCScaleTo::create(0.0, 0.0), 
		CCScaleTo::create(0.06, 1.05),
		CCScaleTo::create(0.08, 0.95),
		CCScaleTo::create(0.08, 1.0), NULL);
	this->runAction(popupActions);

}

//�˳�
void PopupLayer::onExit(){
	CCLayer::onExit();
}
/************************************************************************/
/* ժ�� http://blog.itpub.net/14466241/viewspace-752027/                */
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
