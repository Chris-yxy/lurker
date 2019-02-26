/*
 * @author soloicesky
 * @description
 */


#ifndef _EMVTRANSFLOW_H_
#define _EMVTRANSFLOW_H_

#include <stdlib.h>
#include <stdint.h>

#ifdef WIN32

#define KERNEL_EXPORTS

#ifdef KERNEL_EXPORTS
#define EMVPBOC_API __declspec(dllexport)
#else
#define EMVPBOC_API __declspec(dllimport)
#endif

#else

#define EMVPBOC_API

#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define  QUICS

#define TC_LEN								3
#define EXTC_LEN							5
#define IFD_LEN								8
#define MERCHANT_CATEGORY_CODE_LEN			2
#define MID_LEN								15
#define TID_LEN								8
#define MERCHANT_NAME_LOCATION				80
#define ACQID_LEN							12


#define ACTION_TRANSACTION  0x00 //标准借贷记交易
#define ACTION_INQUERY	 0x01   //查询交易
#define ACTION_ECTRANSACTION  0x02 //标准借贷记小额(电子现金)


#define ENTRYMODE_INSERT			0x05
#define ENTRYMODE_SWIPT				0x02
#define ENTRYMODE_WAVE				0x09
#define ENTRYMODE_MANUAL			0x10
#define ENTRYMODE_MOBILE			0x18
#define ENTRYMODE_FALLBACK			0x92


#define SUPPORT_QPBOC 1 //是否支持QPBOC

/**
	apdu 收发接口
	@param channelNo[in] 卡槽编号
	@param capdu[in] 终端发给卡的apdu
	@param capdulen[in] 终端发给卡的apdu长度
	@param rapdu[out] 卡片发给终端的apdu
	@param capdulen[Out] 卡片发给终端的apdu长度
	@retval 0 交互成功，其他交互失败
**/
typedef int (*dataTransmitCallback)(uint8_t channelNo,uint8_t * capdu, int capdulen,
									uint8_t * rapdu, int *rapduLen);

typedef int (*inputOnlinePIN)(void);

typedef int (*showID)();

typedef uint8_t (*IsIssuerCARevoked)(unsigned char *rid, unsigned char index, unsigned char *serial);

typedef uint8_t (*IsCardInBlackList)(char *pan, unsigned char panSeq);

typedef int(*PromptEnterPIN)(void);

typedef int(*ShowPINCount)(unsigned char count);

typedef int (*GetUnpreditableNumber)(unsigned char *un, int wantedLen);

typedef int (*GetRandNumBetween)(int low, int hight);

typedef int (*Pci_PerformOfflineEncryptedPin)(void *ca,PromptEnterPIN promptEnterPin, ShowPINCount showPinCount);

typedef int (*Pci_PerformOfflinePlainTextPin)(PromptEnterPIN promptEnterPin, ShowPINCount showPinCount);

typedef int (*inputPIN)(char *PIN,uint8_t PINType,uint8_t remaindTimes,int bFirstTrial);

typedef int  (*Verfify_offline_plaintext_pin)(int nSlot);

typedef int  (*Verfify_offline_encipher_pin)(int nSlot, unsigned char *modules, int mudulesLen,
					unsigned char *exponent, unsigned char expLen);


enum {
	OFFLINE_PIN, // 脱机PIN
	OFFLINE_PLAINTEXT_PIN, //脱机明文PIN
	OFFLINE_ENCIPHERED_PIN,	//脱机密文PIN
	ONLINE_ENCIPHERED_PIN //联机密文PIN
};

typedef struct _tag_list_
{
	int *tagSet;
	int size;
}TagList;

#if 0
typedef struct _callback_entry_{
	dataTransmitCallback transmit;
	inputOnlinePIN getOnlinePIN;
	showID showCardholderID;
	IsIssuerCARevoked IsCaRevoked;
	IsCardInBlackList IsInBlackList;
	PromptEnterPIN promtEnterPin;
	ShowPINCount showPinCount;
	GetUnpreditableNumber getUn;
	GetRandNumBetween getRn;
	Pci_PerformOfflineEncryptedPin performOlEPin;
	Pci_PerformOfflinePlainTextPin performOlPPin;
	inputPIN enterPin;
}CBEntry;
#else

typedef struct _callback_entry_{
	dataTransmitCallback transmit;
	inputPIN getPIN;
	showID showCardholderID;
	IsIssuerCARevoked IsCaRevoked;
	IsCardInBlackList IsInBlackList;
	PromptEnterPIN promptEnterPin;
	ShowPINCount showPinCount;
	GetUnpreditableNumber getUn;
	GetRandNumBetween getRn;
	Verfify_offline_plaintext_pin verifyOfflinePlaintextPin;
	Verfify_offline_encipher_pin verifyOfflineEnciperedPin;
}CBEntry;

