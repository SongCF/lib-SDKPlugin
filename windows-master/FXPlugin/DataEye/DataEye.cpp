
#include "FXPlugin/DataEye/DataEye.h"

#include "cocos2d.h"
using namespace cocos2d;

//data eye lib
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "FXPlugin/DataEye/DataEyeLib/Android/include/DCAgent.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "FXPlugin/DataEye/DataEyeLib/IOS/DCAgent.h"
#endif



using namespace FX;
using namespace FX::Plugin;

DataEye::DataEye()
{
}

DataEye* DataEye::getInstance()
{
	static DataEye* _instanceDataEye = nullptr;
	if (!_instanceDataEye){
		_instanceDataEye = new DataEye();
	}
	return _instanceDataEye;
}

////////////////////////////////////////////////////////////////////////////////////////////
//1. custom event   --- �Զ����¼�
////////////////////////////////////////////////////////////////////////////////////////////
void DataEye::logError(const char* errorId, const char* message)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	LogEventMap infoMap;
	infoMap.insert(std::make_pair("ErrorInfor", message));
	DCEvent::onEvent(errorId, &infoMap);
#endif
}
void DataEye::logEvent(const char* eventId, LogEventMap* paramMap)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCEvent::onEvent(eventId, paramMap);
#endif
}


////////////////////////////////////////////////////////////////////////////////////////////
//2. Account   --- �˻� ͳ��
////////////////////////////////////////////////////////////////////////////////////////////
/**
@brief �����˻�id����ʹ���˻�ͳ�ƹ���ʱ����������id��accountId�豣֤ȫ��Ψһ
@param ����������豸Ϊ��ҵ�Ԫ����ͳ�ƣ�����setAccountʱ����getDeviceId()��SDK�������Զ������豸ID��ΪAccount
*/
void DataEye::setAccount(const char* accountId)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCAccount::login(accountId);
#endif
}
const char* DataEye::getDeviceId()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	return DCAgent::getUID();
#endif
	return "";
}

//�����ʻ�����
void DataEye::setAccountType(AccountType accountType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCAccountType type;
	switch (accountType)
	{
	case FX::PluginAnalytics::eAccountAnonymous:
		type = DCAccountType::DC_Anonymous;
		break;
	case FX::PluginAnalytics::eAccountRegistered:
		type = DCAccountType::DC_Registered;
		break;
	case FX::PluginAnalytics::eAccountSianWeibo:
		type = DCAccountType::DC_SinaWeibo;
		break;
	case FX::PluginAnalytics::eAccountQQ:
		type = DCAccountType::DC_QQ;
		break;
	case FX::PluginAnalytics::eAccountTencentWeibo:
		type = DCAccountType::DC_QQWeibo;
		break;
	case FX::PluginAnalytics::eAccountND91:
		type = DCAccountType::DC_ND91;
		break;
	case FX::PluginAnalytics::eAccountFacebook:
		type = DCAccountType::DC_Type1;
		break;
	case FX::PluginAnalytics::eAccountType1:
		type = DCAccountType::DC_Type2;
		break;
	case FX::PluginAnalytics::eAccountType2:
		type = DCAccountType::DC_Type3;
		break;
	case FX::PluginAnalytics::eAccountType3:
		type = DCAccountType::DC_Type4;
		break;
	case FX::PluginAnalytics::eAccountType4:
		type = DCAccountType::DC_Type5;
		break;
	case FX::PluginAnalytics::eAccountType5:
		type = DCAccountType::DC_Type6;
		break;
	default:
		type = DCAccountType::DC_Type10;
		break;
	}
	DCAccount::setAccountType(type);
#endif
}

//�����ʻ���������
void DataEye::setAccountName(const char* accountName)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	CCLOG("Warning: %s ---> DataEye has not this method", __FUNCTION__);
#endif
}
//���ü���
void DataEye::setLevel(int level)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCAccount::setLevel(level);
#endif
}
//�����Ա�
void DataEye::setGender(AcountGender gender)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	DCGender dcGender;
	switch (gender)
	{
	case FX::PluginAnalytics::eGenderMale:
		dcGender = DCGender::DC_MALE;
		break;
	case FX::PluginAnalytics::eGenderFemale:
		dcGender = DCGender::DC_FEMALE;
		break;
	default:
		dcGender = DCGender::DC_UNKNOWN;
		break;
	}
	DCAccount::setGender(dcGender);
