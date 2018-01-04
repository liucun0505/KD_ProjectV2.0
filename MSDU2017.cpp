#include "StdAfx.h"
#include "MSDU2017.h"


MSDU2017::MSDU2017(void)
{
}

MSDU2017::~MSDU2017(void)
{
}
const unsigned int crc32tab[] = {
 0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L, 0x706af48fL, 0xe963a535L, 0x9e6495a3L,
 0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L,
 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL, 0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
 0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L,
 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L, 0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
 0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
 0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L, 0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL,
 0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
 0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L,
 0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L, 0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL,
 0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
 0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
 0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L, 0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL,
 0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L, 0x73dc1683L,
 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L, 0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L,
 0xf00f9344L, 0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L,
 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL, 0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
 0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
 0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL, 0x4669be79L,
 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L, 0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL,
 0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL,
 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
 0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L,
 0x86d3d2d4L, 0xf1d4e242L, 0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L,
 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL, 0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
 0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L, 0x4969474dL, 0x3e6e77dbL,
 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
 0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L, 0xcdd70693L, 0x54de5729L, 0x23d967bfL,
 0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL
};

INT32U crc32( const INT8U *buf, unsigned int size){

    unsigned int i, crc;
	if(buf!=NULL){
    crc = 0xFFFFFFFF;
    for (i = 0; i < size; i++)
    crc = crc32tab[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
	}
    return crc^0xFFFFFFFF;

}
int mystrlen(INT8U* str){
    INT8U* temp = str;
    while('\0' != *str) str++;
    return str-temp;
}







//////////MSDU的MAC帧头
INT8U MSDU2017::Fill_MacHeadStuct(TH_INOUT MacHead &Down_MacHeadForMsdu,INT16U msdulen,INT8U msdutype,INT16U msduseq,INT8U *y_mac,INT8U *to_mac,INT16U y_tei,INT16U to_tei,INT8U sendtype,INT8U macbz)//先组MSDU帧再组MAC帧头结构
{
	//68 00 26 16 0F FF 01 FF 00 20 80 3F FF 2F 01 DF 01 30 04 28 00 08 00 05 00 00 01 02 03 04 05 06 FF FF FF FF FF FF 11 16 00 00 9B 16
	static INT16U seq=0x0000;
	Down_MacHeadForMsdu.u_MacHead_first_5.MacHead_first5.s_macver=0;
	Down_MacHeadForMsdu.u_MacHead_first_5.MacHead_first5.s_ckqtei=y_tei;
	Down_MacHeadForMsdu.u_MacHead_first_5.MacHead_first5.s_nodetei=to_tei;
	Down_MacHeadForMsdu.u_MacHead_first_5.MacHead_first5.s_mactype=sendtype;//发送类型  单播  广播  本地广播等
	Down_MacHeadForMsdu.u_MacHead_first_5.MacHead_first5.s_macnum=0;
	Down_MacHeadForMsdu.u_MacHead_first_5.MacHead_first5.s_macbaoliu=0;
	seq++;
	Down_MacHeadForMsdu.msduNum=seq;//MSDU序号
	Down_MacHeadForMsdu.msdutype=msdutype;//MSDU 类型
	
	Down_MacHeadForMsdu.u_MacHead_secend_5.MacHead_secend5.s_msdulen=msdulen;//长度 
	Down_MacHeadForMsdu.u_MacHead_secend_5.MacHead_secend5.s_rebootnum=5;//重启次数 随便给个5
	Down_MacHeadForMsdu.u_MacHead_secend_5.MacHead_secend5.s_dailujing=0;//代理主路径标识
	Down_MacHeadForMsdu.u_MacHead_secend_5.MacHead_secend5.s_macrote_n=0;//路由总跳数
	Down_MacHeadForMsdu.u_MacHead_secend_5.MacHead_secend5.s_macrote_sn=0;//路由剩余跳数
	Down_MacHeadForMsdu.u_MacHead_secend_5.MacHead_secend5.s_macgbfx=0;//广播方向  0 双向 1下行
	Down_MacHeadForMsdu.u_MacHead_secend_5.MacHead_secend5.s_ljxfbz=0;//路径修复标志
	Down_MacHeadForMsdu.u_MacHead_secend_5.MacHead_secend5.s_macbz=macbz;//MAC地址标志  1 携带MAC地址 0为携带
	Down_MacHeadForMsdu.u_MacHead_secend_5.MacHead_secend5.s_macbaoliu=0;//保留

	Down_MacHeadForMsdu.netnum=0x01;//组网序列号  随便给个 应该是CCO每次重新组网加1
    Down_MacHeadForMsdu.bl1=0;//保留
	Down_MacHeadForMsdu.bl2=0;//保留
	for(int j=0;j<6;j++)
	{
            Down_MacHeadForMsdu.s_macadd[j]=y_mac[j];
	}
	for(int j=0;j<6;j++)
	{
            Down_MacHeadForMsdu.s_mactoadd[j]=to_mac[j];
	}
	return 0;
}
INT8U MSDU2017::Code_MacHeadForMsdu(TH_INOUT MacHead &Down_MacHeadForMsdu){

	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
	INT8U *ptempbuf = Down_MacHeadForMsdu.s_MacHeadDataBuf;
	i=0; 
	for(INT8U m=0; m<5; m++)
	{
		ptempbuf[i++] = Down_MacHeadForMsdu.u_MacHead_first_5.s_MacHead_first[m];
	}
	ptempbuf[i++] = (INT8U)Down_MacHeadForMsdu.msduNum; 
	ptempbuf[i++] = Down_MacHeadForMsdu.msduNum>>8;
	ptempbuf[i++] = Down_MacHeadForMsdu.msdutype;
	for(INT8U m=0; m<5; m++)
	{
		ptempbuf[i++] = Down_MacHeadForMsdu.u_MacHead_secend_5.s_MacHead_secend[m];
	}
	ptempbuf[i++] = Down_MacHeadForMsdu.netnum;
	ptempbuf[i++] = Down_MacHeadForMsdu.bl1;
	ptempbuf[i++] = Down_MacHeadForMsdu.bl2;
	if(Down_MacHeadForMsdu.u_MacHead_secend_5.MacHead_secend5.s_macbz==1){
       	for(INT8U m=0; m<6; m++)
		{
			ptempbuf[i++] = Down_MacHeadForMsdu.s_macadd[m];
		}
		for(INT8U m=0; m<6; m++)
		{
			ptempbuf[i++] = Down_MacHeadForMsdu.s_mactoadd[m];
		}
		Down_MacHeadForMsdu.s_MacHeadDataLen=28;

	}
	else{
		Down_MacHeadForMsdu.s_MacHeadDataLen=16;
	}
	ack = DACK_SUCESS;
	return ack;
}

//////////抄表MSDU
//INT8U *Other645DataBuf  645帧
//INT16U  Other645DataBufLen  645帧长度
//INT8U TYPE  协议类型
INT8U MSDU2017::Fill_Down_TranDataFrame(TH_INOUT sPLCPacket_App_Down_TranData &Down_TranDataCreatFrame,INT8U *Other645DataBuf,INT16U  Other645DataBufLen,INT8U TYPE){
	static INT16U seq=0;
	seq++;
	if(seq==4095){seq=0;}
	Down_TranDataCreatFrame.Msdu2017_head.s_Port=0x11;
	Down_TranDataCreatFrame.Msdu2017_head.s_Id=PLCAPP_ID_POINT_TRANSMIT;
	Down_TranDataCreatFrame.Msdu2017_head.s_Con=0x00;
	Down_TranDataCreatFrame.u_TranDataDownHead4.s_DownHead4.s_pctver=1;
	Down_TranDataCreatFrame.u_TranDataDownHead4.s_DownHead4.s_headlen=8;
	Down_TranDataCreatFrame.u_TranDataDownHead4.s_DownHead4.s_reserved=0;
	Down_TranDataCreatFrame.u_TranDataDownHead4.s_DownHead4.s_pcttype=TYPE;
	Down_TranDataCreatFrame.u_TranDataDownHead4.s_DownHead4.s_datalen=Other645DataBufLen;
	Down_TranDataCreatFrame.s_seq=seq;
	Down_TranDataCreatFrame.s_timeout=50;
	Down_TranDataCreatFrame.s_select=0;//下行
	Down_TranDataCreatFrame.s_databuf=Other645DataBuf;//加645
	return 0;
}
INT8U MSDU2017::Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_TranData &Down_TranDataCreatFrame){
	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
   if(Down_TranDataCreatFrame.s_SendDataBuf != DBUFNULL)
   {			
		INT8U *ptempbuf = Down_TranDataCreatFrame.s_SendDataBuf;
		i=0;
		ptempbuf[i++] = Down_TranDataCreatFrame.Msdu2017_head.s_Port;      //
		ptempbuf[i++] = (INT8U)Down_TranDataCreatFrame.Msdu2017_head.s_Id;
		ptempbuf[i++] = Down_TranDataCreatFrame.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = Down_TranDataCreatFrame.Msdu2017_head.s_Con;		 

		for(INT8U m=0; m<4; m++)
		{
			ptempbuf[i++] = Down_TranDataCreatFrame.u_TranDataDownHead4.s_MSDUDownHead4[m];
		}
		ptempbuf[i++] = (INT8U)Down_TranDataCreatFrame.s_seq;
		ptempbuf[i++] = Down_TranDataCreatFrame.s_seq>>8; 
		

		ptempbuf[i++] = Down_TranDataCreatFrame.s_timeout;
		ptempbuf[i++] = Down_TranDataCreatFrame.s_select;
		for(INT8U m=0; m<Down_TranDataCreatFrame.u_TranDataDownHead4.s_DownHead4.s_datalen; m++)
		{
			ptempbuf[i++] = Down_TranDataCreatFrame.s_databuf[m];
		}
		Down_TranDataCreatFrame.s_SendDataLen=Down_TranDataCreatFrame.u_TranDataDownHead4.s_DownHead4.s_headlen+Down_TranDataCreatFrame.u_TranDataDownHead4.s_DownHead4.s_datalen+4;
		ack = DACK_SUCESS;
	}
	return ack;
}
INT8U MSDU2017::Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_TranData &Down_TranDataCreatFrame)//加四字节完整性校验
{
			//加完整性校验
		 INT32U crc2=0x00000000;
         crc2=crc32(Down_TranDataCreatFrame.s_SendDataBuf,Down_TranDataCreatFrame.s_SendDataLen);
		 if(Down_TranDataCreatFrame.s_SendDataBuf!=NULL){
			Down_TranDataCreatFrame.s_SendDataBuf[Down_TranDataCreatFrame.s_SendDataLen]=(INT8U)crc2;
			Down_TranDataCreatFrame.s_SendDataBuf[Down_TranDataCreatFrame.s_SendDataLen+1]=(INT8U)(crc2>>8);
			Down_TranDataCreatFrame.s_SendDataBuf[Down_TranDataCreatFrame.s_SendDataLen+2]=(INT8U)(crc2>>16);
			Down_TranDataCreatFrame.s_SendDataBuf[Down_TranDataCreatFrame.s_SendDataLen+3]=(INT8U)(crc2>>24);
			Down_TranDataCreatFrame.s_SendDataLen+=4;
		 }
		 return 0;

}




