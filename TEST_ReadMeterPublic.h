#pragma once



#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
class CTEST_ReadMeterPublic : public cDTL2007
{
	

public:


	void  StaSucessCnt(INT8U ack,INT8U &allSucesscnt,INT8U &failCnt);


protected:
		//-------------------------------------------------
	//���������ơ�   TestReadMeterLongFame(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType);
	//���������ܡ�   	��֡���ԣ�ʵ�ʱ�����ģ�����
	//������˵����        
	//��I:	���롿   vSrcCnt ������vSrcAfntype 0: AFN=0x02,F1,1:   AFN =13F1��vSrcMeterType �� 0ʵ��  1ģ��
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U  TestReadMeterLongFame(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType);
		//-------------------------------------------------
	//���������ơ�   INT8U  TestReadMeterErrDi(INT32U vSrcCnt,INT8U vSrcAfntype);
	//���������ܡ�    ����DI���ԣ�ʵ�ʱ�����ģ�����
	//������˵����        
	//��I:	���롿   vSrcCnt ������vSrcAfntype 0: AFN=0x02,F1,1:   AFN =13F1
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
    INT8U  TestReadMeterErrDi(INT32U vSrcCnt,INT8U vSrcAfntype);
	//-------------------------------------------------
	//���������ơ�   INT8U  TestReadMeterCnt(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType)
	//���������ܡ� ��δ�ת�����ԣ�ʵ�ʱ�����ģ�����
	//������˵����        
	//��I:	���롿   vSrcCnt ������vSrcAfntype 0: AFN=0x02,F1,1:   AFN =13F1��vSrcMeterType �� 0ʵ��  1ģ��
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
    INT8U  TestReadMeterCnt(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType);
	INT8U   TestSetPa(void);
		//-------------------------------------------------
	//���������ơ�  INT8U TestSeqNOAck645Di(INT32U vSrcCnt,INT8U Type)
	//���������ܡ�  SEQ���ԣ����������
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U TestSeqNONet(INT32U vSrcCnt,INT8U Type);
	//-------------------------------------------------
	//���������ơ�  INT8U TestSeqNOAck645Di(INT8U Type)
	//���������ܡ�  SEQ���ԣ������ɹ���STA NO�ظ�
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U  TestSeqNOAck645Di(INT8U Type);
	//-------------------------------------------------
	//���������ơ�  INT8U TestSeqAck645Di(INT8U Type)
	//���������ܡ�  SEQ���ԣ������ɹ���STA�лظ�
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U  TestSeqAck645Di(INT8U Type);
		//-------------------------------------------------
	//���������ơ�  INT8U TestSeqAck645ErrDi(INT32U vSrcCnt,INT8U Type)
	//���������ܡ�  �ظ�DI��һ�����ݣ�ģ�����
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U  TestSeqAck645ErrDi(INT32U vSrcCnt,INT8U Type);
		//-------------------------------------------------
	//���������ơ�  INT8U TestPartAckNo(INT8U Type)
	//���������ܡ�  �����ֻظ����ԡ�
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U TestPartAckNo(INT8U Type);
	//-------------------------------------------------
	//���������ơ�  INT8U TestIntevalTime(INT8U Type)
	//���������ܡ�  �ط����������ʱ�����
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	INT8U TestIntevalTime(INT8U Type);


	//-------------------------------------------------
	//���������ơ�  INT8U TestMoreReadMeterNoRcv(INT8U Type)
	//���������ܡ�  ������֡���ԣ��м��޽��գ���ʵ�ʱ�����ģ�����
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	 INT8U  TestMoreReadMeterNoRcv(INT8U Type);

	 	//-------------------------------------------------
	//���������ơ�  INT8U TestMoreReadMeterRcv(INT8U Type)
	//���������ܡ� ��֡���ԣ��м�Ҫ���գ���ʵ�ʱ�����ģ�����
	//������˵����        
	//��I:	���롿   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//��O:	�����    
	//������ֵ	��    
	//��ȫ�ֱ�����       
	//������˵����           
	//��������	��  ���  �����ڡ� 2016��6��28��
	//����  ������ ԭʼ�汾
	//-------------------------------------------------
	//���޸���	��     �����ڡ�
	//����  ������
	 INT8U  TestMoreReadMeterRcv(INT8U Type);
};