#endif
#define CHANNEL_CONTACTIC			0x00 //接触式IC卡卡槽
#define CHANNEL_PICC				0x01 //非接触IC卡接口

#define EMV_PBOC					0x00
#define QPBOC						0x01

/*************************************************************************/
/*		ERROR CODE DEFINATION											 */
/*************************************************************************/
#define ACTION_NOT_SUPPORT				-100

#define ERR_INVALID_PARAMETER			-1
#define ERR_PARSE_TAG					-2
#define ERR_PARSE_LENGTH				-3
#define ERR_MEMALLOC_VALUE				-4
#define ERR_SAVEDATA_FAIL				-5

#define ERR_CONVERT_TYPE				-6
#define ERR_TAG_MISSING					-7
#define ERR_MEM_OVERFLOW				-8
#define ERR_PARSE_VALUE					-9
#define ERR_CAPK_NOT_FOUND				-10

#define ERR_RECOVER_ISSUER_PK			-11
#define ERR_INVALID_ISSUER_PKCERT		-12
#define ERR_RECOVER_ICC_PK				-13
#define ERR_INVALID_ICC_PKCERT			-14
#define ERR_INVALID_ICC_DATA			-15

#define ERR_SDA_FAILED					-16
#define ERR_INTERNAL_AUTH_FAILED		-17
#define ERR_DDA_FAILED					-18
#define ERR_RECOVER_PIN_PK				-19
#define ERR_TLVOBJ_NOT_FOUND			-20

#define ERR_TAG_NOT_IN_DICT				-21
#define ERR_CARD_ACTION_HIGHER_THAN_TERM	-22
#define ERR_SERVICE_NOT_ALLOWED			-23
#define ERR_OFFLINE_DECLINED			-24
#define ERR_GEN_PINBLOCK				-25

#define ERR_ENTER_PIN_CANCEL			-26
#define ERR_ISSUER_AUTH_FAILED			-27
#define ERR_INVALID_SCRIPT_DATA			-28
#define ERR_NO_APP						-29
#define ERR_READ_LASTRECORD_FAILED		-30
#define ERR_INPUTAMTFIRST				-31
#define ERR_TRY_OTHERINTERFACE			-32

#define ERR_WRONGAPDU_RSP				-33
#define ERR_TAG_DUPLECATED				-34
#define ERR_CA_REVOKED					-35
#define ERR_CARD_IN_BLACKLIST			-36
#define ERR_TERMINATED					-37
#define ERR_APP_EXPIRED					-38
#define ERR_OPEN_FILE_FAILED			-39
#define ERR_WRITE_FILE_FAILED			-40
#define ERR_READ_FILE_FAILED			-41
#define ERR_SEEK_FILE_FAILED			-42
#define ERR_CHECKSUM_NOT_MATCH			-43

#define ERR_TRANSMIT_DATA				-200
#define ERR_INVALIDED_ICCDATA			-201
#define ERR_APP_BLOCKED 				-202
#define ERR_AUTH_FAILED 				-203
#define ERR_REF_DATA_INVALIDATED		-204
#define ERR_CON_NOT_SATISFIED			-205
#define ERR_CARD_BLOCKED				-206
#define ERR_FILE_NOT_FOUND				-207
#define ERR_RECORD_NOT_FOUND			-208
#define ERR_DATABBJ_NOT_FOUND			-209
#define ERR_PIN_RETRY_LIMIT 			-210
#define ERR_PIN_TRY_REMAIN				-211
#define ERR_AUTH_METHOD_BLOCK			-212
#define ERR_NOT_RECONISED				-213
#define ERR_SEE_PHONE                   -214


#define INFO_NO_CONFIRMATION			2
#define INFO_NEED_CONFIRMATION			3
#define INFO_TRY_NEXT_AID				4


#define INFO_OFFLINE_DATA_AUTH_NOT_PERFORM	10
#define INFO_OFFLINE_DATA_AUTH_FAILED		11

#define INFO_DECLINED						12
#define INFO_APPROVED						13
#define INFO_ONLINEFAILED					14

#define INFO_GOOD_OFFINE_APPROVED			168
#define INFO_GO_ONLINE						169
#define INFO_GO_ONLINE_DUE_TO_EXPIRED		170


#define STATUS_FAILED					 200


#define ONLINE_FAILED			0
#define ONLINE_APPROVED			1
#define ONLINE_DECLINED			2
#define ONLINE_REFFERAL			3

