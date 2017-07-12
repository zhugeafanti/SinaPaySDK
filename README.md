<span id="_Toc390677553" class="anchor"><span id="_Toc394312149"
class="anchor"></span></span>

<span id="_Toc285549493" class="anchor"><span id="_Toc382574351"
class="anchor"><span id="_Toc382574725"
class="anchor"></span></span></span> **文件版本：V2.0 **

<span id="_Toc285549495" class="anchor"><span id="_Toc382574353"
class="anchor"><span id="_Toc382574727"
class="anchor"></span></span></span>**发布范围：支付插件接入商户、技术支持**

**北京新浪技术(中国)有限公司 **

<span id="_Toc285549498" class="anchor"><span id="_Toc382574356"
class="anchor"><span id="_Toc382574730"
class="anchor"></span></span></span>**发布日期：2016-12-07**

**版本控制信息**

| 版本 | 日期       | 拟稿和修改 | 说明              |
|:------:|:------------:|:------------:|-------------------|
| 1.0  | 2016-12-07 | 赵亮       | 新建文档          |
| 2.0  | 2017-07-06 | 刘瑞刚     | SDK架构、接口更新 |
|      |            |            |                   |
|      |            |            |                   |
|      |            |            |                   |
|      |            |            |                   |
|      |            |            |                   |

目录
====

