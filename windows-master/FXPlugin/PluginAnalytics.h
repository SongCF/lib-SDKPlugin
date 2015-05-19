#ifndef __FXPlugin_PluginAnalytics_H__
#define __FXPlugin_PluginAnalytics_H__


#include <map>
#include <string>

namespace FX{

//Tag
#define PLUGIN_ANALYTICS_TalkingData "PluginAnalyticsTalkingData"
#define PLUGIN_ANALYTICS_DataEye "PluginAnalyticsDataEye"



typedef std::map<std::string,std::string> LogEventMap;

class PluginAnalytics
{
public:
	enum AccountType
	{
		eAccountAnonymous = 0,		//����
		eAccountRegistered = 1,		//����Ϸ��ע��

		//�������˺ţ����ڣ�
		eAccountSianWeibo = 11,		//����΢��
		eAccountQQ = 12,			//QQ
		eAccountTencentWeibo = 13,  //��Ѷ΢��
		eAccountND91 = 14,			//����91

		//�������˺ţ�����)
		eAccountFacebook = 21,		//Facebook

		//Ԥ����10���Զ�����ʻ�����
		eAccountType1 = 101,
		eAccountType2 = 102,
		eAccountType3 = 103,
		eAccountType4 = 104,
		eAccountType5 = 105,
// 		eAccountType6 = 106,
// 		eAccountType7 = 107,
// 		eAccountType8 = 108,
// 		eAccountType9 = 109,
// 		eAccountType10 = 110
	};
	enum AcountGender
	{
		eGenderUnknown = 0,
		eGenderMale = 1,
		eGenderFemale = 2
	};
public:
	////////////////////////////////////////////////////////////////////////////////////////////
	//1. custom event   --- �Զ����¼�
	////////////////////////////////////////////////////////////////////////////////////////////
	virtual void logError(const char* errorId, const char* message) = 0;
	virtual void logEvent(const char* eventId, LogEventMap* paramMap = NULL) = 0;


	////////////////////////////////////////////////////////////////////////////////////////////
	//2. Account   --- �˻� ͳ��
	////////////////////////////////////////////////////////////////////////////////////////////
    /**
     @brief �����˻�id����ʹ���˻�ͳ�ƹ���ʱ����������id��accountId�豣֤ȫ��Ψһ
	 @param ����������豸Ϊ��ҵ�Ԫ����ͳ�ƣ�����setAccountʱ����getDeviceId()��SDK�������Զ������豸ID��ΪAccount
     */
	virtual void setAccount(const char* accountId) = 0;
	virtual const char* getDeviceId() = 0;
	//�����ʻ�����
	virtual void setAccountType(AccountType accountType) = 0;
	//�����ʻ���������
	virtual void setAccountName(const char* accountName) = 0;
	//���ü���
	virtual void setLevel(int level) = 0;
	//�����Ա�
	virtual void setGender(AcountGender gender) = 0;
	//��������  0-120
	virtual void setAge(int age) = 0;
	//��������
	virtual void setGameServer(const char* gameServer) = 0;


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
	/*
	 * @parma 
	 1.orderId(Ψһ����ID) 
	 2.itemName(�ڹ���Ʒ��/ID)
	 3.currencyAmount(��������)
	 4.currencyType(��������)��ʹ�ù��ʱ�׼��֯ISO 4217�й淶��3λ��ĸ�����ǻ������͡����������CNY����ԪUSD��ŷԪEUR
	 5.virtualCurrencyAmount(����3��������Ϸ�����������)
	 6.paymentType(֧������)���磺��֧��������ƻ���ٷ�����XX֧��SDK��
	*/
	virtual void onChargeRequest(const char* orderId, const char* itemName, double currencyAmount, 
		const char* currencyType, double virtualCurrencyAmount, const char* paymentType) = 0;
	//��ֵ�ɹ�
	virtual void onChargeSuccess(const char* orderId) = 0;
	//���������
	/*
	 *pref:������������¼�������ɾͽ����Ȼ�����ѷ��Ÿ���������,
		ֻ��ù���������ҵ���Ҳ��ᱻ��Ϊ������ҡ����������һ���뵽���е�����Ҳ�����
	*/
	virtual void onReward(double virtualCurrencyAmount, const char* reason) = 0;


	////////////////////////////////////////////////////////////////////////////////////////////
	//4. Item   --- ���� ��Ϸ���м�ֵ������ҵ����ѵ�
	////////////////////////////////////////////////////////////////////////////////////////////
	//��¼���ѵ� (���������ѵ㷢��ʱ�������)
	virtual void onPurchase(const char* itemName, int itemNumber, double priceInVirtualCurrency) = 0;
	//������Ʒ������ (��ĳ������/�����õ�����ʧ��ʱ�������)
	virtual void onUse(const char* itemName, int itemNumber, const char* reason) = 0;


	////////////////////////////////////////////////////////////////////////////////////////////
	//5. Mission   --- ���� ����/�ؿ�/����
	////////////////////////////////////////////////////////////////////////////////////////////
	/*
	 *ͬһ��missionId�����δ����ǰ���ظ�������onBegin���ã������¿�ʼ��ʱ����һ�εĵ��ñ�������
	*/
	//���ܻ����
	virtual void onBegin(const char* missionId) = 0;
	//���
	virtual void onCompleted(const char* missionId) = 0;
	//ʧ��
	virtual void onFailed(const char* missionId, const char* cause) = 0;
};
}

#endif /* define(__FXPlugin_PluginAnalytics_H__) */