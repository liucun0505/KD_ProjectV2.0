#ifndef _CKQ2017_H
#define _CKQ2017_H
#include "Tools.h"
#include "MSDU2017.h"
#define     CKQ2017_MAXSENDBUFLEN   2048
typedef struct 
{
	INT8U      TYPE;
	INT8U      *s_SendDataBuf;//发送数据区指针，高危指针，用前要检查是否有值，要指向合法空间
	INT16U     s_SendDataLen;//实际发送数据区的长度。
	INT8U      s_SendBuf[CKQ2017_MAXSENDBUFLEN];//
	INT16U     s_SendLen;//实际发送数据区的长度。
} sPartCKQ2017CreatFrame;//组帧的结构


typedef struct 
{
	INT8U      TYPE;
	INT8U      s_RcvDataBuf[CKQ2017_MAXSENDBUFLEN];//接收数据区指针，高危指针，用前要检查是否有值，要指向合法空间
	INT16U     s_RcvDataLen;//接收数据的个数
} sPartCKQ2017DeCodeFrame;//收帧的结构
class CKQ2017
{
public:
	CKQ2017(void);
	~CKQ2017(void);
public:
	CTools m_tools;
	MSDU2017 gMSDU2017;
	///////////
	INT8U   WaitCKQ2017Ack(INT32U nWaitFramTime , INT16U nWaiteByteTime,TH_OUT sPartCKQ2017DeCodeFrame &CKQ2017DecodeDataFrame);
     INT8U  WaitCKQ2017AckTYPE(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartCKQ2017CreatFrame SrcCodeDataFrame,TH_OUT sPartCKQ2017DeCodeFrame &CKQ2017DecodeDataFrame);
	void GetCOMMCKQ2017ToBuf(INT16U  getLen , INT32U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
	INT8U Check_CKQ2017_Full(TH_IN const INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT  INT16U &vDstLen);
	INT8U DecodeCKQ2017Frame(TH_IN  INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT sPartCKQ2017DeCodeFrame &CKQ2017DecodeDataFrame);

	////////

	INT8U CodeCKQ2017Frame(TH_INOUT sPartCKQ2017CreatFrame &SrcCodeDataFrame);
	INT8U CreatCKQ2017Cs(TH_IN const INT8U *vSrcBuf,TH_IN const INT16U vSrcLen);
	void SendBufToCom(INT8U *vSrcBuf,INT16U vSrcLen);
	void SendCKQ2017ToCom(sPartCKQ2017CreatFrame SrcCodeDataFrame);
	INT8U SendRcvCKQ2017Frame(sPartCKQ2017CreatFrame &SrcCodeDataFrame,TH_OUT sPartCKQ2017DeCodeFrame &DstDecodeDataFrame);


	INT8U SendRec_MAC_13762_toCCO(sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &sRecv376_2HostFrame);//发送接收CKQ的帧包MAC帧包376.2  并提取376.2数据

};

#endif