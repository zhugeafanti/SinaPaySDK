//
//  SinaPayOrder.h
//  SinaPaySDK
//
//  Created by ruigang on 2017/7/3.
//  Copyright © 2017年 ruigang. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SinaPayOrder : NSObject
@property(nonatomic,copy) NSString *corpType;
@property(nonatomic,copy) NSString *businessId;
@property(nonatomic,copy) NSString *orderNum;
@property(nonatomic,copy) NSString *appName;
@property(nonatomic,copy) NSNumber *orderAmt;
@property(nonatomic,copy) NSString *key;
@property(nonatomic,copy) NSString *sign;
@property(nonatomic,strong) NSNumber *paymentTag;

+(SinaPayOrder *)getModel;
-(NSMutableDictionary*)changeModel2Dic;

@end
