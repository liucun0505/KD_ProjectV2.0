#ifndef _MSDU2017_H
#define _MSDU2017_H
#define MACADDR_LEN 6
#define MSDU2017_MAXSENDBUFLEN 2048
#include "Tools.h"
#include "MainFrm.h"
#include "cSerBuf_LoopRcv.h"
typedef enum 
{
	PLCAPP_ID_POINT_TRANSMIT = 0x0001,                  // 集中器主动

	PLCAPP_ID_ROUND_TRANSMIT = 0x0002,                  // 路由主动
	PLCAPP_ID_PARALLEL_TRANSMIT = 0x0003,               //并发读表 
	PLCAPP_ID_TIMING = 0x0004,                          //广播数据转发命令   校时报文????
	PLCAPP_ID_COMM_TEST = 0x0006,                       //通信测试报文
	PLCAPP_ID_EVENT_REPORT = 0x0008,                    //事件报文	
	PLCAPP_ID_GET_METERLIST = 0x0011,                   //查询从节点注册结果
	PLCAPP_ID_SEARCH_START = 0x0012,                    //启动从节点主动注册: 开始搜表
	PLCAPP_ID_SEARCH_STOP = 0x0013,                     // 停止从节点注册:     停止搜表

	PLCAPP_ID_OK_CANCEL = 0x0020,                       //swcol
	PLCAPP_ID_COLLECT_TRANSMIT = 0x0021,                //swcol

	PLCAPP_ID_FTP_START = 0x0030,                       // 开始升级 	
	PLCAPP_ID_FTP_STOP = 0x0031,                        // 停止升级
	PLCAPP_ID_FTP_TRANSFER = 0x0032,                    // 传输文件数据
	PLCAPP_ID_FTP_LC_TRANSFER = 0x0033,                 // 传输文件数据(单播转本地广播)
	PLCAPP_ID_FTP_GET_STATUS = 0x0034,                  // 查询站点升级状态
	PLCAPP_ID_FTP_EXEC = 0x0035,                        // 执行升级
	PLCAPP_ID_FTP_GET_STAINFO = 0x0036,                 // 查询站点信息

	PLCAPP_ID_AUTH = 0x00a0,                            //鉴权安全

	//扩展命令
	PLCAPP_ID_EXTEND = 0x00f0                           //扩展命令
} ePLCAPP_ID_TYPE;

//MAC层帧头格式
typedef struct
{
	INT16U          s_macver        : 4;                //协议版本号 0
	INT16U          s_ckqtei        : 12;               //原始源TEI  抄控器的tei？ 80 3F
	INT16U          s_nodetei       : 12;               //原始目的TEI sta的tei FF 2F
	INT16U          s_mactype       : 4;                //发送类型 0单播 1全网广播 2本地广播 3代理广播 2
	INT8U           s_macnum        : 5;                //发送次数限值 一般是1  01 
	INT8U           s_macbaoliu      : 3;               //保留
} MacHead_first_5;//80 3F FF 2F 01 


typedef struct
{
	INT16U          s_msdulen       : 11;                //MSDU 长度 
	INT16U          s_rebootnum     : 4;                 //重启次数
	INT16U          s_dailujing      : 1;                //代理主路径标识 0未启用代理主路径模式
	INT8U           s_macrote_n     : 4;               //路由总跳数
	INT8U           s_macrote_sn       : 4;                //路由剩余跳数
	INT16U           s_macgbfx       : 2;               //广播方向 0双向 1 下行广播（从CCO发起广播至STA）2与1相反
	INT16U           s_ljxfbz       : 1;               //路径修复标志 0 当前报文未触发过路径修复 1相反
	INT16U           s_macbz      : 1;               //MAC地址标志 0未携带MAC地址  1相反
	INT16U           s_macbaoliu      : 12;               //保留
} MacHead_secend_5;//04 28 00 08 00

typedef struct
{
	INT8U      s_MacHeadDataBuf[30];//整MAC帧头数据
	INT16U     s_MacHeadDataLen;//整MAC帧头长度。
	union
	{
		MacHead_first_5   MacHead_first5;
		INT8U  s_MacHead_first[5];
	} u_MacHead_first_5;
	INT16U  msduNum;  //MSDU 序列号 DF 01
	INT8U   msdutype;//MSDU 类型 添了30,代表应用层报文48
	union
	{
		MacHead_secend_5   MacHead_secend5;
		INT8U  s_MacHead_secend[5];
	} u_MacHead_secend_5;
	INT8U   netnum;//组网序列号
	INT8U   bl1;//保留
	INT8U   bl2;//保留
	INT8U    s_macadd[6]; //原始源MAC地址
	INT8U    s_mactoadd[6]; //原始目的MAC地址
} MacHead;