#endif
}
//��������  0-120
void DataEye::setAge(int age)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCAccount::setAge(age);
#endif
}
//��������
void DataEye::setGameServer(const char* gameServer)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCAccount::setGameServer(gameServer);
#endif
}


////////////////////////////////////////////////////////////////////////////////////////////
//3. VirtualCurrency   --- ���� ��ֵ/���� �����������
////////////////////////////////////////////////////////////////////////////////////////////
/*
*��ֵ���̷��������ٽ׶Σ�1��������Ч�ĳ�ֵ����2ȷ��ĳ�γ�ֵ��������ɳ�ֵ��
*��������ҷ����ֵ����ʱ���������ѡ����ĳ����ֵ��������֧��������һ
*    �̣�����onChargeRequest��������ñʽ��׵�Ψһ����ID����ϸ��Ϣ����
*    ȷ�����֧���ɹ�ʱ����onChargeSuccess������֪��ɵ����ĸ�����ID��
*/
//��ֵ����
void DataEye::onChargeRequest(const char* orderId, const char* itemName, double currencyAmount, 
								  const char* currencyType, double virtualCurrencyAmount, const char* paymentType)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	m_paymentInfo.insert(std::make_pair(orderId,
		std::make_tuple(currencyAmount, currencyType, paymentType, itemName)));
#endif
}
//��ֵ�ɹ�
void DataEye::onChargeSuccess(const char* orderId)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DataeyePaymentInfo::iterator iter = m_paymentInfo.find(orderId);
	if (iter != m_paymentInfo.end())
	{
		double currencyAmount = 0.0;
		std::string currencyType;
		std::string paymentType;
		std::string itemName;
		std::tie(currencyAmount,currencyType,paymentType,itemName) = iter->second;
		DCVirtualCurrency::paymentSuccessInLevel(orderId, currencyAmount, currencyType.c_str(), paymentType.c_str(), itemName.c_str());
	}
	else
	{
		CCLOG("Error: %s ---> not found this orderId[%s]", __FUNCTION__, orderId);
	}
#endif
}
//���������
/*
*pref:������������¼�������ɾͽ����Ȼ�����ѷ��Ÿ���������,
ֻ��ù���������ҵ���Ҳ��ᱻ��Ϊ������ҡ����������һ���뵽���е�����Ҳ�����
*/
void DataEye::onReward(double virtualCurrencyAmount, const char* reason)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCCoin::gain(reason, "Unkown", virtualCurrencyAmount, 0);
#endif
}


////////////////////////////////////////////////////////////////////////////////////////////
//4. Item   --- ���� ��Ϸ���м�ֵ������ҵ����ѵ�
////////////////////////////////////////////////////////////////////////////////////////////
//��¼���ѵ� (���������ѵ㷢��ʱ�������)
void DataEye::onPurchase(const char* itemName, int itemNumber, double priceInVirtualCurrency)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCItem::buy(itemName, "", itemNumber, priceInVirtualCurrency, "Unknown", "");
#endif
}
//������Ʒ������ (��ĳ������/�����õ�����ʧ��ʱ�������)
void DataEye::onUse(const char* itemName, int itemNumber, const char* reason)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCItem::consume(itemName, "Unknown", itemNumber, reason);
#endif
}


////////////////////////////////////////////////////////////////////////////////////////////
//5. Mission   --- ���� ����/�ؿ�/����
////////////////////////////////////////////////////////////////////////////////////////////
/*
*ͬһ��missionId�����δ����ǰ���ظ�������onBegin���ã������¿�ʼ��ʱ����һ�εĵ��ñ�������
*/
//���ܻ����
void DataEye::onBegin(const char* missionId)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCTask::begin(missionId, DCTaskType::DC_Other);
#endif
}
//���
void DataEye::onCompleted(const char* missionId)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCTask::complete(missionId);
#endif
}
//ʧ��
void DataEye::onFailed(const char* missionId, const char* cause)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	DCTask::fail(missionId, cause);
#endif
}