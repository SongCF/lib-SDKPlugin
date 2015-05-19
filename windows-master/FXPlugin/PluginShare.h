
#pragma once

#include <map>

namespace FX{


enum class ShareResultCode
{
	eSuccess = 0,
	eCancle,
	eError,
};




class ShareResultListener
{
public:
    virtual void onShareResult(ShareResultCode ret, const char* msg) = 0;
};




class PluginShare
{
public:

    /**
    @breif set the result listener
    @param pListener The callback object for share result
    @wraning Must invoke this interface before share
    */
    virtual void setShareListener(ShareResultListener* pListener) = 0;

	/**
    @brief share information
    @param info The info of share, contains key:
			link : �������� ������sdk��link����ʱ���������漸���ֶΣ��磺Facebook��
			name : ����
			caption : ������
			description : ����
			pictureURL : ���������ͼƬ
			pictureImg : ����ͼƬ���������ͼƬΪ�ҵ��ͻ�ʹ�� urlͼƬ����
    @warning For different plugin, the parameter should have other keys to share.
             Look at the manual of plugins.
    */
    virtual void share(std::map<std::string, std::string>* info) = 0;

};


}