//***************************MSDU结构体，开始*********************************
//Msdu应用层头格式
typedef struct
{
	INT8U		s_Port;									//报文端口号
	INT16U		s_Id;									//报文ID
	INT8U		s_Con;									//报文控制字
} MsduHead;


typedef struct 
{
	INT16U          s_pctver        : 6;                //协议版本号
	INT16U          s_headlen       : 6;                //报文头长度
	INT16U          s_reserved      : 4;                //保留
	INT16U          s_pcttype       : 4;                //转发数据的规约类型
	INT16U          s_datalen       : 12;               //转发数据长度
} sMSDU_TranData_DOWNHEAD4;// 抄表下行应用数据帧头前四个字节


typedef struct 
{
	INT16U          s_pctver        : 6;                //协议版本号
	INT16U          s_headlen       : 6;                //报文头长度
	INT16U          s_ack_flag      : 4;                //应答状态
	INT16U          s_pcttype       : 4;                //转发数据的规约类型
	INT16U          s_datalen       : 12;               //转发数据长度
} sMSDU_TranData_UPHEAD4;// 抄表上行应用数据帧头前四个字节

//应用层——数据传输帧头格式，应用于点抄，轮抄，并发，下行
typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
    MsduHead   Msdu2017_head;
	union
	{
		sMSDU_TranData_DOWNHEAD4   s_DownHead4;
		INT8U  s_MSDUDownHead4[4];
	} u_TranDataDownHead4;
	INT16U          s_seq;                              //报文序号
	INT8U           s_timeout;                          //电能表超时时间
	INT8U           s_select;                           //选项字
	INT8U *         s_databuf;                          //发送的数据源
} sPLCPacket_App_Down_TranData;


//应用层——数据传输帧头格式，应用于点抄，轮抄，并发，上行
typedef struct 
{
    MsduHead   Msdu2017_head;
	union
	{
		sMSDU_TranData_UPHEAD4    s_UpHead4;
		INT8U  s_MSDUUpHead4[4];
	} u_TranDataUpHead4;
	INT16U          s_seq;                              //报文序号
	INT16U          s_select;                           //选项字
	INT8U *         s_databuf;                          //接收的数据源
} sPLCPacket_App_Up_TranData;



//////////////////////******************MSDU包376.2下行*****************************////////////////////////////
typedef struct 
{
	INT16U          s_pctver        : 6;                //协议版本号
	INT16U          s_headlen       : 6;                //报文头长度
	INT16U          s_reserved      : 4;                //保留
} union_Down_13762;//


typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_13762    s_Down13762_2;
		INT8U  s_Down13762[2];
	} u_DataDown_13762_2;
	//INT16U          s_KID;                              //内部扩展ID
	INT16U          s_3762datalen;                       //报文长度
	INT16U          s_seq;                              //报文序号
	INT8U *         s_3762databuf;                       //376.2数据
} sPLCPacket_App_Down_13762;

/////////////////////***********************************************////////////////////////////


















//启动从节点注册，下行
typedef struct 
{
MsduHead   Msdu2017_head;
INT16U          s_pctver        : 6;                //协议版本号
INT16U          s_headlen       : 6;                //报文头长度
INT16U          s_forceackfg    : 1;                //强制应答标志
INT16U          s_regpa         : 3;                //从节点注册参数
INT16U          s_reserved;                         //保留
INT32U          s_seq;                              //报文序号
} sPLCPacket_App_Down_EnableRegMsg;


//查询从节点注册结果报文格式说明，下行
typedef struct 
{
MsduHead   Msdu2017_head;
INT16U          s_pctver        : 6;                //协议版本号
INT16U          s_headlen       : 6;                //报文头长度
INT16U          s_forceackfg    : 1;                //强制应答标志
INT16U          s_regpa         : 3;                //从节点注册参数
INT16U          s_reserved;                         //保留
INT32U          s_seq;                              //报文序号
} sPLCPacket_App_Down_GetRegMsg;


//该结构体可与数组强制转换
typedef struct 
{
INT8U           s_staadd[6];                        //电能表地址
INT8U           s_pcttype;                          //规约类型
INT8U           s_devicetype    : 4;                //模块类型
INT8U           s_secreserved   : 4;                // 保留
} sRegNodeMsg;