/****************包13762所用MSDU*********************/
//INT8U *s_13762DataBuf  376.2帧
//INT16U  s_13762DataBufLen  376.2帧长度
INT8U MSDU2017::Fill_DownMSDU_13762Frame(TH_INOUT sPLCPacket_App_Down_13762 &Down_13762CreatFrame,INT8U *s_13762DataBuf,INT16U s_13762DataBufLen)//MSDU包13762结构的填充
{
	static INT16U seq=0;
	seq++;
	if(seq==256){seq=0;}
	Down_13762CreatFrame.Msdu2017_head.s_Port=0x11;
	Down_13762CreatFrame.Msdu2017_head.s_Id=PLCAPP_ID_EXTEND;
	Down_13762CreatFrame.Msdu2017_head.s_Con=0x00;
	Down_13762CreatFrame.u_DataDown_13762_2.s_Down13762_2.s_pctver=1;
	Down_13762CreatFrame.u_DataDown_13762_2.s_Down13762_2.s_headlen=6;
	Down_13762CreatFrame.u_DataDown_13762_2.s_Down13762_2.s_reserved=0;
	//Down_13762CreatFrame.s_KID=PLCAPP_ID_EXTEND;
	Down_13762CreatFrame.s_3762datalen=s_13762DataBufLen;
	Down_13762CreatFrame.s_seq=seq;
	Down_13762CreatFrame.s_3762databuf=s_13762DataBuf;//加376.2
	return 0;

}
INT8U MSDU2017::Code_DownMSDU_13762Frame(TH_INOUT sPLCPacket_App_Down_13762 &Down_13762CreatFrame)//MSDU包13762组帧
{
	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
   if(Down_13762CreatFrame.s_SendDataBuf != DBUFNULL)
   {			
		INT8U *ptempbuf = Down_13762CreatFrame.s_SendDataBuf;
		i=0;
		ptempbuf[i++] = Down_13762CreatFrame.Msdu2017_head.s_Port;      //
		ptempbuf[i++] = (INT8U)Down_13762CreatFrame.Msdu2017_head.s_Id;
		ptempbuf[i++] = Down_13762CreatFrame.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = Down_13762CreatFrame.Msdu2017_head.s_Con;		 

		for(INT8U m=0; m<2; m++)
		{
			ptempbuf[i++] = Down_13762CreatFrame.u_DataDown_13762_2.s_Down13762[m];
		}
		//ptempbuf[i++] = (INT8U)Down_13762CreatFrame.Msdu2017_head.s_Id;
		//ptempbuf[i++] = Down_13762CreatFrame.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = (INT8U)Down_13762CreatFrame.s_3762datalen;
		ptempbuf[i++] = Down_13762CreatFrame.s_3762datalen>>8; 
		ptempbuf[i++] = (INT8U)Down_13762CreatFrame.s_seq;
		ptempbuf[i++] = Down_13762CreatFrame.s_seq>>8; 
		for(INT8U m=0; m<Down_13762CreatFrame.s_3762datalen; m++)
		{
			ptempbuf[i++] = Down_13762CreatFrame.s_3762databuf[m];
		}
		Down_13762CreatFrame.s_SendDataLen=Down_13762CreatFrame.u_DataDown_13762_2.s_Down13762_2.s_headlen+Down_13762CreatFrame.s_3762datalen+4;
		ack = DACK_SUCESS;
	}
	return ack;

}
INT8U MSDU2017::Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_13762 &Down_13762CreatFrame)//加四字节完整性校验
{
	INT32U crc2=0x00000000;
    crc2=crc32(Down_13762CreatFrame.s_SendDataBuf,Down_13762CreatFrame.s_SendDataLen);
	if(Down_13762CreatFrame.s_SendDataBuf!=NULL){
	Down_13762CreatFrame.s_SendDataBuf[Down_13762CreatFrame.s_SendDataLen]=(INT8U)crc2;
	Down_13762CreatFrame.s_SendDataBuf[Down_13762CreatFrame.s_SendDataLen+1]=(INT8U)(crc2>>8);
	Down_13762CreatFrame.s_SendDataBuf[Down_13762CreatFrame.s_SendDataLen+2]=(INT8U)(crc2>>16);
	Down_13762CreatFrame.s_SendDataBuf[Down_13762CreatFrame.s_SendDataLen+3]=(INT8U)(crc2>>24);
	Down_13762CreatFrame.s_SendDataLen+=4;
	}
	return 0;
}