#define INFO_ONLY_P1_P2_AMT		20

//cardholder verification actions
#define ACTION_SKIP						0x01
#define ACTION_OFFLINE_PLAINTEXT_PIN	0x02
#define ACTION_OFFLINE_ENCIPHERED_PIN	0x04
#define ACTION_ONLINE_ENCIPHERED_PIN	0x08
#define ACTION_SIGNATURE				0x10
#define ACTION_SHOW_CARDHOLD_ID			0x20



/*^=======================================================================^*/


/*************************************************************************/
/*		TRANSACTION TYPE DEFINATION										 */
/*************************************************************************/

#define TRANS_TYPE_CASH            0x01    //交易类型(现金)
#define TRANS_TYPE_GOODS           0x02    //交易类型(购物)
#define TRANS_TYPE_SERVICE         0x04    //交易类型(服务)
#define TRANS_TYPE_CASHBACK        0x08    //交易类型(反现)
#define TRANS_TYPE_INQUIRY         0x10    //交易类型(查询)
#define TRANS_TYPE_PAYMENT         0x20    //交易类型(支付)
#define TRANS_TYPE_ADMINISTRATIVE  0x40    //交易类型(管理)
#define TRANS_TYPE_TRANSFER        0x80    //交易类型(转账)



/*^=======================================================================^*/

/*************************************************************************/
/*		KERNEL TYPES DEFINATION											 */
/*************************************************************************/

//FOR AIDS
#define WHOLE_MATCH_STRATEGY			0x00
#define PARTIAL_MATCH_STRATEGY			0x01


#define MAX_AID_COUNT					1
#define MAX_CANDIDATE_AID_COUNT 		6
#define MAX_APP_LABEL_LENGTH			16
#define MAX_AID_LENGTH					16
#define APP_VERSION_LEN					2
#define MAX_ARRAY_LEN					128
#define TAC_SIZE						5
#define TAC_TRMD_MAXLEN					8

typedef struct _var_uint8_t_array_
{
	uint8_t value[MAX_ARRAY_LEN];
	uint16_t len;
}VarByteArray;

typedef struct _var_uint8_t_array_ex_
{
	uint8_t * value;
	uint16_t len;
}VarByteArrayEx;



typedef struct _aid_{
	char	appLabel[MAX_APP_LABEL_LENGTH + 1];  //application label
	char	appPreferLabel[MAX_APP_LABEL_LENGTH + 1]; //application prefer name;
	uint8_t	AID[MAX_AID_LENGTH + 1];			//application identity
	uint8_t	AIDLen; 							//aid length
	uint8_t	matchStrategy;						//full match or partial match
	int forceConfirm;						//force cardholder to confirm the application
	uint8_t	appVersion[APP_VERSION_LEN]; 						//application version
	uint8_t	priorityIndicator;					//application selection priority indicator
	uint8_t	defaultDDOL[128];						//default DDOL
	uint8_t	defaultTDOL[128];						//default TDOL
	uint8_t	maxTargetPercentage;				//max target percentage
	int sprtRandomTransSelction;
	uint8_t	targetPercentage;
	int	threshold;
	int sprtVelocityChecking;
	uint8_t    bDTACExist;
	uint8_t	defaultTAC[TAC_SIZE];
	uint8_t    bOTACExist;
	uint8_t	onlineTAC[TAC_SIZE];
	uint8_t    bDETACExist;
	uint8_t	denialTAC[TAC_SIZE];
	int	floorLimit;
	int onlinePINSuprt;
	int	ECTransLimit;
	int	CLofflineFloorLimit;
	int	CLTransLimit;
	int   CLCVMLimit;
	VarByteArray	CVM;
	uint8_t	issuerCodeTableIndex;
	VarByteArray	issuerData;
//new add 0701
	char acqId[ACQID_LEN+1];
	uint8_t MCC[MERCHANT_CATEGORY_CODE_LEN];
	char MID[MID_LEN+1];
	char TID[TID_LEN+1];
	char MNL[MERCHANT_NAME_LOCATION+1];
	uint8_t TCC[2];
	uint8_t TCE;
	uint8_t TRCC[2];
	uint8_t TRCE;
	uint8_t TRMD[TAC_TRMD_MAXLEN+1];
//end add

}Aid;

typedef struct _aid_list_{
	Aid configAid[MAX_AID_COUNT];
	uint16_t count;
}AidList;

typedef struct _candidate_aid_list__{
	Aid canAid[MAX_CANDIDATE_AID_COUNT];
	uint16_t count;
	uint16_t selectedAidIndex;
}CandidateAidList;