//查询从节点注册结果报文格式说明，上行
typedef struct 
{
MsduHead   Msdu2017_head;
INT16U          s_pctver        : 6;                //协议版本号
INT16U          s_headlen       : 6;                //报文头长度
INT16U          s_status        : 1;                //状态字段，如果STA正在搜表时，接收到CCO下发的查询从节点注册结果命令且下行报文中的强制应答状态为强制应答时，

//将该状态位置为1；如STA已搜表完成，接收到CCO下发的查询从节点注册结果命令时，将该状态位置为0。
INT16U          s_regpa         : 3;                //从节点注册参数
INT8U           s_meter_num;                        //电表数量
INT8U           s_type;                             //0:电表 1:采集器
INT8U           s_deviceadd[MACADDR_LEN];           //设备地址，采集器或电表地址
INT8U           s_idBuf[MACADDR_LEN];               //设备ID
INT32U          s_seq;                              //报文序号
INT32U          s_reserved;                         //保留
INT8U           s_DevMacAddr[MACADDR_LEN];          //源(节点)MAC地址
INT8U           s_DestMacAddr[MACADDR_LEN];         //目的MAC地址
INT16U          s_DataLen;                          //数据长度
INT8U *         s_DataBuf;                          //数据区
} sPLCPacket_App_Up_GetRegMsg;


//停止从节点注册，下行
typedef struct 
{
MsduHead   Msdu2017_head;
INT16U          s_pctver        : 6;                //协议版本号
INT16U          s_headlen       : 6;                //报文头长度
INT16U          s_reserved      : 4;                //保留
INT16U          s_secreserved;                      //保留
INT32U          s_seq;                              //报文序号
} sPLCPacket_App_Down_StopRegMsg;


////////////////////////////////确认/否认，上下行//////////////////////////////////////////////////////

typedef struct 
{
	INT8U          s_pctver        : 6;                //协议版本号
	INT8U          s_headlen       : 6;                //报文头长度
	INT8U          s_dir           : 1;                //方向位 0=下行方向,1=上行方向
	INT8U          s_okcancel      : 1;                //确认位 0=否认,1=确认
	INT16U          s_secreserved   : 2;                //保留
} union_ok_cancel2;//

typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
	MsduHead   Msdu2017_head;
	union
	{
		union_ok_cancel2    s_union_ok_cancel_2;
		INT8U  s_union_ok_cancel2[2];
	} u_ok_cancel_2;
	INT16U          s_seq;                              //报文序号
} sPLCPacket_App_OKCancel;

////////////////////////////////////////////END///////////////////////////////////////////////////////////

//校时报文，下行
typedef struct 
{
MsduHead   Msdu2017_head;
INT16U          s_pctver        : 6;                //协议版本号
INT16U          s_headlen       : 6;                //报文头长度
INT16U          s_reserved      : 4;                //保留
INT16U          s_secreserved   : 4;                //保留
INT16U          s_datalen       : 12;               //数据长度
INT8U *         s_databuf;                          //数据
} sPLCPacket_App_Down_AdjustTime;


//事件，上行
typedef struct 
{
MsduHead   Msdu2017_head;
INT32U          s_pctver        : 6;                //协议版本号
INT32U          s_headlen       : 6;                //报文头长度
INT32U          s_dir           : 1;                //方向位
INT32U          s_start         : 1;                //启动位
INT32U          s_function      : 6;                //功能码
INT32U          s_datalen       : 12;               //数据长度
INT16U          s_seq;                              //报文序号
INT8U           s_staadd[MACADDR_LEN];              //电能表地址
INT8U *         s_databuf;                          //数据
} sPLCPacket_App_Up_Event;


//事件，下行
typedef struct 
{
MsduHead   Msdu2017_head;
INT32U          s_pctver        : 6;                //协议版本号
INT32U          s_headlen       : 6;                //报文头长度
INT32U          s_dir           : 1;                //方向位
INT32U          s_start         : 1;                //启动位
INT32U          s_function      : 6;                //功能码
INT32U          s_datalen       : 12;               //数据长度
INT16U          s_seq;                              //报文序号
INT8U           s_staadd[MACADDR_LEN];              //电能表地址，据协议下行中没用
INT8U *         s_databuf;                          //数据
} sPLCPacket_App_Down_Event;


