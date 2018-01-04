#include "StdAfx.h"
#include "CKQ2017.h"
#include "MainFrm.h"
#include "cSerBuf_LoopRcv.h"
extern cSerBuf_LoopRcv  m_loopRcv64507;
extern cSerBuf_LoopRcv m_loopRcv13762;
#include "LogFile.h"
extern CLogFile plog;

CKQ2017::CKQ2017(void)
{
}

CKQ2017::~CKQ2017(void)
{
}
INT8U  CKQ2017::WaitCKQ2017Ack(INT32U nWaitFramTime , INT16U nWaiteByteTime,TH_OUT sPartCKQ2017DeCodeFrame &CKQ2017DecodeDataFrame)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	INT8U ack = DACK_FAILURE;
	INT8U recvbuf[CKQ2017_MAXSENDBUFLEN];
	INT16U recvbuflen=0;
	int nItem = 0;
	//pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.SetWindowTextW(_T("没进来？？？"));
	GetCOMMCKQ2017ToBuf(CKQ2017_MAXSENDBUFLEN , nWaitFramTime , nWaiteByteTime , recvbuf , recvbuflen);
	//pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.SetWindowTextW(_T("接收前<<"));
	if(recvbuflen>0)
	{
		//pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.SetWindowTextW(_T("接收到<<"));
		ack = DecodeCKQ2017Frame(recvbuf,recvbuflen,CKQ2017DecodeDataFrame);
		plog.saveLog_HexBuf(DATA_FILE,INPUT_DATA,recvbuf,recvbuflen);//打印接收帧数据
		nItem = pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem( nItem,pMainDlg-> m_strSysDateTime);
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 1, _T("接收<<"));
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 2 , pMainDlg->m_tools._buf16tostr16(recvbuf , recvbuflen , true));
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItem,FALSE);
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.RedrawItems(nItem,nItem);
		if(ack == DACK_SUCESS)
		{
			//plog.saveInformation_rev(CKQ2017DecodeDataFrame);
		}
		else
		{
		    plog.saveLog_err(DATA_FILE,NOTIME,_T(""),DACK_ERR_FORMAT);
		}
	}
	else{
		 //pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.SetWindowTextW(_T("没接收到<<"));
           plog.saveLog_err(DATA_FILE,NOTIME,_T(""),DACK_ERR_FORMAT);
	    }
	return ack;
}