/****************升级所用MSDU*********************/
////开始升级MSDU
//TH_INOUT sPLCPacket_App_Down_FTPStart &Down_FTPStartCreatFrame//开始升级结构体
//INT16U  s_window;                           //升级时间窗  单位分钟
//INT16U  s_blksize;                          //升级块大小
//INT32U  s_filesize;                         //升级文件大小
//INT32U  s_fileCRC;                          //文件校验
INT8U MSDU2017::Fill_sPLCPacket_App_Down_FTPStart(TH_INOUT sPLCPacket_App_Down_FTPStart &Down_FTPStartCreatFrame,INT16U windowTime,INT16U blksize,INT32U filesize,INT32U fileCRC){
	static INT32U StartID=16;
	StartID++;
	if(StartID==100000){StartID=16;}
	Down_FTPStartCreatFrame.Msdu2017_head.s_Port=0x12;//变
	Down_FTPStartCreatFrame.Msdu2017_head.s_Id=PLCAPP_ID_FTP_START;//变
	Down_FTPStartCreatFrame.Msdu2017_head.s_Con=0x00;
	Down_FTPStartCreatFrame.u_DataDownFTP4START.s_DownFTP4.s_pctver=1;
	Down_FTPStartCreatFrame.u_DataDownFTP4START.s_DownFTP4.s_headlen=20;//变
	Down_FTPStartCreatFrame.u_DataDownFTP4START.s_DownFTP4.s_reserved=0;
	Down_FTPStartCreatFrame.s_ftpID=StartID;
	Down_FTPStartCreatFrame.s_window=windowTime;
    Down_FTPStartCreatFrame.s_blksize=blksize;
	Down_FTPStartCreatFrame.s_filesize=filesize;
	Down_FTPStartCreatFrame.s_fileCRC=fileCRC;
	return 0;
}
INT8U MSDU2017::Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPStart &Down_FTPStartCreatFrame){
	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
    if(Down_FTPStartCreatFrame.s_SendDataBuf != DBUFNULL)
    {			
		INT8U *ptempbuf = Down_FTPStartCreatFrame.s_SendDataBuf;
		i=0;
		ptempbuf[i++] = Down_FTPStartCreatFrame.Msdu2017_head.s_Port;      //
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.Msdu2017_head.s_Id;
		ptempbuf[i++] = Down_FTPStartCreatFrame.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = Down_FTPStartCreatFrame.Msdu2017_head.s_Con;		 

		for(INT8U m=0; m<4; m++)
		{
			ptempbuf[i++] = Down_FTPStartCreatFrame.u_DataDownFTP4START.s_MSDUFDownFTP4[m];
		}
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_ftpID;
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_ftpID>>8; 
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_ftpID>>16; 
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_ftpID>>24; 

		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_window;
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_window>>8; 

		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_blksize;
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_blksize>>8; 

		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_filesize;
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_filesize>>8; 
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_filesize>>16; 
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_filesize>>24; 

		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_fileCRC;
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_fileCRC>>8; 
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_fileCRC>>16; 
		ptempbuf[i++] = (INT8U)Down_FTPStartCreatFrame.s_fileCRC>>24; 

		Down_FTPStartCreatFrame.s_SendDataLen=Down_FTPStartCreatFrame.u_DataDownFTP4START.s_DownFTP4.s_headlen+4;
		ack = DACK_SUCESS;
	}
	return ack;
}
INT8U MSDU2017::Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPStart &Down_FTPStartCreatFrame)//加四字节完整性校验
{
	INT32U crc2=0x00000000;
    crc2=crc32(Down_FTPStartCreatFrame.s_SendDataBuf,Down_FTPStartCreatFrame.s_SendDataLen);
	if(Down_FTPStartCreatFrame.s_SendDataBuf!=NULL){
	Down_FTPStartCreatFrame.s_SendDataBuf[Down_FTPStartCreatFrame.s_SendDataLen]=(INT8U)crc2;
	Down_FTPStartCreatFrame.s_SendDataBuf[Down_FTPStartCreatFrame.s_SendDataLen+1]=(INT8U)(crc2>>8);
	Down_FTPStartCreatFrame.s_SendDataBuf[Down_FTPStartCreatFrame.s_SendDataLen+2]=(INT8U)(crc2>>16);
	Down_FTPStartCreatFrame.s_SendDataBuf[Down_FTPStartCreatFrame.s_SendDataLen+3]=(INT8U)(crc2>>24);
	Down_FTPStartCreatFrame.s_SendDataLen+=4;
	}
	return 0;
}