/////////////////////////////////////////通信测试，下行//////////////////////////////////////////////////////////////

typedef struct 
{
	INT16U          s_pctver        : 6;                //协议版本号
	INT16U          s_headlen       : 6;                //报文头长度
	INT16U          s_ack_flag      : 4;                //保留
	INT16U          s_pcttype       : 4;                //转发数据的规约类型//0 透明传输 1 DL/T645—1997 2 DL/T645—2007 3 DLT698.45
	INT16U          s_datalen       : 12;               //转发数据长度
} sMSDU_ConnectTest4;// 通信测试所用的四个字节

typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
	MsduHead   Msdu2017_head;
	union
	{
		sMSDU_ConnectTest4   s_ConnectTest4;
		INT8U  s_MSDUConnectTest4[4];
	} u_ConnectTest4;
	INT8U *         s_databuf;                          //数据
} sPLCPacket_App_Down_ConnectTest;

///////////////////////////////////////END//////////////////////////////////////////////////////////

//FTP 开始升级，下行

typedef struct 
{
INT32U          s_pctver        : 6;                //协议版本号
INT32U          s_headlen       : 6;                //报文头长度
INT32U          s_reserved      : 20;               //保留
} union_Down_FTPStart;

typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPStart    s_DownFTP4;
		INT8U  s_MSDUFDownFTP4[4];
	} u_DataDownFTP4START;
	INT32U          s_ftpID;                            //升级ID
	INT16U          s_window;                           //升级时间窗
	INT16U          s_blksize;                          //升级块大小
	INT32U          s_filesize;                         //升级文件大小
	INT32U          s_fileCRC;                          //文件校验 
} sPLCPacket_App_Down_FTPStart;

//FTP 开始升级，上行应答

typedef struct 
{
	INT32U          s_pctver        : 6;                //协议版本号
	INT32U          s_headlen       : 6;                //报文头长度
	INT32U          s_reserved      : 12;               //保留
	INT32U          s_result        : 8;                //升级结果码
} union_Up_FTPStart;

typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
    MsduHead   Msdu2017_head;
	union
	{
		union_Up_FTPStart    s_UpFTP4;
		INT8U  s_MSDUFUpFTP4[4];
	} u_DataUpFTP4START;

	INT32U          s_ftpID;                            //升级ID
} sPLCPacket_App_Up_FTPStart;


//FTP 停止升级，下行
typedef struct 
{

	INT32U          s_pctver        : 6;                //协议版本号
	INT32U          s_headlen       : 6;                //报文头长度
	INT32U          s_reserved      : 20;               //保留

} union_Down_FTPStop;

typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPStop    s_DownFTP4;
		INT8U  s_MSDUFDownFTP4[4];
	} u_DataDownFTP4STOP;

	INT32U          s_ftpID;                            //升级ID
} sPLCPacket_App_Down_FTPStop;


//FTP 文件传输，下行
typedef struct 
{
	INT16U          s_pctver        : 6;                //协议版本号
	INT16U          s_headlen       : 6;                //报文头长度
	INT16U          s_reserved      : 4;                //保留    
} union_Down_FTPTransfile;
typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPTransfile    s_DownFTPTransfile2;
		INT8U  s_DownFTPFile[2];
	} u_DataDownFTPTransfile;

	INT16U          s_blksize;                          //数据块大小
	INT32U          s_ftpID;                            //升级ID
	INT32U          s_blkno;                            //数据块编号
	INT8U *         s_DataBuf;                          //数据       
} sPLCPacket_App_Down_FTPTransfile;


//FTP 查询站点升级状态，下行

typedef struct 
{

	INT16U          s_pctver        : 6;                //协议版本号
	INT16U          s_headlen       : 6;                //报文头长度
	INT16U          s_reserved      : 4;                //保留
} union_Down_FTPGetStatus;
typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPGetStatus    s_DownFTPGetStatus2;
		INT8U  s_DownFTPStatus[2];
	} u_DataDownFTPGetStatus;

	INT16U          s_blknum;                           //数据块数
	INT32U          s_startno;                          //起始数据块编号    
	INT32U          s_ftpID;                            //升级ID
} sPLCPacket_App_Down_FTPGetStatus;