void CKQ2017::GetCOMMCKQ2017ToBuf(INT16U  getLen , INT32U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	INT16U len = 0;
	INT32U dlycnt=0;
	INT16U acklen;
	INT16U tmp16;
	INT8U ack;
	while(true)
	{
		len = m_loopRcv13762.LoopReadRcvBufNByte(1 , recvbuf );

		if (1 == len) 
		{
			break;
		}
		if(nWaitFramTime >0 )
		{
			Sleep(10);
		}
		if (dlycnt == nWaitFramTime/10)
		{
			recvlen = 0;
			return ;
		}
		dlycnt++;
	}

	for(;len < getLen; )
	{

		tmp16= m_loopRcv13762.LoopReadRcvBufNByte(1, &recvbuf[len] );
		if( tmp16 ==0)
		{
			if(nWaiteByteTime > 0)
			{
				Sleep(nWaiteByteTime);
			}
			tmp16= m_loopRcv13762.LoopReadRcvBufNByte(1, &recvbuf[len] );
			if( tmp16 ==0)
			{
				break;
			}
		}
		len  += tmp16;

		ack =Check_CKQ2017_Full(recvbuf,len,acklen);
		//ack = Cgw13762.Check_376_2_Full(recvbuf,len,acklen);
		if( ack == DACK_SUCESS)
		{
			break;
		}


	}
	recvlen = len;
}
INT8U CKQ2017::Check_CKQ2017_Full(TH_IN const INT8U *pSrcBuf, TH_IN INT16U vSrcLen, TH_OUT INT16U &vDstLen){
		INT16U tmp16;
        INT16U i=0;
	    vDstLen=vSrcLen;//vDstLen整帧的长度
		   if(vSrcLen >= 6)//
			{				
				for(i=0; i<vSrcLen; i++)
		       {
					if(pSrcBuf[i] == 0x68)  
					break;
			  }
			  if(i+6 <= vSrcLen)
				{ 
					tmp16 = pSrcBuf[i+1];
					tmp16 >>= 8;
					tmp16 |= pSrcBuf[i+2];          
					if(pSrcBuf[tmp16+i+5] == 0x16)
					{
							//vDstLen = tmp16+6;
							return DACK_SUCESS;
					}
	           }	        
	    }
	return DACK_ERR_NULL;
}
INT8U CKQ2017::DecodeCKQ2017Frame(TH_IN  INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT sPartCKQ2017DeCodeFrame &CKQ2017DecodeDataFrame){
	INT8U  cs = 0;
	INT16U i = 0;
	INT16U j;
	//INT8U  temp;
	INT8U  ack = DACK_ERR_NULL;     //
	INT16U tmp16=0;
	if(vSrcLen >= 6)//
	{
			i=0;
			for(i=0; i<vSrcLen; i++)
			{
				if(pSrcBuf[i] != 0x68)  
				{
					continue;
				}
				if(i+6 <= vSrcLen)
				{ 
					tmp16 = pSrcBuf[i+1];
					tmp16 >>= 8;
					tmp16 |= pSrcBuf[i+2];   
					if(pSrcBuf[tmp16+i+5] == 0x16)
					{
							break;
					}
				}
			}
			CKQ2017DecodeDataFrame.TYPE=pSrcBuf[i+3];
			CKQ2017DecodeDataFrame.s_RcvDataLen = tmp16;
			for(INT16U mm = 0; mm<CKQ2017DecodeDataFrame.s_RcvDataLen; mm++)
			{
				CKQ2017DecodeDataFrame.s_RcvDataBuf[mm] = pSrcBuf[mm+i+4];//
			}


            for(j=0;j<tmp16;j++)//
			{
				CKQ2017DecodeDataFrame.s_RcvDataBuf[j] = pSrcBuf[j+i+4];
				cs += pSrcBuf[j+i+4];//
			}
			if(cs==pSrcBuf[tmp16+i+4]){
			   		if(pSrcBuf[tmp16+i+5] == 0x16)
					{
							return DACK_SUCESS;
					}
			}
			else{
				ack=DACK_ERR_CS;
			}

	}

	return ack;
}

INT8U CKQ2017::CodeCKQ2017Frame(TH_INOUT sPartCKQ2017CreatFrame &SrcCodeDataFrame)
{
	INT8U  cs = 0;
	INT16U i = 0;
	INT16U j;
	INT16U tmp16;
	INT8U ack = DACK_ERR_BUF;
	
	//if((SrcCodeDataFrame.s_RcvDataLen > 0) && (SrcCodeDataFrame.s_RcvDataBuf == DBUFNULL))
	//{
	//	ack = DACK_ERR_BUF;
	//	return ack;
	//}

   if(SrcCodeDataFrame.s_SendBuf != DBUFNULL)
   {			//
		SrcCodeDataFrame.s_SendLen = 6 + SrcCodeDataFrame.s_SendDataLen;//
		tmp16=SrcCodeDataFrame.s_SendLen;
		if(tmp16 <= CKQ2017_MAXSENDBUFLEN)
		{
			    INT8U *ptempbuf = SrcCodeDataFrame.s_SendBuf;
				i=0;
				ptempbuf[i++] = 0x68;      //
				ptempbuf[i++] = SrcCodeDataFrame.s_SendDataLen>>8;        //
				ptempbuf[i++] = (INT8U)SrcCodeDataFrame.s_SendDataLen;		 
				ptempbuf[i++] = SrcCodeDataFrame.TYPE;         //
				 
				//
				for(INT8U m=0; m<SrcCodeDataFrame.s_SendDataLen; m++)
				 {
						ptempbuf[i++] = SrcCodeDataFrame.s_SendDataBuf[m];
				 }	
				cs=CreatCKQ2017Cs(SrcCodeDataFrame.s_SendDataBuf,SrcCodeDataFrame.s_SendDataLen);
				ptempbuf[i++] = cs;         
				ptempbuf[i++] = 0x16;       
				ack = DACK_SUCESS;
		}
		else
		{
			ack = DACK_ERR_BUF;
		}		
	}
		return ack;
}

INT8U CKQ2017::CreatCKQ2017Cs(TH_IN const INT8U *vSrcBuf,TH_IN const INT16U vSrcLen)
{
	INT8U cs = 0;
	
	for(INT16U m = 0; m<vSrcLen; m++)
	{
		cs += vSrcBuf[m];
	}
	return cs;
}

