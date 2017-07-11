//
//  NSMutableDictionary+SinaPaySDKInit.h
//  SinaPaySDK
//
//  Created by ruigang on 2017/7/5.
//  Copyright © 2017年 ruigang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSMutableDictionary (SinaPaySDKInit)
/**
 *  设置微信应用信息
 *
 *  @param appId      应用标识
 *  @param desc  描述
 */
- (void)SinaPaySDKSetupWeChatByAppId:(NSString *)appId
                     appDesc:(NSString *)desc;

/**
 设置支付宝应用信息
 
 @param appId 应用标识
 @param scheme 工程中URL Scheme配置信息
 */
- (void)SinaPaySDKSetupAliPayByAppId:(NSString *)appId
                           appScheme:(NSString*)scheme;
@end