////停止升级MSDU
//sPLCPacket_App_Down_FTPStop &Down_FTPStopCreatFrame 停止升级结构体
//INT32U UPID  升级ID
INT8U MSDU2017::Fill_sPLCPacket_App_Down_FTPStop(TH_INOUT sPLCPacket_App_Down_FTPStop &Down_FTPStopCreatFrame,INT32U UPID){
	Down_FTPStopCreatFrame.Msdu2017_head.s_Port=0x12;//变
	Down_FTPStopCreatFrame.Msdu2017_head.s_Id=PLCAPP_ID_FTP_STOP;//变
	Down_FTPStopCreatFrame.Msdu2017_head.s_Con=0x00;
	Down_FTPStopCreatFrame.u_DataDownFTP4STOP.s_DownFTP4.s_pctver=1;
	Down_FTPStopCreatFrame.u_DataDownFTP4STOP.s_DownFTP4.s_headlen=8;//变
	Down_FTPStopCreatFrame.u_DataDownFTP4STOP.s_DownFTP4.s_reserved=0;
	Down_FTPStopCreatFrame.s_ftpID=UPID;
	return 0;
}
INT8U MSDU2017::Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPStop &Down_FTPStopCreatFrame){
	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
    if(Down_FTPStopCreatFrame.s_SendDataBuf != DBUFNULL)
    {			
		INT8U *ptempbuf = Down_FTPStopCreatFrame.s_SendDataBuf;
		i=0;
		ptempbuf[i++] = Down_FTPStopCreatFrame.Msdu2017_head.s_Port;      //
		ptempbuf[i++] = (INT8U)Down_FTPStopCreatFrame.Msdu2017_head.s_Id;
		ptempbuf[i++] = Down_FTPStopCreatFrame.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = Down_FTPStopCreatFrame.Msdu2017_head.s_Con;		 

		for(INT8U m=0; m<4; m++)
		{
			ptempbuf[i++] = Down_FTPStopCreatFrame.u_DataDownFTP4STOP.s_MSDUFDownFTP4[m];
		}
		ptempbuf[i++] = (INT8U)Down_FTPStopCreatFrame.s_ftpID;
		ptempbuf[i++] = (INT8U)Down_FTPStopCreatFrame.s_ftpID>>8; 
		ptempbuf[i++] = (INT8U)Down_FTPStopCreatFrame.s_ftpID>>16; 
		ptempbuf[i++] = (INT8U)Down_FTPStopCreatFrame.s_ftpID>>24; 

		Down_FTPStopCreatFrame.s_SendDataLen=Down_FTPStopCreatFrame.u_DataDownFTP4STOP.s_DownFTP4.s_headlen+4;
		ack = DACK_SUCESS;
	}
	return ack;
}
INT8U MSDU2017::Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPStop &Down_FTPStopCreatFrame)//加四字节完整性校验
{
	INT32U crc2=0x00000000;
    crc2=crc32(Down_FTPStopCreatFrame.s_SendDataBuf,Down_FTPStopCreatFrame.s_SendDataLen);
	if(Down_FTPStopCreatFrame.s_SendDataBuf!=NULL){
	Down_FTPStopCreatFrame.s_SendDataBuf[Down_FTPStopCreatFrame.s_SendDataLen]=(INT8U)crc2;
	Down_FTPStopCreatFrame.s_SendDataBuf[Down_FTPStopCreatFrame.s_SendDataLen+1]=(INT8U)(crc2>>8);
	Down_FTPStopCreatFrame.s_SendDataBuf[Down_FTPStopCreatFrame.s_SendDataLen+2]=(INT8U)(crc2>>16);
	Down_FTPStopCreatFrame.s_SendDataBuf[Down_FTPStopCreatFrame.s_SendDataLen+3]=(INT8U)(crc2>>24);
	Down_FTPStopCreatFrame.s_SendDataLen+=4;
	}
	return 0;
}