#define DATE_LEN			3
#define TIME_LEN			3
#define COUNTRYCODE_LEN		4
#define CURRENCYCODE_LEN	4
#define MERCHANT_NAME_LEN	20

typedef struct _log_record_
{
	char transDate[DATE_LEN + 1];
	char transTime[TIME_LEN + 1];
	char authAmt[12 + 1];
	char otherAmt[12 + 1];
	char countryCode[COUNTRYCODE_LEN + 1];
	char currencyCode[CURRENCYCODE_LEN + 1];
	char merchantName[MERCHANT_NAME_LEN + 1];
	int transType;
	int atc;
	unsigned char p1;
	unsigned char p2;
}LogRecord;

/*****                FOR CA  	*****************/
#define RID_LEN					5
#define CA_CHECKSUM_LEN			20
#define MAX_CA_NUM				1
#define SM_POINT_LEN			80
#define USER_ID_LEN				80

typedef struct _rsa_ca_{
	uint8_t	caModules[248];
	uint8_t	caModulesLen;
	uint8_t	caPKExponent[3];
	uint8_t	caPKExponentLen;
	uint8_t	caCheckSum[CA_CHECKSUM_LEN];
	uint8_t	caCheckSumLen;
}RSA_CA;

typedef struct _sm_ca_{
	char    userId[USER_ID_LEN+1];
	int		idLen;
	unsigned short ENTL;
	uint8_t	x[SM_POINT_LEN];
	uint8_t	xLen;
	uint8_t 	y[SM_POINT_LEN];
	uint8_t	yLen;
}SM_CA;

//typedef struct _ca_public_key_{
//	uint8_t	RID[RID_LEN];
//	uint8_t 	Index;
//	uint8_t	validDate[4];
//	uint8_t	hashAlgorithmIndicator;
//	uint8_t	caAlgorithmInicator;
//	uint8_t	caModules[248];
//	uint8_t	caModulesLen;
//	uint8_t	caPKExponent[3];
//	uint8_t	caPKExponentLen;
//	uint8_t	caCheckSum[CA_CHECKSUM_LEN];
//	uint8_t	caCheckSumLen;
//}CAPublicKey;
//#define CA_TYPE_RSA		0x00
//#define CA_TYPE_SM		0x01
#define CA_TYPE_DEFAULT			0x00
#define CA_TYPE_RSA				0x01
#define CA_TYPE_ECCSHA256		0x02
#define CA_TYPE_ECCSHA512		0x03
#define CA_TYPE_SM				0x04


typedef struct _ca_public_key_{
	uint8_t 	ca_type;
	uint8_t	RID[RID_LEN];
	uint8_t 	Index;
	uint8_t	validDate[4];
	uint8_t	hashAlgorithmIndicator;
	uint8_t	caAlgorithmInicator;

	union _capk_{
		RSA_CA rsa_ca;
		SM_CA sm_ca;
	}capk;

	uint8_t	caCheckSum[CA_CHECKSUM_LEN];
	uint8_t	caCheckSumLen;
}CAPublicKey;

typedef struct _ca_repo_{
	CAPublicKey CAPKList[MAX_CA_NUM];
	uint8_t	CAPKCount;
}CARepo;



typedef struct _kernel_config_param_{
	uint8_t	terminalType;	  //specify the terminal type
	int bSupportPSE;	  //does terminal support pse selection or not '1' for yes, '0' for no
	int bSupportCardHolderConfirm; //does terminal support cardholder confirmation? '1' for yes, '0' for no
	uint8_t	TC[TC_LEN]; 		// terminal capability
	uint8_t	exTC[EXTC_LEN]; 	//extend terminal capability
	int alwaysPerformTRM; //always perform terminal risk management or not
	uint8_t termCountryCode[2];
	uint8_t CurrencyCode[2];
	uint8_t termTransCapability[4];
	uint8_t bStatusCheck;	 //终端是否支持状态检查
	uint8_t bSupportOnline; //终端是否支持联机
	uint8_t bSupportBatchCapture; //知否支持批记录捕获
	int bForceOnline;//强制联机
	char IFD[IFD_LEN + 1];
	int bDenialTAC;//拒绝TAC
	int bOnlineTAC;//联机TAC
	int bDefaultTAC;//默认TAC
	int bDefaultTDOL;//支持默认TDOL
	uint8_t MerchantCategoryCode[MERCHANT_CATEGORY_CODE_LEN];
	char Mid[MID_LEN+1];
	char Tid[TID_LEN+1];
	char MerchantNameLocation[MERCHANT_NAME_LOCATION+1];
	uint8_t TransType;
	char AcqId[ACQID_LEN + 1];
//    uint8_t bSupportSM; //是否支持国密
}KernelConfigParam;


