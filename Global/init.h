#ifndef _INIT
#define _INIT
#include "header.h"

void initMap()
{
	int i, j;
	for (i = 0; i <= 16; i++)
	{
		for (j = 0; j <= 16; j++)
		{
			if ((i % 2) != (j % 2)) // ��ʼ����·
			{
				Map[i][j] = 0;
			}
			else
				Map[i][j] = 1; // ��ʼ������
		}
	}
}

/*
	��ʼ�����ֱ�������ʼ������ʱ���ֱ�������δ��ɶ���
 */
void initRiderBag()
{
	RiderList *rider = AllRiderLog->Nxt_rider;
	while (rider)
	{
		OrderList *order = rider->Cur_rider->Bag->Nxt_order;
		while (order)
		{
			if (order->Cur_order->status == 3) //��״̬Ϊ��ɵĶ���ɾ��
				order = delete_order(order);
			order = order->Nxt_order;
		}
		rider = rider->Nxt_rider;
	}
}
#endif