//FTP 查询站点升级状态，上行
typedef struct 
{

	INT16U          s_pctver        : 6;                //协议版本号
	INT16U          s_headlen       : 6;                //报文头长度
	INT16U          s_status        : 4;                //保留

} union_Up_FTPGetStatus;
typedef struct 
{
    MsduHead   Msdu2017_head;
	union
	{
		union_Up_FTPGetStatus    s_UpFTPGetStatus2;
		INT8U  s_UpFTPStatus[2];
	} u_DataUpFTPGetStatus;

	INT16U          s_blknum;                           //数据块数
	INT32U          s_startno;                          //起始数据块编号    
	INT32U          s_ftpID;                            //升级ID
	INT8U *         s_DataBuf;                          //位图
} sPLCPacket_App_Up_FTPGetStatus;


//FTP 执行升级，下行
typedef struct 
{

	INT16U          s_pctver        : 6;                //协议版本号
	INT16U          s_headlen       : 6;                //报文头长度
	INT16U          s_reserved      : 4;                //保留

} union_Down_FTPExec;
typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPExec    s_DoFTPFTPExec2;
		INT8U  s_DownFTPExec[2];
	} u_DataDownFTPExec;

	INT16U          s_waitsec;                          //等待复位时间
	INT32U          s_ftpID;                            //升级ID    
	INT32U          s_trysec;                           //试运行时间
} sPLCPacket_App_Down_FTPExec;


//FTP 查询站点信息，下行
typedef struct 
{
	INT16U          s_pctver        : 6;                //协议版本号
	INT16U          s_headlen       : 6;                //报文头长度
	INT16U          s_reserved      : 12;                //保留
   
} union_Down_FTPGetInfo;
typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//整帧MSDU数据
	INT16U     s_SendDataLen;//整帧MSDU长度。
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPGetInfo    s_DoFTPGetInfo3;
		INT8U  s_DownFTPGetInfo[3];
	} u_DataDownFTPGetInfo;

	INT8U           s_infonum;                          //信息列表元素个数
	INT8U *         s_infoDataBuf;                          //数据    
} sPLCPacket_App_Down_FTPGetInfo;


//FTP 查询站点信息，上行
typedef struct 
{
	INT32U          s_pctver        : 6;                //协议版本号
	INT32U          s_headlen       : 6;                //报文头长度
	INT32U          s_reserved      : 12;               //保留
	INT32U          s_infonum       : 8;                //信息列表元素个数
} union_Up_FTPGetInfo;
typedef struct 
{
    MsduHead   Msdu2017_head;
	union
	{
		union_Up_FTPGetInfo    s_UpFTPGetInfo4;
		INT8U  s_UpFTPGetInfo[4];
	} u_DataUpFTPGetInfo;
	INT32U          s_ftpID;                            //升级ID        
	INT8U *         s_DataBuf;                          //数据    
} sPLCPacket_App_Up_FTPGetInfo;


//扩展
typedef struct 
{
INT8U           s_Port;                             //报文端口号
INT16U          s_Id;                               //报文ID
INT8U           s_Con;                              //报文控制字
INT16U          s_pctver        : 6;                //协议版本号
INT16U          s_headlen       : 6;                //报文头长度
INT16U          s_reserved      : 4;                //保留
INT16U          s_ExtendId;                         //扩展ID
INT16U          s_DataLen;                          //接收数据的个数
INT16U          s_seq;                              //报文序号
INT8U *         s_DataBuf;                          //接收数据区指针，高危指针，用前要检查是否有值，要指向合法空间
} sPLCPacket_App_Down_Extend;

class MSDU2017
{
public:
	MSDU2017(void);
	~MSDU2017(void);

	//**** 组MSDU的MAC帧头******//
	INT8U Fill_MacHeadStuct(TH_INOUT MacHead &Down_MacHeadForMsdu,INT16U msdulen,INT8U msdutype,INT16U msduseq,INT8U *y_mac,INT8U *to_mac,INT16U y_tei,INT16U to_tei,INT8U sendtype,INT8U macbz);//先组MSDU帧再组MAC帧头结构
	INT8U Code_MacHeadForMsdu(TH_INOUT MacHead &Down_MacHeadForMsdu);//组MAC帧头数据