////文件传输MSDU
//INT16U blksize;                          //数据块大小
//INT32U UPID;                             //升级ID
//INT32U blkno;                            //数据块编号
//INT8U * s_FileDataBuf;                   //数据块数据
INT8U MSDU2017::Fill_sPLCPacket_App_Down_FTPTransfile(TH_INOUT sPLCPacket_App_Down_FTPTransfile &Down_FTPTransfileCreatFrame,INT16U blksize,INT32U UPID,INT32U blkno,INT8U *s_FileDataBuf){
	Down_FTPTransfileCreatFrame.Msdu2017_head.s_Port=0x12;//变
	Down_FTPTransfileCreatFrame.Msdu2017_head.s_Id=PLCAPP_ID_FTP_TRANSFER;//变
	Down_FTPTransfileCreatFrame.Msdu2017_head.s_Con=0x00;
	Down_FTPTransfileCreatFrame.u_DataDownFTPTransfile.s_DownFTPTransfile2.s_pctver=1;
	Down_FTPTransfileCreatFrame.u_DataDownFTPTransfile.s_DownFTPTransfile2.s_headlen=12;//变
	Down_FTPTransfileCreatFrame.u_DataDownFTPTransfile.s_DownFTPTransfile2.s_reserved=0;
	Down_FTPTransfileCreatFrame.s_blksize=blksize;
	Down_FTPTransfileCreatFrame.s_ftpID=UPID;
	Down_FTPTransfileCreatFrame.s_blkno=blkno;
	Down_FTPTransfileCreatFrame.s_DataBuf=s_FileDataBuf;
	return 0;
}
INT8U MSDU2017::Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPTransfile &Down_FTPTransfileCreatFrame){
	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
   if(Down_FTPTransfileCreatFrame.s_SendDataBuf != DBUFNULL)
   {			
		INT8U *ptempbuf = Down_FTPTransfileCreatFrame.s_SendDataBuf;
		i=0;
		ptempbuf[i++] = Down_FTPTransfileCreatFrame.Msdu2017_head.s_Port;      //
		ptempbuf[i++] = (INT8U)Down_FTPTransfileCreatFrame.Msdu2017_head.s_Id;
		ptempbuf[i++] = Down_FTPTransfileCreatFrame.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = Down_FTPTransfileCreatFrame.Msdu2017_head.s_Con;		 

		for(INT8U m=0; m<2; m++)
		{
			ptempbuf[i++] = Down_FTPTransfileCreatFrame.u_DataDownFTPTransfile.s_DownFTPFile[2];
		}

		ptempbuf[i++] = (INT8U)Down_FTPTransfileCreatFrame.s_blksize;
		ptempbuf[i++] =Down_FTPTransfileCreatFrame.s_blksize>>8; 

		ptempbuf[i++] = (INT8U)Down_FTPTransfileCreatFrame.s_ftpID;
		ptempbuf[i++] = (INT8U)Down_FTPTransfileCreatFrame.s_ftpID>>8; 
		ptempbuf[i++] = (INT8U)Down_FTPTransfileCreatFrame.s_ftpID>>16; 
		ptempbuf[i++] = (INT8U)Down_FTPTransfileCreatFrame.s_ftpID>>24; 

		ptempbuf[i++] = (INT8U)Down_FTPTransfileCreatFrame.s_blkno;
		ptempbuf[i++] = (INT8U)Down_FTPTransfileCreatFrame.s_blkno>>8; 
		ptempbuf[i++] = (INT8U)Down_FTPTransfileCreatFrame.s_blkno>>16; 
		ptempbuf[i++] = (INT8U)Down_FTPTransfileCreatFrame.s_blkno>>24; 

		for(INT16U m=0; m<Down_FTPTransfileCreatFrame.s_blksize; m++)
		{
			ptempbuf[i++] = Down_FTPTransfileCreatFrame.s_DataBuf[m];
		}
		Down_FTPTransfileCreatFrame.s_SendDataLen=Down_FTPTransfileCreatFrame.u_DataDownFTPTransfile.s_DownFTPTransfile2.s_headlen+Down_FTPTransfileCreatFrame.s_blksize+4;
		ack = DACK_SUCESS;
	}
	return ack;
}
INT8U MSDU2017::Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPTransfile &Down_FTPTransfileCreatFrame)//加四字节完整性校验
{
	INT32U crc2=0x00000000;
    crc2=crc32(Down_FTPTransfileCreatFrame.s_SendDataBuf,Down_FTPTransfileCreatFrame.s_SendDataLen);
	if(Down_FTPTransfileCreatFrame.s_SendDataBuf!=NULL){
	Down_FTPTransfileCreatFrame.s_SendDataBuf[Down_FTPTransfileCreatFrame.s_SendDataLen]=(INT8U)crc2;
	Down_FTPTransfileCreatFrame.s_SendDataBuf[Down_FTPTransfileCreatFrame.s_SendDataLen+1]=(INT8U)(crc2>>8);
	Down_FTPTransfileCreatFrame.s_SendDataBuf[Down_FTPTransfileCreatFrame.s_SendDataLen+2]=(INT8U)(crc2>>16);
	Down_FTPTransfileCreatFrame.s_SendDataBuf[Down_FTPTransfileCreatFrame.s_SendDataLen+3]=(INT8U)(crc2>>24);
	Down_FTPTransfileCreatFrame.s_SendDataLen+=4;
	}
	return 0;
}