[*1* *文档说明* 4](#文档说明)

[*1.1* *功能描述* 4](#功能描述)

[*1.2* *阅读对象* 4](#阅读对象)

[*1.3* *业务术语* 4](#业务术语)

[*2* *支付插件集成说明* 4](#支付插件集成说明)

[*2.1* *集成SDK* 4](#集成sdk)

[*2.2* *开发包导入* 5](#开发包导入)

[*2.3* *接口调用方式* 5](#接口调用方式)

[*2.4* *请求参数说明* 7](#请求参数说明)

[*2.5* *同步通知参数说明* 8](#同步通知参数说明)

[*2.6* *服务器支付结果回调参数说明* 8](#服务器支付结果回调参数说明)

[*2.7* *插件集成的具体步骤* 8](#插件集成的具体步骤)

[*2.7.1* *增加URL Types* 8](#增加url-types)

[*2.7.2* *更改代理类* 8](#更改代理类)

[*2.7.3* *新浪支付注册* 9](#新浪支付注册)

[*2.7.4* *组装请求信息。* 9](#组装请求信息)

[*3* *附录* 10](#附录)

[*3.1* *响应码说明* 10](#响应码说明)

1.  文档说明
    ========

    1.  功能描述
        --------

新浪支付中心支付SDK2.0版主要用来向第三方应用程序提供便捷，安全，可靠的支付服务。本文主要描述了支付接口的使用方法，供合作伙伴的开发者接入使用

阅读对象
--------

本文档面向具有一定IOS客户端开发能力，了解IOS客户端的开发和管理人员。

业务术语
--------

| **术语** | **解释**                                                                                                                             |
|----------|--------------------------------------------------------------------------------------------------------------------------------------|
| 请求     | 手机客户端以字符串的形式把需要传输的数据发送给接收方的过程                                                                           |
| 通知     | 服务器异步通知，新浪支付中心支付平台根据得到的数据处理完成后，支付平台主动发送通知给商户的网站，同时携带处理完成的结果信息反馈给商户 |
| 返回     | 第三方支付返回客户端状态码                                                                                                           |

1.  支付插件集成说明
    ================

    1.  集成SDK
        -------

IOS开发包基于IOS SDK 10.1.1开发，支持IOS 8.0及以上版本系统。

IOS版开发包共包括核心插件framework包,和集成了新浪支付的demo示例代码组成

**开发包结构如下：**

| SinaPaySDKSpec/SinaPaySDK.framework | 新浪支付中心支付核心SDK   |
|-------------------------------------|---------------------------|
| SinaPaySDKSpec/SinaPaySDK.podspec   | cocoapods规范描述文件     |
| SinaPaySDKSpec/libcrypto.a          | 加解密.a文件              |
| SinaPaySDKSpec/libssl.a             | libssl.a                  |
| SinaPaySDKDemo                      | 集成新浪支付SDK的使用demo |

开发包导入
----------

IOS版本开发包导入

方法1：

**第一步：**导入相关资源目录SinaPaySDKSpec。

1.  将对应的SinaPaySDKSpec资源目录拷贝到项目所在的目录下。

>![pic1.png](http://upload-images.jianshu.io/upload_images/2693519-04c824afbf7df97f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

**第二步**：修改项目Podfile文件，添加新浪支付依赖.

1.  编辑Podfile如：

```
pod 'SinaPaySDK',:path=>git;'../SinaPaySDKSpec/'。
```
（SinaPaySDKSpec与项目目录平级可如此引用，注意路径，可自行调整）
>
> ![pic2.png](http://upload-images.jianshu.io/upload_images/2693519-7e21ebbc3cc48144.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

方法2：

1、编辑Podfile文件：

```
pod 'SinaPaySDK',:git=>git;'https://github.com/zhugeafanti/SinaPaySDK.git'
```

>![pic3.png](http://upload-images.jianshu.io/upload_images/2693519-8bc2423caadd8c23.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

接口调用方式
------------

IOS平台上的支付中心支付SDK接口如下表：

| **接口名称**                              | **接口描述**        |
|-------------------------------------------|---------------------|
| registerActivePlatforms: onConfiguration: | 新浪支付SDK注册接口 |

| **方法原型** | + (void)registerActivePlatforms:(NSArray\*)arr onConfiguration:(SinaPaySDKConfigurationHandler)configurationHandler; |
|--------------|----------------------------------------------------------------------------------------------------------------------|
| **方法功能** | 新浪支付SDK注册                                                                                                      |
| **方法参数** | /\*\*                                                                                                                                                                                                                               <br>新浪支付SDK注册接口<br> @param arr 使用的支付平台集合，如:@\[@(SinaPaySDKPaymentTypeAlipay),@(SinaPaySDKPaymentTypeWechatPay)\] <br/><br/>@param configurationHandler 配置回调处理，在此方法中根据设置的platformType来填充应用配置信息 <br>\*/                                                                                                                   |
| **返回值**   | 无                                                                                                                   |

| **接口名称**   | **接口描述**            |
|----------------|-------------------------|
| handleOpenURL: | 新浪支付URL统一处理接口 |

| **方法原型** | +(BOOL)handleOpenURL:(NSURL\*)url                                    |
|------------|----------------------------------------------------------------------|
| **方法功能** | URL统一处理接口                                                      |
| **方法参数** | /\*\* <br>URL统一处理接口，iOS app中AppDelegate ：<br>                - (BOOL)application:openURL:sourceApplication:annotation:   <br> - (BOOL)application: openURL: options: // NOTE: 9.0以后使用新API接口中调用。<br><br>@param url NSURL类型对象<br><br> @return 返回bool类型YES or NO <br>\*/                                                                                                                                         |
| **返回值**   | BOOL类型                                                             |

| **接口名称**                            | **接口描述**             |
|-----------------------------------------|--------------------------|
| payActionWithType: withOrder: callback: | 新浪支付发起支付行为接口 |

| **方法原型** | +(void)payActionWithType :(SinaPaySDKPaymentTypeCode)payType withOrder:(SinaPayOrder \*)sinaPayOrder callback:(SinaPaySDKImportHandler)importHandler; |
|--------------|-------------------------------------------------------------------------------------------------------------------------------------------------------|
| **方法功能** | 提供给商户发起支付行为功能                                                                                                                            |
| **方法参数** | /\*\*<br>新浪支付 发起支付行为接口<br><br>@param payType 支付类型<br><br>@param sinaPayOrder 新浪支付 订单消息结构<br><br> @param sinaPayOrder 新浪支付 订单消息结构<br><br> @param importHandler 支付结果回调处理block <br>\*/<br> 注：<br>1、payType参数为SinaPaySDKPaymentTypeCode枚举类型，参见SinaPaySDK.h。<br> 2、sinaPayOrder参数为SinaPayOrder类实例，初始化示例如下: <br><font color=red> SinaPayOrder \*orderModel = \[SinaPayOrder getModel\];  <br>orderModel.corpType = @"11";     <br>orderModel.businessId = @"14561929961102029";                  <br>orderModel.orderNum = \[@"201606161653" stringByAppendingString:\[NSString stringWithFormat:@"%d",arc4random()\]\];  <br>orderModel.appName = @"超级玛丽"; <br>orderModel.orderAmt = \[NSNumber numberWithFloat:0.01\];  <br>orderModel.key=@"03d3180858f08b4ae6a09460f4dfd0cf";<br>orderModel.paymentTag=@2;</font> <br>3、importHandler参数为block类型，支付回调处理。 <br>请参考2.4请求参数说明，查看各个字段的含义和规格。                                                                                                         |
| **返回值**   | 无                                                                                                                                                    |

请求参数说明
------------

| 参数             | 参数说明                                                | 参数长度             | 参数构成                     | 是否必须传 | 是否可为空 | 备注、示例                                  |
|------------------|---------------------------------------------------------|----------------------|------------------------------|------------|------------|---------------------------------------------|
| corpType         | 业务类型                                                | 以实际长度为准       | 以实际规则为准               | 是         | 否         | 参加demo                                    |
| appName          | 应用的产品名称                                          | 最长40位长度（0~40） | 数字，字母，特殊符号，或组合 | 是         | 否         | “商户测试”                                  |
| appType          | 应用的产品类别                                          | （0~20）             | 数字，字母，特殊符号，或组合 | 是         | 否         | “游戏”                                      |
| orderNum         | 商户订单号                                              | （0-32）             | 数字，字母，或组合           | 是         | 否         | “20150211”                                  |
| orderAmt         | 商户订单金额(**单位为元**)                              | （1-12）             | 数字                         | 是         | 否         | **银联支付最小金额为8分**                   |
| orderDescription | 商户订单描述                                            | （0-128）            | 数字，字母，特殊符号，或组合 | 否         | 否         | 中文最多40个                                |
| businessId       | 商户ID(注册应用信息分配的)                              | （0-24）             | 数字                         | 是         | 否         | “623”                                       |
| paymentTag       | 支付方式,有支付宝，微信，支付方式(不同支付方式传不同值) | （0-20）             | 支付宝：“2” 微信：“3”                     | 是         | 否         | 不同支付方式传不同的值，如：2标示支付宝支付 |
| key              | 商户key                                                 | 以实际长度为准       | 以实际规则为准               | 是         | 否         | 以实际规则为准                              |

注意：1. key和businessId是我方运营提供的

2. orderNum（订单号）每次发送支付请求，都要更换不同的订单号

3. orderAmt订单金额的单位为**元**，**请一定注意**！

4. 支付方式和运营商的选择请根据不同的方式和运营商传相对应的值

同步通知参数说明
----------------

> **目前，IOS版本没有封装同步通知参数，支付宝和微信还是用本来的返回码和错误信息。具体的参数规则见3.1响应码说明。**

服务器支付结果回调参数说明 
---------------------------

服务器回调方法与规则与浏览器支付

1.  插件集成的具体步骤
    ------------------

    1.  ### 增加URL Types

>![pic4.png](http://upload-images.jianshu.io/upload_images/2693519-fcaf0ac8334000b4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

上面的是支付宝的配置，其中URL
Schemes字段还是要和调起支付宝的appScheme字段相同否则支付成功返回的时候，可能调不起商户应用。

下面的是微信的配置，其中URL Scheme字段是在微信开放平台注册的appid字段。

### 更改代理类 

配置配置支付宝、微信客户端返回url处理方法。

**\#import &lt;SinaPaySDK/SinaPaySDK.h&gt;**

AppDelegate.m代理类处理了各种支付方式同步回调。相关代码如下：

```
- (BOOL)application:(UIApplication \*)application

openURL:(NSURL \*)url

sourceApplication:(NSString \*)sourceApplication

annotation:(id)annotation {

return \[SinaPaySDK handleOpenURL:url\];

}
```

// NOTE: 9.0以后使用新API接口

```
- (BOOL)application:(UIApplication \*)app openURL:(NSURL \*)url
options:(NSDictionary&lt;NSString\*, id&gt; \*)options

{

return \[SinaPaySDK handleOpenURL:url\];

}
```
详细请看demo中AppDelegate.m的代码。

### 新浪支付注册

**\#import &lt;SinaPaySDK/SinaPaySDK.h&gt;**

在使用SDK时，需要进行注册，注册的代码如下：

```
\[SinaPaySDK
registerActivePlatforms:@\[@(SinaPaySDKPaymentTypeAlipay),@(SinaPaySDKPaymentTypeWechatPay)\]
onConfiguration:^(SinaPaySDKPaymentTypeCode platformType,
NSMutableDictionary \*appInfo) {

switch (platformType){

case SinaPaySDKPaymentTypeAlipay:{

\[appInfo SinaPaySDKSetupAliPayByAppId:@"" appScheme:@"alisdkdemo"\];

}break;

case SinaPaySDKPaymentTypeWechatPay:{

\[appInfo SinaPaySDKSetupWeChatByAppId:@"wxfe0fd15b9c796981"
appDesc:@"SinaPay Demo 2.0"\];

}break;

}

}\];
```

其中：需微信开放平台注册的appid字段，阿里支付需URL Schemes字段scheme。

### 组装请求信息。

**\#import &lt;SinaPaySDK/SinaPaySDK.h&gt;**

相关代码如下：

```
SinaPayOrder \*orderModel = \[SinaPayOrder getModel\];

orderModel.corpType = @"11";

orderModel.businessId = @"14561929961102029";

orderModel.orderNum = \[@"201606161653"
stringByAppendingString:\[NSString
stringWithFormat:@"%d",arc4random()\]\];

orderModel.appName = @"超级玛丽";

orderModel.orderAmt = \[NSNumber numberWithFloat:0.01\];

orderModel.key=@"03d3180858f08b4ae6a09460f4dfd0cf";

<orderModel.paymentTag=@2>;

\[SinaPaySDK payActionWithType:SinaPaySDKPaymentTypeAlipay
withOrder:orderModel callback:^(SinaPaySDKPaymentTypeCode
platformType,id response) {

}\];
```

1.  附录
    ====

    1.  响应码说明
        ----------

| **支付宝支付结果** |**错误描述**|
|--------------------|---|
| 9000               |订单支付成功|
| 8000               |正在处理中|
| 4000               |订单支付失败|
| 5000               |重复请求|
| 6001               |用户中途取消|
| 6002               |网络连接出错|
| **微信支付结果**   |**错误描述**|
| 0                  |支付成功|
| -1                 |支付错误|
| -2                 |用户取消|


