
/*
	�����볣��
*/

#ifndef _VARIABLE
#define _VARIABLE
#include "header.h"

const int TIME_UNIT = 2;		 // ʱ�䵥λΪTIME_UNIT��
const int INIT_MONEY = 1000;	 // ��ʼ�ʽ�
const int HIRE_MONEY = 300;		 // ��ļһ������Ҫ���ʽ�
const int DEAD_TIME = 3;		 // ����DEAD_TIMEʱ�䵥λ�󣬱���Ϊ�ܵ�
const int FINE_FIRST_TIME = 30;  // ��ʱʱ�䣬��һ�γ�ʱ����
const int FINE_MONEY = 50;		 // ��һ�γ�ʱ������
const int FINE_SECOND_TIME = 60; // ��ʱʱ�䣬�ڶ��γ�ʱ����
const int MONEY_GAIN_ONE = 10;   // ���һ����õ�Ǯ
const int MAP_X = 17;			 // ��ͼX��С
const int MAP_Y = 17;			 // ��ͼY��С
const int COMPANY_X = 7;		 //��˾����X��С
const int COMPANY_Y = 8;		 //��˾����Y��С
const int HWID = 50;
const int RWID = 25;

/*
	��˾״̬����
	Ϊ����ȫ�ֳ�����ȫ�ֱ�������������ʾ
 */
int CompanyMoney = INIT_MONEY; // ��ǰ��˾�ж���Ǯ
int CompanyRiderCount = 0;	 // ��˾��������
int Time = -1;				   // ��ǰʱ�䣬��Time��ʱ�䵥λ
int CompanyOrderSum = 0;	   // ��˾�ӵ���
int CompanyOrderFinish = 0;	// ��˾��ɵ���
int CompanyOrderOverTime = 0;  // ��˾��ʱ����
int outputFlag = 0;			   // ���ֶ��������������
int isEnd = 0;				   // �Ƿ������������ 0����ʼֵ 1:������˳� 2�������������� 3���Ʋ� 4������ִ��

OrderList *AllOrderLog; // ȫ��������¼(����ͷ���)
OrderList *Buffer;		// ������(����ͷ���)
RiderList *AllRiderLog; // ȫ�����ּ�¼(����ͷ���)
int Map[17][17];		// ����ã�0Ϊ��·��1Ϊ��ͨ���ݣ�2Ϊ������3Ϊ���ᣬ4Ϊ���֣�-2Ϊͣ��������-3Ϊͣ������
#endif