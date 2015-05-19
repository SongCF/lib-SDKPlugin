﻿#include "ProductInfoHelper.h"

#include "CocoStudio/Json/rapidjson/document.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#define FILE_Path "ProductID.txt"
#else
#define FILE_Path "config/ProductID.txt"
#endif
//
#define KEY_VerChannel	"VersionChannelID"
#define KEY_Product		"Product"

#define KEY_ID			"ID"
#define KEY_Name		"name"
#define KEY_Describe	"describe"
#define KEY_Price		"price"
#define KEY_Channel		"channel"

#define KEY_ChannelName		 "channelName"
#define KEY_ChannelID		 "channelID"
#define KEY_ChannelProductID "productID"


ProductInfoHelper* ProductInfoHelper::_productInfoHelper = nullptr;

ProductInfoHelper::ProductInfoHelper()
{

}

ProductInfoHelper* ProductInfoHelper::getHelper()
{
	if (! _productInfoHelper){
		_productInfoHelper = new ProductInfoHelper();
		_productInfoHelper->initData();
	}
	return _productInfoHelper;
}

bool ProductInfoHelper::initData()
{
	CCLOG("%s begin", __FUNCTION__);
	string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(FILE_Path);
	unsigned long dataSize = 0;
	unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(filePath.c_str(), "r", &dataSize);
	if (dataSize == 0 || data == nullptr)
	{
		CC_SAFE_DELETE_ARRAY(data);
		return false;
	}

	string temp((char*)data, dataSize);
	delete[] data;
	rapidjson::Document d;
	d.Parse<0>(temp.c_str());

	if (d.HasParseError())  //打印解析错误
	{
		CCLOG("%s ---> GetParseError %s\n", __FUNCTION__, d.GetParseError());
		return false;
	}
	else if (d.IsObject()) 
	{
		if (d.HasMember(KEY_VerChannel))
		{
			m_ChannelId = d[KEY_VerChannel].GetString();
		}

		if (d.HasMember(KEY_Product) && d[KEY_Product].IsArray())
		{
			const rapidjson::Value& arr = d[KEY_Product];
			for (int i=0,count=arr.Size(); i<count; ++i)
			{
				if (arr[i].HasMember(KEY_ID) && arr[i].HasMember(KEY_Describe) && arr[i].HasMember(KEY_Price) && arr[i].HasMember(KEY_Channel))
				{
					ProductInfo one;
					one.ID = arr[i][KEY_ID].GetInt();
					one.name = arr[i][KEY_Name].GetString();
					one.describe = arr[i][KEY_Describe].GetString();
					one.price = arr[i][KEY_Price].GetInt();

					//channel
					const rapidjson::Value& channel = arr[i][KEY_Channel];
					for (int channelIdx=0,channelCount=channel.Size(); channelIdx<channelCount; ++channelIdx)
					{
						//key渠道ID，value渠道计费码
						one.channelProduct.insert(std::make_pair(channel[channelIdx][KEY_ChannelID].GetString()
							,channel[channelIdx][KEY_ChannelProductID].GetString()));
					}

					m_productList.push_back(one);
				}
				else 
				{
					return false;
				}
			}
		}
		CCLOG("%s end", __FUNCTION__);
		return true;
	}

	return false;
}

const ProductInfo* ProductInfoHelper::getOneProductInfo(ProductID productID)
{
	for (int i=0,count=m_productList.size(); i<count; ++i)
	{
		if (m_productList[i].ID == productID) 
			return &m_productList[i];
	}

	return nullptr;
}