void CKQ2017::SendBufToCom(INT8U *vSrcBuf,INT16U vSrcLen)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	pMainDlg->SendBufToCOMM(vSrcBuf ,vSrcLen , 0);	
	plog.saveLog_HexBuf(DATA_FILE,OUTPUT,vSrcBuf,vSrcLen);//打印发送帧数据

}
void CKQ2017::SendCKQ2017ToCom(sPartCKQ2017CreatFrame SrcCodeDataFrame)
{
	SendBufToCom(SrcCodeDataFrame.s_SendBuf ,SrcCodeDataFrame.s_SendLen );
	//plog.saveInformation_send(SrcCodeDataFrame);

}

 INT8U CKQ2017::SendRcvCKQ2017Frame(sPartCKQ2017CreatFrame &SrcCodeDataFrame,TH_OUT sPartCKQ2017DeCodeFrame &DstDecodeDataFrame)
 {
    INT8U ack;

	ack = CodeCKQ2017Frame(SrcCodeDataFrame);
	if(ack == DACK_SUCESS)
	{
		for(INT8U mm = 0; mm < 1; mm ++)
		{
			SendCKQ2017ToCom(SrcCodeDataFrame);

			ack = WaitCKQ2017AckTYPE(10000 , 20 ,SrcCodeDataFrame,DstDecodeDataFrame);

			if(ack == DACK_SUCESS)
			{
				break;
			}
		}
	}
     return ack;
 }


 INT8U  CKQ2017::WaitCKQ2017AckTYPE(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartCKQ2017CreatFrame SrcCodeDataFrame,TH_OUT sPartCKQ2017DeCodeFrame &CKQ2017DecodeDataFrame){
 	INT8U reack = DACK_FAILURE;
	INT8U ack = WaitCKQ2017Ack(nWaitFramTime,nWaiteByteTime,CKQ2017DecodeDataFrame);
	if(ack == DACK_SUCESS)
	{
		reack = ack;
		//CKQ2017DecodeDataFrame.TYPE=CKQ2017DecodeDataFrame.TYPE;
		INT8U type=SrcCodeDataFrame.TYPE+0x80;
		if(type == CKQ2017DecodeDataFrame.TYPE)
		{
			reack = DACK_SUCESS;
		}
		else
		{
			reack = DACK_EER_SEQERR;
		}
	}
	else
	{
		reack = ack;
	}
	return reack;
 }


 ///抄控器转发MAC 包含376.2的发送和接收
 INT8U CKQ2017::SendRec_MAC_13762_toCCO(sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &sRecv376_2HostFrame)//发送接收CKQ的帧包MAC帧包376.2  并提取376.2数据
{
	INT16U temp16 = 0;
	INT8U ack = -1;
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	sPartCKQ2017CreatFrame ptSendCKQ2017;
	sPartCKQ2017DeCodeFrame ptDeCodeCKQ2017,ptDeCodeCKQ2017_2;

	//组MSDU包376.2帧
	sPLCPacket_App_Down_13762 Down_Msdu13762DataCreatFrame;
	gMSDU2017.Fill_DownMSDU_13762Frame(Down_Msdu13762DataCreatFrame,sQGDW376_2HostFrame.s_SendDataBuf,sQGDW376_2HostFrame.s_SendDataLen);//填充结构
	gMSDU2017.Code_DownMSDU_13762Frame(Down_Msdu13762DataCreatFrame);//组MSDU包376.2的帧

	//组mac帧头
	MacHead Down_MacHeadForMsdu;
	INT8U MAC_y_buf[6]={0x01,0x02,0x03,0x04,0x05,0x00};//抄控器MAC ***********************要改
	//INT8U MAC_y_buf[6];
	//m_tools._str16tobuf16(pMain->m_strMAddress , MAC_y_buf , temp16 , false);
	INT8U MAC_sta_buf[6];//广播时用 单点要换 ***  大端
	m_tools._str16tobuf16( pMain->m_strMAddress , MAC_sta_buf , temp16 , false);//大端、、CCO的地址
	INT8U sendtype=0;//2;单播0，本地广播2 *** 单播给CCO
	INT16U mac_to_tei=1;//_ttoi(NodeTEI);//目的tei  要换  广播时是0xfff ***CCO 是1
	gMSDU2017.Fill_MacHeadStuct(Down_MacHeadForMsdu,Down_Msdu13762DataCreatFrame.s_SendDataLen,0x30,Down_Msdu13762DataCreatFrame.s_seq,MAC_y_buf,MAC_sta_buf,1016,mac_to_tei,sendtype,1);//抄控器TEI 1016
	gMSDU2017.Code_MacHeadForMsdu(Down_MacHeadForMsdu);

		//加完整性校验
	gMSDU2017.Add4BataIntegrityCheck(Down_Msdu13762DataCreatFrame);//加四字节完整性校验


	ptSendCKQ2017.TYPE=0x16;//抄控器的TYPE(需要替代)
	INT8U buf[1000];
	INT8U i = 0;
	INT16U TEI_16=1;//0xfff;//全局或单点TEI  ***CCO 的tei 为1
	buf[i++]=TEI_16>>8;//0x0f;//TEI_16>>8;//表TEI两个字节(需要替代)
	buf[i++]=(INT8U)TEI_16;//0xff;//(INT8U)TEI_16;//表TEI(需要替代)
	buf[i++]=0x01;  
	buf[i++]=0xFF;//业务LIDs是什么
	buf[i++]=(Down_MacHeadForMsdu.s_MacHeadDataLen+Down_Msdu13762DataCreatFrame.s_SendDataLen)>>8;
	buf[i++]=(INT8U)(Down_MacHeadForMsdu.s_MacHeadDataLen+Down_Msdu13762DataCreatFrame.s_SendDataLen);
	for(INT8U m=0; m<Down_MacHeadForMsdu.s_MacHeadDataLen; m++)//加入MSDU帧MAC头到抄控器帧中
	{
		buf[i++] = Down_MacHeadForMsdu.s_MacHeadDataBuf[m];
	}
	for(INT8U m=0; m<Down_Msdu13762DataCreatFrame.s_SendDataLen; m++)//加入MSDU帧到抄控器帧中
	{
		buf[i++] = Down_Msdu13762DataCreatFrame.s_SendDataBuf[m];
	}
	ptSendCKQ2017.s_SendDataBuf=buf;//加入包含了MSDU帧的抄控器数据域
	ptSendCKQ2017.s_SendDataLen=Down_MacHeadForMsdu.s_MacHeadDataLen+Down_Msdu13762DataCreatFrame.s_SendDataLen+6;//
	ack=SendRcvCKQ2017Frame(ptSendCKQ2017,ptDeCodeCKQ2017);//发送接收抄控器帧
	if(ack==DACK_SUCESS){
		if(ptDeCodeCKQ2017.TYPE==0x96){
			if(ptDeCodeCKQ2017.s_RcvDataBuf[0]=0x00){
				ack = WaitCKQ2017Ack(5000,10,ptDeCodeCKQ2017_2);
				if(ack==DACK_SUCESS){
					if(ptDeCodeCKQ2017_2.TYPE==0x97){

						//ptDeCodeCKQ2017.s_RcvDataBuf[17];//长度2字节
						//ptDeCodeCKQ2017.s_RcvDataBuf[18];
						if(ptDeCodeCKQ2017.s_RcvDataLen>22){
							INT16U len=ptDeCodeCKQ2017.s_RcvDataBuf[17]*16+ptDeCodeCKQ2017.s_RcvDataBuf[18];//MSDU长度
							//ptDeCodeCKQ2017.s_RcvDataBuf[19]->ptDeCodeCKQ2017.s_RcvDataBuf[18+len]//MADU报文
							sRecv376_2HostFrame.s_RcvDataLen=ptDeCodeCKQ2017.s_RcvDataBuf[21]*16+ptDeCodeCKQ2017.s_RcvDataBuf[22];
							if(ptDeCodeCKQ2017.s_RcvDataLen>23+sRecv376_2HostFrame.s_RcvDataLen){
								for(int m=0;m<sRecv376_2HostFrame.s_RcvDataLen;m++)
								{
									sRecv376_2HostFrame.s_RcvDataBuf[m]=ptDeCodeCKQ2017.s_RcvDataBuf[25+m];
								}
							}
						}
					}
				}
			}
			else{
				//1-报文长度错误
				//2-抄控器软件错误
				//3-目的TEI错误
				//4-MAC类型字段错误
				//5-抄控器硬件错误
				ack=ptDeCodeCKQ2017.s_RcvDataBuf[0];
			}
		}
		else{
		    ack=-1;
		}
	}
	return ack;
	
}