////查询站点升级状态MSDU
//INT16U s_blknum;                           //需要查询的数据块数
//INT32U s_startno;                          //起始数据块编号    
//INT32U s_ftpID;                            //升级ID
INT8U MSDU2017::Fill_sPLCPacket_App_Down_FTPGetStatus(TH_INOUT sPLCPacket_App_Down_FTPGetStatus &Down_FTPGetStatusCreatFrame,INT16U blknum,INT32U startno,INT32U ftpID){
	Down_FTPGetStatusCreatFrame.Msdu2017_head.s_Port=0x12;//变
	Down_FTPGetStatusCreatFrame.Msdu2017_head.s_Id=PLCAPP_ID_FTP_GET_STATUS;//变
	Down_FTPGetStatusCreatFrame.Msdu2017_head.s_Con=0x00;
	Down_FTPGetStatusCreatFrame.u_DataDownFTPGetStatus.s_DownFTPGetStatus2.s_pctver=1;
	Down_FTPGetStatusCreatFrame.u_DataDownFTPGetStatus.s_DownFTPGetStatus2.s_headlen=12;//变
	Down_FTPGetStatusCreatFrame.u_DataDownFTPGetStatus.s_DownFTPGetStatus2.s_reserved=0;
	Down_FTPGetStatusCreatFrame.s_blknum=blknum;
	Down_FTPGetStatusCreatFrame.s_startno=startno;
	Down_FTPGetStatusCreatFrame.s_ftpID=ftpID;
	return 0;
}
INT8U MSDU2017::Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPGetStatus &Down_FTPGetStatusCreatFrame){
	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
   if(Down_FTPGetStatusCreatFrame.s_SendDataBuf != DBUFNULL)
   {			
		INT8U *ptempbuf = Down_FTPGetStatusCreatFrame.s_SendDataBuf;
		i=0;
		ptempbuf[i++] = Down_FTPGetStatusCreatFrame.Msdu2017_head.s_Port;      //
		ptempbuf[i++] = (INT8U)Down_FTPGetStatusCreatFrame.Msdu2017_head.s_Id;
		ptempbuf[i++] = Down_FTPGetStatusCreatFrame.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = Down_FTPGetStatusCreatFrame.Msdu2017_head.s_Con;		 

		for(INT8U m=0; m<2; m++)
		{
			ptempbuf[i++] = Down_FTPGetStatusCreatFrame.u_DataDownFTPGetStatus.s_DownFTPStatus[m];
		}

		ptempbuf[i++] = (INT8U)Down_FTPGetStatusCreatFrame.s_blknum;
		ptempbuf[i++] =Down_FTPGetStatusCreatFrame.s_blknum>>8; 

		ptempbuf[i++] = (INT8U)Down_FTPGetStatusCreatFrame.s_startno;
		ptempbuf[i++] = (INT8U)Down_FTPGetStatusCreatFrame.s_startno>>8; 
		ptempbuf[i++] = (INT8U)Down_FTPGetStatusCreatFrame.s_startno>>16; 
		ptempbuf[i++] = (INT8U)Down_FTPGetStatusCreatFrame.s_startno>>24;

		ptempbuf[i++] = (INT8U)Down_FTPGetStatusCreatFrame.s_ftpID;
		ptempbuf[i++] = (INT8U)Down_FTPGetStatusCreatFrame.s_ftpID>>8; 
		ptempbuf[i++] = (INT8U)Down_FTPGetStatusCreatFrame.s_ftpID>>16; 
		ptempbuf[i++] = (INT8U)Down_FTPGetStatusCreatFrame.s_ftpID>>24; 
 

		Down_FTPGetStatusCreatFrame.s_SendDataLen=Down_FTPGetStatusCreatFrame.u_DataDownFTPGetStatus.s_DownFTPGetStatus2.s_headlen+4;
		ack = DACK_SUCESS;
	}
	return ack;
}
INT8U MSDU2017::Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPGetStatus &Down_FTPGetStatusCreatFrame)//加四字节完整性校验
{
	INT32U crc2=0x00000000;
    crc2=crc32(Down_FTPGetStatusCreatFrame.s_SendDataBuf,Down_FTPGetStatusCreatFrame.s_SendDataLen);
	if(Down_FTPGetStatusCreatFrame.s_SendDataBuf!=NULL){
	Down_FTPGetStatusCreatFrame.s_SendDataBuf[Down_FTPGetStatusCreatFrame.s_SendDataLen]=(INT8U)crc2;
	Down_FTPGetStatusCreatFrame.s_SendDataBuf[Down_FTPGetStatusCreatFrame.s_SendDataLen+1]=(INT8U)(crc2>>8);
	Down_FTPGetStatusCreatFrame.s_SendDataBuf[Down_FTPGetStatusCreatFrame.s_SendDataLen+2]=(INT8U)(crc2>>16);
	Down_FTPGetStatusCreatFrame.s_SendDataBuf[Down_FTPGetStatusCreatFrame.s_SendDataLen+3]=(INT8U)(crc2>>24);
	Down_FTPGetStatusCreatFrame.s_SendDataLen+=4;
	}
	return 0;
}


////执行升级MSDU
//INT16U waitsec;                          //等待复位时间 单位秒
//INT32U ftpID;                            //升级ID    
//INT32U trysec;                           //试运行时间  单位秒
INT8U Fill_sPLCPacket_App_Down_FTPExec(TH_INOUT sPLCPacket_App_Down_FTPExec &Down_FTPExecCreatFrame,INT16U waitsec,INT32U ftpID,INT32U trysec){
	Down_FTPExecCreatFrame.Msdu2017_head.s_Port=0x12;//变
	Down_FTPExecCreatFrame.Msdu2017_head.s_Id=PLCAPP_ID_FTP_EXEC;//变
	Down_FTPExecCreatFrame.Msdu2017_head.s_Con=0x00;
	Down_FTPExecCreatFrame.u_DataDownFTPExec.s_DoFTPFTPExec2.s_pctver=1;
	Down_FTPExecCreatFrame.u_DataDownFTPExec.s_DoFTPFTPExec2.s_headlen=13;//变
	Down_FTPExecCreatFrame.u_DataDownFTPExec.s_DoFTPFTPExec2.s_reserved=0;
	Down_FTPExecCreatFrame.s_waitsec=waitsec;
	Down_FTPExecCreatFrame.s_ftpID=ftpID;
	Down_FTPExecCreatFrame.s_trysec=trysec;
	return 0;
}
INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPExec &Down_FTPExecCreatFrame){
	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
    if(Down_FTPExecCreatFrame.s_SendDataBuf != DBUFNULL)
    {			
		INT8U *ptempbuf = Down_FTPExecCreatFrame.s_SendDataBuf;
		i=0;
		ptempbuf[i++] = Down_FTPExecCreatFrame.Msdu2017_head.s_Port;      //
		ptempbuf[i++] = (INT8U)Down_FTPExecCreatFrame.Msdu2017_head.s_Id;
		ptempbuf[i++] = Down_FTPExecCreatFrame.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = Down_FTPExecCreatFrame.Msdu2017_head.s_Con;		 

		for(INT8U m=0; m<2; m++)
		{
			ptempbuf[i++] = Down_FTPExecCreatFrame.u_DataDownFTPExec.s_DownFTPExec[m];
		}

		ptempbuf[i++] = (INT8U)Down_FTPExecCreatFrame.s_waitsec;
		ptempbuf[i++] =Down_FTPExecCreatFrame.s_waitsec>>8; 

		ptempbuf[i++] = (INT8U)Down_FTPExecCreatFrame.s_ftpID;
		ptempbuf[i++] = (INT8U)Down_FTPExecCreatFrame.s_ftpID>>8; 
		ptempbuf[i++] = (INT8U)Down_FTPExecCreatFrame.s_ftpID>>16; 
		ptempbuf[i++] = (INT8U)Down_FTPExecCreatFrame.s_ftpID>>24; 

		ptempbuf[i++] = (INT8U)Down_FTPExecCreatFrame.s_trysec;
		ptempbuf[i++] = (INT8U)Down_FTPExecCreatFrame.s_trysec>>8; 
		ptempbuf[i++] = (INT8U)Down_FTPExecCreatFrame.s_trysec>>16; 
		ptempbuf[i++] = (INT8U)Down_FTPExecCreatFrame.s_trysec>>24;

		Down_FTPExecCreatFrame.s_SendDataLen=Down_FTPExecCreatFrame.u_DataDownFTPExec.s_DoFTPFTPExec2.s_headlen+4;
		ack = DACK_SUCESS;
	}
	return ack;
}
INT8U MSDU2017::Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPExec &Down_FTPExecCreatFrame)//加四字节完整性校验
{
	INT32U crc2=0x00000000;
    crc2=crc32(Down_FTPExecCreatFrame.s_SendDataBuf,Down_FTPExecCreatFrame.s_SendDataLen);
	if(Down_FTPExecCreatFrame.s_SendDataBuf!=NULL){
	Down_FTPExecCreatFrame.s_SendDataBuf[Down_FTPExecCreatFrame.s_SendDataLen]=(INT8U)crc2;
	Down_FTPExecCreatFrame.s_SendDataBuf[Down_FTPExecCreatFrame.s_SendDataLen+1]=(INT8U)(crc2>>8);
	Down_FTPExecCreatFrame.s_SendDataBuf[Down_FTPExecCreatFrame.s_SendDataLen+2]=(INT8U)(crc2>>16);
	Down_FTPExecCreatFrame.s_SendDataBuf[Down_FTPExecCreatFrame.s_SendDataLen+3]=(INT8U)(crc2>>24);
	Down_FTPExecCreatFrame.s_SendDataLen+=4;
	}
	return 0;
}



