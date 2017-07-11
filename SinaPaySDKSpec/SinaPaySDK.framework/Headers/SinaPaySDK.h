//
//  SinaPaySDK.h
//  SinaPaySDK
//
//  Created by ruigang on 2017/6/30.
//  Copyright © 2017年 ruigang. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SinaPayOrder.h"
#import "NSMutableDictionary+SinaPaySDKInit.h"

typedef NS_ENUM(NSInteger, SinaPaySDKResponseStatusCode)
{
    SinaPaySDKResponseStatusCodeFinished              = 200,//结束支付
    SinaPaySDKResponseStatusCodeStartPaying           = 50, //启动支付页面
    SinaPaySDKResponseStatusCodeUserCancel            = -100,//用户取消支付
    SinaPaySDKResponseStatusCodeSentFail              = -200,//支付失败
    SinaPaySDKResponseStatusCodeUnsupport             = -300,//不支持的支付请求
    SinaPaySDKResponseStatusCodeUnknown               = -400,//未知状态
};

/**
 当前支持的支付方式有四种：支付宝页面方式、网银支付方式、短信sp支付方式和充值卡方式
 */
typedef NS_ENUM(NSInteger, SinaPaySDKPaymentTypeCode)
{
    //PaySDKPaymentTypeNotChoose                     =100,//默认未选择状态
    SinaPaySDKPaymentTypeAlipay                        =110,//支付宝页面方式
//    SinaPaySDKPaymentTypeApplePay                      =150,//苹果支付页面
    SinaPaySDKPaymentTypeWechatPay                     =120,
    //SinaPaySDKPaymentTypeOnlineBank                    =120,//网银支付方式
    //SinaPaySDKPaymentTypeSMS                           =130,//短信sp支付方式
    //SinaPaySDKPaymentTypePrepaidCard                   =140,//充值卡方式
};

/**
 *  配置原平台回调处理
 *
 *  @param platformType 需要初始化的分享平台类型
 *  @param appInfo      需要初始化的分享平台应用信息
 */
typedef void(^SinaPaySDKConfigurationHandler) (SinaPaySDKPaymentTypeCode platformType, NSMutableDictionary *appInfo);

/**
 SDK回调处理器
 
 @param platformType 导入的原平台SDK的平台类型
 @param response 支付响应结果的返回
 */
typedef void(^SinaPaySDKImportHandler) (SinaPaySDKPaymentTypeCode platformType,id response);

@interface SinaPaySDK : NSObject
@property (nonatomic,copy) void (^responseBlock) (id);
@property (nonatomic,strong) NSMutableDictionary *appInfo;

+ (instancetype)sharedInstance;
+ (void)registerActivePlatforms:(NSArray*)arr
                onConfiguration:(SinaPaySDKConfigurationHandler)configurationHandler;
+(BOOL)handleOpenURL:(NSURL*)url;
+(void)payActionWithType :(SinaPaySDKPaymentTypeCode)payType withOrder:(SinaPayOrder *)sinaPayOrder callback:(SinaPaySDKImportHandler)importHandler;

@end