typedef struct _host_data_
{
	unsigned char onlineResult;
	VarByteArrayEx responseCode;
	VarByteArrayEx issuerAuthCode;
	VarByteArrayEx issuerAuthData;
	VarByteArrayEx issuerScripts;
}HostData;

/*^=======================================================================^*/

enum{
	ENTER_PIN_OK = 0,
	ENTER_PIN_CANCEL = -2006,
	ENTER_PIN_BYPASS = -2007,
	ENTER_PIN_TIMEOUT = -2008
};

extern unsigned char channel;
extern unsigned char KernelType;


/*^=======================================================================^*/
/*************************************************************************/
/*		EXPORT APIS DEFINATIONS 										 */
/*************************************************************************/

//EMVPBOC_API void TransLib_SetupApduTransmitMethod(dataTransmitCallback transmitCB);
/**
	预处理
	@param amount[IN] 交易金额分为单位如“1”表示1分
	@retval 0 成功，其它失败
**/
int TransFlow_Pre_Process(char *amount);

/**
	建立候选列表
	@param channel[IN] 卡槽通道
	@retval ERR_NO_APP 无应用，INFO_NO_CONFIRMATION 无需持卡人选择确认，INFO_NEED_CONFIRMATION 需要持卡人选择确认
**/
EMVPBOC_API int TransFlow_BuildCandidateAidList(unsigned char channel);
/**
	是否需要持卡人确认
	@param none
	@retval ERR_NO_APP 无应用，INFO_NO_CONFIRMATION 无需持卡人选择确认，INFO_NEED_CONFIRMATION 需要持卡人选择确认
**/
EMVPBOC_API int TransFlow_NeedCardholderConfirmation(void);
/**
	最终选择
	@param selectedIndex 选择的候选列表中的应用索引
	@retval ERR_TRANSMIT_DATA apdu收发失败 INFO_TRY_NEXT_AID 请选择下一个aid ERR_NO_APP无应用 0 成功
**/
EMVPBOC_API int TransFlow_FinalSelection(uint16_t selectedIndex);
/**
	获取候选列表
	@param none
	@retval CandidateAidList 建立的候选列表
**/
EMVPBOC_API CandidateAidList *TransFlow_GetCandidateAidList(void);
/**
	获取处理选项
	@param none
	@retval ERR_NO_APP 无应用 INFO_TRY_NEXT_AID 选择下一个aid 0成功 其它异常终止
**/
EMVPBOC_API int TransFlow_GetProcessingOption(void);
/**
	读取应用数据
	@param none
	@retval 0 成功，ERR_READ_LASTRECORD_FAILED读取最后一条记录失败， 其它异常终止
**/
EMVPBOC_API int TransFlow_ReadApplicationData(void);

/**
	执行脱机数据认证
	@param none
	@retval 0 执行脱机认证成功，其它脱机数据认证失败
**/
EMVPBOC_API int TransFlow_OfflineDataAuthentication(void);
/**
	执行脱机数据认证
	@param none
	@retval 0 执行脱机认证成功，其它脱机数据认证失败
**/
EMVPBOC_API int TransFlow_OfflineDataAuthenticationEx(void);

/**
	执行处理限制
	@param none
	@retval none
**/
EMVPBOC_API void TransFlow_ProcessingRestrictions(void);
/**
	执行终端风险管理
	@param none
	@retval 0 成功，其它异常终止
**/
EMVPBOC_API int TransFlow_TermianRiskManage(void);

/**
	查询CVM方法行为
	@param none
	@retval 返回值是以掩码方式返回，如下：
	#define ACTION_SKIP						0x01 无需CVM，急跳过执行CVM
	#define ACTION_OFFLINE_PLAINTEXT_PIN	0x02 脱机明文PIN
	#define ACTION_OFFLINE_ENCIPHERED_PIN	0x04 脱机密文PIN
	#define ACTION_ONLINE_ENCIPHERED_PIN	0x08 联机密文PIN
	#define ACTION_SIGNATURE				0x10 签名
	#define ACTION_SHOW_CARDHOLD_ID			0x20 持卡人身份验证
**/
EMVPBOC_API int TransFlow_ConsultCVMAction(void);

/**
	执行持卡人认证行为
	@param actionCode CVM方法行为同TransFlow_ConsultCVMAction 的返回值
	@param getPinRet 执行CVM方法的结果
	@param PIN 存放脱机PIN的明文

**/
EMVPBOC_API int TransFlow_PerformCVMAction(int actionCode, int getPinRet, char * PIN);