////查询站点信息MSDU
//INT8U infonum;                          //信息列表元素个数
//INT8U *infoDataBuf;                          //数据  
INT8U Fill_sPLCPacket_App_Down_FTPGetInfo(TH_INOUT sPLCPacket_App_Down_FTPGetInfo &Down_FTPGetInfoCreatFrame,INT8U infonum,INT8U *infoDataBuf){
	Down_FTPGetInfoCreatFrame.Msdu2017_head.s_Port=0x12;//变
	Down_FTPGetInfoCreatFrame.Msdu2017_head.s_Id=PLCAPP_ID_FTP_GET_STAINFO;//变
	Down_FTPGetInfoCreatFrame.Msdu2017_head.s_Con=0x00;
	Down_FTPGetInfoCreatFrame.u_DataDownFTPGetInfo.s_DoFTPGetInfo3.s_pctver=1;
	Down_FTPGetInfoCreatFrame.u_DataDownFTPGetInfo.s_DoFTPGetInfo3.s_headlen=4;//变
	Down_FTPGetInfoCreatFrame.u_DataDownFTPGetInfo.s_DoFTPGetInfo3.s_reserved=0;
	Down_FTPGetInfoCreatFrame.s_infonum=infonum;
	Down_FTPGetInfoCreatFrame.s_infoDataBuf=infoDataBuf;
	return 0;
}
INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPGetInfo &Down_FTPGetInfoCreatFrame){
	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
    if(Down_FTPGetInfoCreatFrame.s_SendDataBuf != DBUFNULL)
    {			
		INT8U *ptempbuf = Down_FTPGetInfoCreatFrame.s_SendDataBuf;
		i=0;
		ptempbuf[i++] = Down_FTPGetInfoCreatFrame.Msdu2017_head.s_Port;      //
		ptempbuf[i++] = (INT8U)Down_FTPGetInfoCreatFrame.Msdu2017_head.s_Id;
		ptempbuf[i++] = Down_FTPGetInfoCreatFrame.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = Down_FTPGetInfoCreatFrame.Msdu2017_head.s_Con;		 

		for(INT8U m=0; m<3; m++)
		{
			ptempbuf[i++] = Down_FTPGetInfoCreatFrame.u_DataDownFTPGetInfo.s_DownFTPGetInfo[m];
		}

		ptempbuf[i++] = Down_FTPGetInfoCreatFrame.s_infonum;
		for(INT8U m=0; m<Down_FTPGetInfoCreatFrame.s_infonum; m++)
		{
			ptempbuf[i++] = Down_FTPGetInfoCreatFrame.s_infoDataBuf[m];
		}

		Down_FTPGetInfoCreatFrame.s_SendDataLen=Down_FTPGetInfoCreatFrame.u_DataDownFTPGetInfo.s_DoFTPGetInfo3.s_headlen+Down_FTPGetInfoCreatFrame.s_infonum+4;
		ack = DACK_SUCESS;
	}
	return ack;
}
INT8U MSDU2017::Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPGetInfo &Down_FTPGetInfoCreatFrame)//加四字节完整性校验
{
	INT32U crc2=0x00000000;
    crc2=crc32(Down_FTPGetInfoCreatFrame.s_SendDataBuf,Down_FTPGetInfoCreatFrame.s_SendDataLen);
	if(Down_FTPGetInfoCreatFrame.s_SendDataBuf!=NULL){
	Down_FTPGetInfoCreatFrame.s_SendDataBuf[Down_FTPGetInfoCreatFrame.s_SendDataLen]=(INT8U)crc2;
	Down_FTPGetInfoCreatFrame.s_SendDataBuf[Down_FTPGetInfoCreatFrame.s_SendDataLen+1]=(INT8U)(crc2>>8);
	Down_FTPGetInfoCreatFrame.s_SendDataBuf[Down_FTPGetInfoCreatFrame.s_SendDataLen+2]=(INT8U)(crc2>>16);
	Down_FTPGetInfoCreatFrame.s_SendDataBuf[Down_FTPGetInfoCreatFrame.s_SendDataLen+3]=(INT8U)(crc2>>24);
	Down_FTPGetInfoCreatFrame.s_SendDataLen+=4;
	}
	return 0;
}

