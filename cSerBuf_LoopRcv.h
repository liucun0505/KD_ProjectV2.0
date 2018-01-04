/* 数据队列的配置 */
#ifndef _cSerBuf_LoopRcv_H
#define _cSerBuf_LoopRcv_H
#include "User_Mcu_Cfg.h"
#include "User_Ack_Def.h"
class cSerBuf_LoopRcv
{
  
  public:
//-------------------------------------------------------------------------------------------------------
// 函数名称: cSerBuf_LoopRcv(INT8U *rcvbuf,INT16U rcvlen);
// 功能描述: 构造函数
// 参数描述:
//     输　入: 
//        INT8U *rcvbuf：缓冲区的地址
//        INT16U rcvlen：缓冲区的长度
//     输　出: 
//   
// return : 无
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
     cSerBuf_LoopRcv(INT8U *rcvbuf,INT16U rcvlen);
	
	//-------------------------------------------------------------------------------------------------------
// 函数名称: InPutRcvByte(INT8U Data)
// 功能描述: 往缓冲区写一个字节数据，一般是中断调用
// 参数描述:
//     输　入: 
//        INT8U Data：数据
//      
//     输　出: 
//   
// return :  DACK_SUCESS，DACK_ERR_FULL
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
	 INT8U   InPutRcvByte(INT8U Data);
	 
	//-------------------------------------------------------------------------------------------------------
// 函数名称: InPutRcvByteInPutRcvNByte(const INT8U *vSrcBuf,INT16U vSrcLen)
// 功能描述: 往缓冲区写多个字节数据，一般是中断调用
// 参数描述:
//   输　入: 
//        INT8U *vSrcBuf：数据源
//        INT16U vSrcLen：数据个数
//   输　出: 
//   
// return :  DACK_SUCESS，DACK_ERR_FULL
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
   INT8U   InPutRcvNByte(const INT8U *vSrcBuf,INT16U vSrcLen);
	
	//-------------------------------------------------------------------------------------------------------
// 函数名称: QueRcvCnt(void)
// 功能描述: 查询接收到的数据长度。
// 参数描述:
//     输　入: 无
//        
//      
//     输　出: 无
//   
// return :   数据长度
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
   INT16U  QueRcvCnt();
	 
//-------------------------------------------------------------------------------------------------------
// 函数名称: QueueSizeRcvBuf(void)
// 功能描述: 查询缓冲区的最大长度
// 参数描述:
//     输　入: 无
//        
//      
//     输　出: 无
//   
// return :   最大长度
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//----------------------------------------------------------------------------------------------------
   INT16U  QueueSizeRcvBuf();
	 
//-------------------------------------------------------------------------------------------------------
// 函数名称: ClrRcvBuf(void)
// 功能描述: 清缓冲区
// 参数描述:
//     输　入: 无
//        
//      
//     输　出: 无
//   
// return :   无
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
   void ClrRcvBuf(void);
	 
//-------------------------------------------------------------------------------------------------------
// 函数名称: LoopReadRcvBufNByte(INT16U vSrcLen,INT8U *vDstBuf)
// 功能描述: 从接收缓冲区中，读数据。 缓冲区数据>=vSrcLen，返回vSrcLen个数据.
//           如果缓冲区数据<vSrcLen,返回缓冲区实际的数据个数。
// 参数描述:
//      输　入: 
//           INT16U vSrcLen:vDstBuf数据区最大长度
//           INT8U *vDstBuf : 数据区指针
//      输　出: 
//   
// return :  从接收缓冲区中，读到的数据长度
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------ 
	 INT16U LoopReadRcvBufNByte(INT16U vSrcLen,INT8U *vDstBuf);
	 
//-------------------------------------------------------------------------------------------------------
// 函数名称: INT8U *QueStartRcvBuf(void)
// 功能描述: 查询有数据的起始地址
// 参数描述:
//     输　入: 无
//        
//      
//     输　出: 无
//   
// return :   数据的起始地址
// 全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//------------------------------------------------------------------------------------------------------
 INT8U *QueStartRcvBuf(void);
 private:
    INT8U   *BufRcv;//接收缓冲BUF
    INT16U  m_BufRcvMaxData;//接收缓冲BUF的最大长度
    INT16U  m_RcvIn;//接收缓冲BUF的IN指针
    INT16U  m_RcvOut;//接收缓冲BUF的OUT指针
};

#endif