/**
	持卡人验证
	@param none
	@retval 0 成功，其它失败
**/
EMVPBOC_API int TransFlow_CardholderVerification(void);

/**
	终端行为与卡片行为分析
	@param none
	@retval INFO_GO_ONLINE 联机处理，ERR_TRY_OTHERINTERFACE 尝试其它界面， ERR_OFFLINE_DECLINED脱机拒绝，
	INFO_GOOD_OFFINE_APPROVED 脱机批准，ERR_ENTER_PIN_CANCEL用户取消,其它异常终止
**/
EMVPBOC_API int TransFlow_TerminalAndCardActionAnylyze(void);

/**
	完成交易
	@param onlineResult 联机结果 ONLINE_FAILED 联机失败，ONLINE_APPROVED 联机批准，ONLINE_DECLINED 联机拒绝
						如果是返回联机参考需要调用者发起参考提示并回传结果(ONLINE_APPROVED 或者 ONLINE_DECLINED)
	@param responseCode 发卡行响应码
	@param issuerAuthCode 发卡行授权吗
	@param issuerAuthData 发卡行认证数据
	@param issuerScripts 发卡行脚本
	@retval INFO_APPROVED 交易批准， INFO_DECLINED 交易拒绝，	ERR_SERVICE_NOT_ALLOWED 服务不允许，其它异常终止
**/
EMVPBOC_API int TransFlow_CompleteTransaction(int onlineResult, VarByteArrayEx responseCode,
																VarByteArrayEx issuerAuthCode,
																VarByteArrayEx issuerAuthData,
																VarByteArrayEx issuerScripts);

/**
	读取交易日志
	@param recordNo 交易记录号
	@param logRecord 记录内容
	@retval ERR_RECORD_NOT_FOUND 无此交易记录，到此已读完
			0 交易记录读取成功
			其它异常终止
**/
EMVPBOC_API int TransFlow_ReadTransactionRecord(unsigned char recordNo, LogRecord *logRecord);

/**
	读取圈存日志
	@param recordNo 交易记录号
	@param logRecord 记录内容
	@retval ERR_RECORD_NOT_FOUND 无此交易记录，到此已读完
			0 交易记录读取成功
			其它异常终止
**/
EMVPBOC_API int TransFlow_ReadLoadRecord(unsigned char recordNo, LogRecord *logRecord);

/*****************************************************************************************************************************/

//获取交易过程中的TLV对象接口
	typedef struct _tlv_obj_{
		uint16_t	tag;
		uint16_t	length;
		uint8_t *	value;
	}TlvObj;

/**
	获取内核tag对象
	@param tag 标签
	@retval NULL 找不到tag对象，非空tag对象指针
**/
EMVPBOC_API TlvObj *getTlvObjRef(uint16_t tag);


/**
	组建TLV数据
	@param tlvMsg[out] 组建好的tlv数据
	@param tlvMsgLen[out] 组件好的tlv数据长度
	@param tagList[in] 需要组建的tag列表
	@retval 0 成功，其它失败
**/
EMVPBOC_API int buildConstructedTlv(uint8_t * tlvMsg, uint16_t *tlvMsgLen, TagList *tagList);

/**
	是否需要签名
	@param none
	@retval 1 需要签名，0不需要签名

**/
EMVPBOC_API int TransFlow_CheckIfNeedSignature(void);
/**
	解析tlv数据
	@param saveDataCallback[in] 保存TLV对象接口
	@param constructedData[in] tlv数据
	@param constructedDataLen[in] tlv数据长度
	@param objRepo[out] TLV对象存储的位置
**/
EMVPBOC_API int decodeAllConstructedTlvObj(void *saveDataCallback,uint8_t * constructedData,
								 int constructedDataLen, void *objRepo);

////////////////////////////////////////////////////////////////////////////////
//new API
/////////////////////////////////////////////////////////////////////////////////
/**
	交易初始化
	@param transSeqNo 交易序列号
	@param date 交易日期 YYMMDDHHMMSS
	@param tchannel 交易通道，接触通道或者非接触通道
	@retval  ERR_NO_APP 无应用，INFO_NO_CONFIRMATION 无需持卡人选择确认，INFO_NEED_CONFIRMATION 需要持卡人选择确认
**/
EMVPBOC_API int TransFlow_InitTransaction(int transSeqNo, char *date,uint8_t tchannel);

