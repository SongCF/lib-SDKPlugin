#ifndef __FXPlugin_DataEye_H__
#define __FXPlugin_DataEye_H__


#include "FXPlugin/PluginAnalytics.h"
#include <map>
#include <string>



namespace FX{ namespace Plugin{


class DataEye : public PluginAnalytics
{
private:
	DataEye();
public:
	static DataEye* getInstance();

public:
	////////////////////////////////////////////////////////////////////////////////////////////
	//1. custom event   --- �Զ����¼�
	////////////////////////////////////////////////////////////////////////////////////////////
	virtual void logError(const char* errorId, const char* message);
	virtual void logEvent(const char* eventId, LogEventMap* paramMap = NULL);
/*	virtual void logTimedEventBegin(const char* eventId);
	virtual void logTimedEventEnd(const char* eventId);*/


	////////////////////////////////////////////////////////////////////////////////////////////
	//2. Account   --- �˻� ͳ��
	//����DataEye���������ע����Ϸ�˻��Ϳ����棬��ô��ʹ�� DC_DEFAULTģʽ
	//����DataEye�����ʹ����DC_AFTER_LOGINģʽ����ôֻ����setAcoount֮��Ż��ϴ�����
	////////////////////////////////////////////////////////////////////////////////////////////
    /**
     @brief �����˻�id����ʹ���˻�ͳ�ƹ���ʱ����������id��accountId�豣֤ȫ��Ψһ
	 @param ����������豸Ϊ��ҵ�Ԫ����ͳ�ƣ�����setAccountʱ����getDeviceId()��SDK�������Զ������豸ID��ΪAccount
     */
	virtual void setAccount(const char* accountId);
	virtual const char* getDeviceId();
	//�����ʻ�����
	virtual void setAccountType(AccountType accountType);
	//�����ʻ�����������DataEyeû�иýӿڣ�
	virtual void setAccountName(const char* accountName);
	//���ü���(��ұ�ǩ,vip�ȼ���..)
	virtual void setLevel(int level);
	//�����Ա�
	virtual void setGender(AcountGender gender);
	//��������  0-120
	virtual void setAge(int age);
	//��������
	virtual void setGameServer(const char* gameServer);


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
	 2.iapId(�ڹ���Ʒ��/ID)
	 3.currencyAmount(��������)
	 4.currencyType(��������)��ʹ�ù��ʱ�׼��֯ISO 4217�й淶��3λ��ĸ�����ǻ������͡����������CNY����ԪUSD��ŷԪEUR
	 5.virtualCurrencyAmount(����3��������Ϸ�����������)
	 6.paymentType(֧������)���磺��֧��������ƻ���ٷ�����XX֧��SDK��
	*/
	virtual void onChargeRequest(const char* orderId, const char* itemName, double currencyAmount, 
		const char* currencyType, double virtualCurrencyAmount, const char* paymentType);
	//��ֵ�ɹ�
	virtual void onChargeSuccess(const char* orderId);
	//���������
	/*
	 *pref:������������¼�������ɾͽ����Ȼ�����ѷ��Ÿ���������,
		ֻ��ù���������ҵ���Ҳ��ᱻ��Ϊ������ҡ����������һ���뵽���е�����Ҳ�����
	*/
	virtual void onReward(double virtualCurrencyAmount, const char* reason);


	////////////////////////////////////////////////////////////////////////////////////////////
	//4. Item   --- ���� ��Ϸ���м�ֵ������ҵ����ѵ�
	////////////////////////////////////////////////////////////////////////////////////////////
	//��¼���ѵ� (���������ѵ㷢��ʱ�������)
	virtual void onPurchase(const char* itemName, int itemNumber, double priceInVirtualCurrency);
	//������Ʒ������ (��ĳ������/�����õ�����ʧ��ʱ�������)
	virtual void onUse(const char* itemName, int itemNumber, const char* reason);


	////////////////////////////////////////////////////////////////////////////////////////////
	//5. Mission   --- ���� ����/�ؿ�/����
	////////////////////////////////////////////////////////////////////////////////////////////
	/*
	 *ͬһ��missionId�����δ����ǰ���ظ�������onBegin���ã������¿�ʼ��ʱ����һ�εĵ��ñ�������
	*/
	//���ܻ����
	virtual void onBegin(const char* missionId);
	//���
	virtual void onCompleted(const char* missionId);
	//ʧ��
	virtual void onFailed(const char* missionId, const char* cause);



private:
	//����֧���������Ϣ
	//key: orderId
	//value: 1.currencyAmount 2.currencyType 3.paymentType 4.itemName
	typedef std::map<std::string, std::tuple<double,std::string,std::string,std::string>> DataeyePaymentInfo;
	DataeyePaymentInfo m_paymentInfo;
};

}}



#endif /* define(__FXPlugin_DataEye_H__) */