//****START****确认否认MSDU******//
//INT8U dir方向  0下行  1上行
//INT8U okcancel  0否认 1确认
//INT16U seq
INT8U MSDU2017::Fill_App_OKCancel(TH_INOUT sPLCPacket_App_OKCancel &App_OKCancel,INT8U dir,INT8U okcancel,INT16U seq)//MSDU抄表结构的填充
{
	App_OKCancel.Msdu2017_head.s_Port=0x11;//变
	App_OKCancel.Msdu2017_head.s_Id=PLCAPP_ID_OK_CANCEL;//变
	App_OKCancel.Msdu2017_head.s_Con=0x00;
	App_OKCancel.u_ok_cancel_2.s_union_ok_cancel_2.s_pctver=1;
	App_OKCancel.u_ok_cancel_2.s_union_ok_cancel_2.s_dir=dir;
	App_OKCancel.u_ok_cancel_2.s_union_ok_cancel_2.s_headlen=4;
	App_OKCancel.u_ok_cancel_2.s_union_ok_cancel_2.s_okcancel=okcancel;//变
	App_OKCancel.u_ok_cancel_2.s_union_ok_cancel_2.s_secreserved=0;
    App_OKCancel.s_seq=seq;
	return 0;

}	
INT8U MSDU2017::Code_DownMsduFrame(TH_INOUT sPLCPacket_App_OKCancel &App_OKCancel)//MSDU抄表组帧
{
	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
    if(App_OKCancel.s_SendDataBuf != DBUFNULL)
    {			
		INT8U *ptempbuf = App_OKCancel.s_SendDataBuf;
		i=0;
		ptempbuf[i++] = App_OKCancel.Msdu2017_head.s_Port;      //
		ptempbuf[i++] = (INT8U)App_OKCancel.Msdu2017_head.s_Id;
		ptempbuf[i++] = App_OKCancel.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = App_OKCancel.Msdu2017_head.s_Con;		 

		for(INT8U m=0; m<2; m++)
		{
			ptempbuf[i++] = App_OKCancel.u_ok_cancel_2.s_union_ok_cancel2[m];
		}
		ptempbuf[i++] = (INT8U)App_OKCancel.s_seq;
		ptempbuf[i++] = (INT8U)App_OKCancel.s_seq>>8; 
		App_OKCancel.s_SendDataLen=App_OKCancel.u_ok_cancel_2.s_union_ok_cancel_2.s_headlen+4;
		ack = DACK_SUCESS;
	}
	return ack;

}
INT8U MSDU2017::Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_OKCancel &App_OKCancel)//加四字节完整性校验
{
	INT32U crc2=0x00000000;
    crc2=crc32(App_OKCancel.s_SendDataBuf,App_OKCancel.s_SendDataLen);
	if(App_OKCancel.s_SendDataBuf!=NULL){
	App_OKCancel.s_SendDataBuf[App_OKCancel.s_SendDataLen]=(INT8U)crc2;
	App_OKCancel.s_SendDataBuf[App_OKCancel.s_SendDataLen+1]=(INT8U)(crc2>>8);
	App_OKCancel.s_SendDataBuf[App_OKCancel.s_SendDataLen+2]=(INT8U)(crc2>>16);
	App_OKCancel.s_SendDataBuf[App_OKCancel.s_SendDataLen+3]=(INT8U)(crc2>>24);
	App_OKCancel.s_SendDataLen+=4;
	}
	return 0;
}
//****END****确认否认MSDU******//

//****START****通信测试MSDU******//
INT8U MSDU2017::Fill_App_Down_ConnectTest(TH_INOUT sPLCPacket_App_Down_ConnectTest &App_Down_ConnectTest,INT8U *OtherDataBuf,INT16U OtherDataBufLen,INT8U TYPE)//MSDU抄表结构的填充
{

	App_Down_ConnectTest.Msdu2017_head.s_Port=0x11;
	App_Down_ConnectTest.Msdu2017_head.s_Id=PLCAPP_ID_COMM_TEST;
	App_Down_ConnectTest.Msdu2017_head.s_Con=0x00;
	App_Down_ConnectTest.u_ConnectTest4.s_ConnectTest4.s_pctver=1;
	App_Down_ConnectTest.u_ConnectTest4.s_ConnectTest4.s_headlen=4;
	App_Down_ConnectTest.u_ConnectTest4.s_ConnectTest4.s_ack_flag=0;
	App_Down_ConnectTest.u_ConnectTest4.s_ConnectTest4.s_pcttype=TYPE;
	App_Down_ConnectTest.u_ConnectTest4.s_ConnectTest4.s_datalen=OtherDataBufLen;
	App_Down_ConnectTest.s_databuf=OtherDataBuf;//加数据域内容
	return 0;
}
INT8U MSDU2017::Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_ConnectTest &App_Down_ConnectTest)//MSDU抄表组帧
{
	INT16U i = 0;
	INT8U ack = DACK_ERR_BUF;
   if(App_Down_ConnectTest.s_SendDataBuf != DBUFNULL)
   {			
		INT8U *ptempbuf = App_Down_ConnectTest.s_SendDataBuf;
		i=0;
		ptempbuf[i++] = App_Down_ConnectTest.Msdu2017_head.s_Port;      //
		ptempbuf[i++] = (INT8U)App_Down_ConnectTest.Msdu2017_head.s_Id;
		ptempbuf[i++] = App_Down_ConnectTest.Msdu2017_head.s_Id>>8; 
		ptempbuf[i++] = App_Down_ConnectTest.Msdu2017_head.s_Con;		 

		for(INT8U m=0; m<4; m++)
		{
			ptempbuf[i++] = App_Down_ConnectTest.u_ConnectTest4.s_MSDUConnectTest4[m];
		}
		for(INT8U m=0; m<App_Down_ConnectTest.u_ConnectTest4.s_ConnectTest4.s_datalen; m++)
		{
			ptempbuf[i++] = App_Down_ConnectTest.s_databuf[m];
		}
		App_Down_ConnectTest.s_SendDataLen=App_Down_ConnectTest.u_ConnectTest4.s_ConnectTest4.s_headlen+App_Down_ConnectTest.u_ConnectTest4.s_ConnectTest4.s_datalen+4;
		ack = DACK_SUCESS;
	}
	return ack;
}
INT8U MSDU2017::Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_ConnectTest &App_Down_ConnectTest)//加四字节完整性校验
{
	INT32U crc2=0x00000000;
    crc2=crc32(App_Down_ConnectTest.s_SendDataBuf,App_Down_ConnectTest.s_SendDataLen);
	if(App_Down_ConnectTest.s_SendDataBuf!=NULL){
	App_Down_ConnectTest.s_SendDataBuf[App_Down_ConnectTest.s_SendDataLen]=(INT8U)crc2;
	App_Down_ConnectTest.s_SendDataBuf[App_Down_ConnectTest.s_SendDataLen+1]=(INT8U)(crc2>>8);
	App_Down_ConnectTest.s_SendDataBuf[App_Down_ConnectTest.s_SendDataLen+2]=(INT8U)(crc2>>16);
	App_Down_ConnectTest.s_SendDataBuf[App_Down_ConnectTest.s_SendDataLen+3]=(INT8U)(crc2>>24);
	App_Down_ConnectTest.s_SendDataLen+=4;
	}
	return 0;
}
//****END****通信测试MSDU******//



//**********************START*****MSDU的解帧*******************************//
INT8U Decode_Down_TranDataFrame(INT8U *DataBuf)//MSDU的解帧
{
	return 0;
}