/**
	开始交易
	@param index 最终选择的应用索引
	@param amount 交易金额分为单位入“1”代表1分
	@param otherAmt 其它金额同amount
	@retval 0 成功，ERR_NO_APP 无应用，INFO_NO_CONFIRMATION 无需持卡人选择确认，INFO_NEED_CONFIRMATION 需要持卡人选择确认
			其它异常终止
**/
EMVPBOC_API int TransFlow_StartTransaction(uint8_t index, uint32_t amount, uint32_t otherAmt);

/**
	开始交易
	@param index 最终选择的应用索引
	@param amount 交易金额分为单位入“1”代表1分
	@param otherAmt 其它金额同amount
	@retval 0 成功，ERR_NO_APP 无应用，INFO_NO_CONFIRMATION 无需持卡人选择确认，INFO_NEED_CONFIRMATION 需要持卡人选择确认
			其它异常终止
**/
EMVPBOC_API int TransFlow_StartTransactionEx(uint8_t index, char *amount, char *otherAmt);

/**
	处理交易
	@param none
	@retval 0 成功， 其它异常终止
**/
EMVPBOC_API int TransFlow_ProcessTransaction(void);

/**
	处理交易
	@param none
	@retval 0 成功， 其它异常终止
**/
EMVPBOC_API int TransFlow_ProcessTransactionEx(void);

/**
	结束交易
	@param hostdata[in] 后台下发数据，其中包括联机结果，响应码， 授权码， 认证数据，脚本
	@retval INFO_APPROVED 交易批准， INFO_DECLINED 交易拒绝，	ERR_SERVICE_NOT_ALLOWED 服务不允许，其它异常终止
**/
EMVPBOC_API int TransFlow_EndTransaction(HostData *hostData);

/**
	设置是否需要发通知报文
	@param b 1需要发 0不需要发
	@retval none

**/
EMVPBOC_API void TransFlow_Set_b_gNeedAdvice(unsigned char b);

/**
	是否需要发通知报文
	@param none
	@retval 1 需要发 0 无需发
**/
EMVPBOC_API unsigned char TransFlow_IsNeedAdvice(void);

/**
	获取余额
	@param balance[out] 出参
	@retval 0 成功，其它失败
**/
EMVPBOC_API int TransFlow_GetBalance(char *balance);

/**
	初始化交易环境
	@param cbFunEntry[in] 回调函数集合入口
	@param path[in] 参数存储路径
	@retval none
**/
EMVPBOC_API void TransLib_InitEnv(CBEntry *cbFunEntry, char *path);

/**
	保存TLV对象到内核
	@param tag 标签
	@param len 长度
	@param value 值
	@param repo 数据仓库，如果为则默认保存到缺省仓库
	@retval 0 存储成功， 其它失败
**/
EMVPBOC_API int saveTermTlvObjEx(unsigned short tag, int len, uint8_t * value, void *repo);

EMVPBOC_API KernelConfigParam *getKernelConfig(void);

EMVPBOC_API void setKernelConfigParam(KernelConfigParam *config);

EMVPBOC_API CBEntry *GetCallbackFuncEntry(void);

EMVPBOC_API void TransLib_ClearTransLog(void);

EMVPBOC_API char *GetKernelVersion(void);

EMVPBOC_API void TransFlow_SetAction(unsigned char action);

EMVPBOC_API unsigned char TransFlow_GetAction(void);

EMVPBOC_API int TransFlow_IsECTransaction(void);

EMVPBOC_API unsigned char TransFlow_GetKernelType(void);

EMVPBOC_API void TransKernelClearAidList(void);

EMVPBOC_API int TransKernelAppendAid(Aid *aid);

EMVPBOC_API int TransKernelGetAid(Aid *aid, int index);

EMVPBOC_API void TransKernelClearCAPKList(void);

EMVPBOC_API int TransKernelAppendCapk(CAPublicKey *capk);

EMVPBOC_API int TransKernelGetCapk(CAPublicKey *capk, int index);

EMVPBOC_API unsigned char TransKernelIsAidInited(void);

EMVPBOC_API unsigned char TransKernelIsCapkInited(void);

EMVPBOC_API void KernelConfigSetTC(unsigned char *TC);

EMVPBOC_API void KernelConfigSetTerminalType(uint8_t	 terminalType);

EMVPBOC_API void KernelConfigSetSptrPSE(uint8_t bSupportPSE);

EMVPBOC_API void KernelConfigSetSptrCHDConfirm(uint8_t bSupportCardHolderConfirm);

EMVPBOC_API void KernelConfigSetEXTC(unsigned char *exTC);

EMVPBOC_API void KernelConfigSetCountryCode(unsigned char *code);