	//****抄表MSDU******//
	INT8U Fill_Down_TranDataFrame(TH_INOUT sPLCPacket_App_Down_TranData &Down_TranDataCreatFrame,INT8U *OtherDataBuf,INT16U OtherDataBufLen,INT8U TYPE);//MSDU抄表结构的填充
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_TranData &Down_TranDataCreatFrame);//MSDU抄表组帧
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_TranData &Down_TranDataCreatFrame);//加四字节完整性校验

	//**********//
	//****转发376.2MSDU******//
	INT8U Fill_DownMSDU_13762Frame(TH_INOUT sPLCPacket_App_Down_13762 &Down_13762CreatFrame,INT8U *s_13762DataBuf,INT16U s_13762DataBufLen);//MSDU包13762结构的填充
	INT8U Code_DownMSDU_13762Frame(TH_INOUT sPLCPacket_App_Down_13762 &Down_13762CreatFrame);//MSDU包13762组帧
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_13762 &Down_13762CreatFrame);//加四字节完整性校验
	//**********//
	//**********//

/****************升级所用MSDU*********************/
	//*****开始升级*****//
	INT8U Fill_sPLCPacket_App_Down_FTPStart(TH_INOUT sPLCPacket_App_Down_FTPStart &Down_FTPStartCreatFrame,INT16U windowTime,INT16U blksize,INT32U filesize,INT32U fileCRC);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPStart &Down_FTPStartCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPStart &Down_FTPStartCreatFrame);//加四字节完整性校验

	//****停止升级MSDU******//
	INT8U Fill_sPLCPacket_App_Down_FTPStop(TH_INOUT sPLCPacket_App_Down_FTPStop &Down_FTPStopCreatFrame,INT32U UPID);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPStop &Down_FTPStopCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPStop &Down_FTPStopCreatFrame);//加四字节完整性校验

	//*****文件传输MSDU*****//
	INT8U Fill_sPLCPacket_App_Down_FTPTransfile(TH_INOUT sPLCPacket_App_Down_FTPTransfile &Down_FTPTransfileCreatFrame,INT16U blksize,INT32U UPID,INT32U blkno,INT8U *s_FileDataBuf);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPTransfile &Down_FTPTransfileCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPTransfile &Down_FTPTransfileCreatFrame);//加四字节完整性校验

	//*****查询站点升级状态MSDU*****//

	INT8U Fill_sPLCPacket_App_Down_FTPGetStatus(TH_INOUT sPLCPacket_App_Down_FTPGetStatus &Down_FTPGetStatusCreatFrame,INT16U s_blknum,INT32U s_startno,INT32U s_ftpID);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPGetStatus &Down_FTPGetStatusCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPGetStatus &Down_FTPGetStatusCreatFrame);//加四字节完整性校验

	//*****执行升级MSDU*****//

	INT8U Fill_sPLCPacket_App_Down_FTPExec(TH_INOUT sPLCPacket_App_Down_FTPExec &Down_FTPExecCreatFrame,INT8U *OtherDataBuf,INT16U OtherDataBufLen,INT8U TYPE);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPExec &Down_FTPExecCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPExec &Down_FTPExecCreatFrame);//加四字节完整性校验

	//*****查询站点信息MSDU*****//
	//INT8U infonum;                          //信息列表元素个数
	//INT8U *infoDataBuf;                          //数据  
	INT8U Fill_sPLCPacket_App_Down_FTPGetInfo(TH_INOUT sPLCPacket_App_Down_FTPGetInfo &Down_FTPGetInfoCreatFrame,INT8U infonum,INT8U *infoDataBuf);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPGetInfo &Down_FTPGetInfoCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPGetInfo &Down_FTPGetInfoCreatFrame);//加四字节完整性校验

/*******************************************/	
		//****确认否认MSDU******//
	INT8U Fill_App_OKCancel(TH_INOUT sPLCPacket_App_OKCancel &App_OKCancel,INT8U dir,INT8U okcancel,INT16U seq);//MSDU抄表结构的填充
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_OKCancel &App_OKCancel);//MSDU抄表组帧
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_OKCancel &App_OKCancel);//加四字节完整性校验
/*********************************************/

/*******************************************/	
		//****通信测试MSDU******//
	INT8U Fill_App_Down_ConnectTest(TH_INOUT sPLCPacket_App_Down_ConnectTest &App_Down_ConnectTest,INT8U *OtherDataBuf,INT16U OtherDataBufLen,INT8U TYPE);//MSDU抄表结构的填充
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_ConnectTest &App_Down_ConnectTest);//MSDU抄表组帧
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_ConnectTest &App_Down_ConnectTest);//加四字节完整性校验
/*********************************************/


	///////////////////MSDU解析///////////////////////////
	INT8U Decode_Down_TranDataFrame(INT8U *DataBuf);//MSDU的解帧



};
#endif