EMVPBOC_API void KernelConfigSetCurrencyCode(unsigned char *code);

EMVPBOC_API void KernelConfigSetStatusCheck(unsigned char option);

EMVPBOC_API void KernelConfigSetOnline(unsigned char option);

EMVPBOC_API void KernelConfigSetBatchCapture(unsigned char option);

EMVPBOC_API void KernelConfigSetForceOnline(unsigned char option);

EMVPBOC_API void KernelConfigSetDenialTACSwitch(unsigned char option);

EMVPBOC_API void KernelConfigSetOnlineTACSwitch(unsigned char option);

EMVPBOC_API void KernelConfigSetDefaultTACSwitch(unsigned char option);

EMVPBOC_API void KernelConfigSetTransactionCapability(unsigned char *tc);

EMVPBOC_API void KernelConfigSetIFD(unsigned char *ifd);

EMVPBOC_API void KernelConfigSetMerchantCategoryCode(unsigned char *mcc);

EMVPBOC_API void KernelConfigSetMid(char *mid);

EMVPBOC_API void KernelConfigSetTid(char *tid);

EMVPBOC_API void KernelConfigSetTransType(unsigned char transType);

EMVPBOC_API void KernelConfigSetAcquirerId(char *acqid);

EMVPBOC_API int TransKernelIsConfigParamInited(void);

EMVPBOC_API unsigned char *KernelConfigGetTC(void);

EMVPBOC_API uint8_t KernelConfigGetTerminalType(void);

EMVPBOC_API uint8_t KernelConfigIsSptrPSE(void);

EMVPBOC_API uint8_t KernelConfigIsCHDConfirm(void);

EMVPBOC_API unsigned char * KernelConfigGetEXTC(void);

EMVPBOC_API unsigned char * KernelConfigGetCountryCode(void);

EMVPBOC_API unsigned char * KernelConfigGetCurrencyCode(void);

EMVPBOC_API unsigned char KernelConfigIsStatusCheck(void);

EMVPBOC_API unsigned char KernelConfigIsOnline(void);

EMVPBOC_API unsigned char KernelConfigIsBatchCapture( void);

EMVPBOC_API unsigned char KernelConfigIsForceOnline(void);

EMVPBOC_API unsigned char * KernelConfigGetTransactionCapability(void);

EMVPBOC_API unsigned char * KernelConfigGetIFD(void);

EMVPBOC_API unsigned char * KernelConfigGetMerchantCategoryCode(void);

EMVPBOC_API char * KernelConfigGetMid(void);

EMVPBOC_API char * KernelConfigGetTid(void);

EMVPBOC_API unsigned char KernelConfigGetTransType(void);

EMVPBOC_API char * KernelConfigGetAcquirerId(void);

EMVPBOC_API unsigned char KernelConfigIsSuportSM(void);

EMVPBOC_API void KernelConfigSetOnlinePin(unsigned char option);

EMVPBOC_API unsigned char KernelConfigGetOnlinePin(void);

EMVPBOC_API int IsSupportDefaultTac(void);

EMVPBOC_API int IsSupportDenialTac(void);

EMVPBOC_API int IsSupportOnlineTac(void);

EMVPBOC_API int IsSupportDefaultTDOL(void);

EMVPBOC_API int KernelConfigSetDefaultTac(unsigned char *tac);

EMVPBOC_API int KernelConfigSetDenialTac(unsigned char *tac);

EMVPBOC_API int KernelConfigSetOnlineTac(unsigned char *tac);

EMVPBOC_API int KernelConfigSetFloorLimit(long floorLimit);

EMVPBOC_API int KernelConfigSetCvmLimit(long limit);

EMVPBOC_API int KernelConfigSetECTransLimit(long limit);

EMVPBOC_API int KernelConfigSetOfflineLimit(long limit);

EMVPBOC_API int KernelConfigSetCLTransLimit(long limit);

EMVPBOC_API int KernelConfigSetMaxTargetPercentage(unsigned char maxTargetPercentage);

EMVPBOC_API int KernelConfigSetTargetPercentage(unsigned char targetPercentage);

EMVPBOC_API int KernelConfigSetThreshold(long threshold);

EMVPBOC_API int KernelConfigSetRandomTrans(unsigned char option);

EMVPBOC_API int KernelConfigSetVelocityCheck(unsigned char option);

EMVPBOC_API int KernelConfigSetDefaultTDOL(unsigned char *tdol,int len);

EMVPBOC_API int KernelConfigSetDefaultDDOL(unsigned char *ddol,int len);

#ifdef __cplusplus
}
#endif

#endif
