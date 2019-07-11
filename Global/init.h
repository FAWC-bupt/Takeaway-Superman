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
	��ʼ��ͼ�ν����ͼ
*/
void updateMap()
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

	// ��ʼ����������
	OrderList *HeadOrder = AllOrderLog;
	HeadOrder = HeadOrder->Nxt_order;
	while (HeadOrder)
	{
		if (HeadOrder->Cur_order->status == 3 && HeadOrder->Cur_order->turn_time == Time && HeadOrder->Cur_order->end_time == Time)
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = -2; // ͣ������
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = -3;
		}
		else if (HeadOrder->Cur_order->status == 2 && HeadOrder->Cur_order->turn_time == Time)
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = -2; // ������ͼ����
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = 3;  // ͣ������
		}
		else if (HeadOrder->Cur_order->status == 3 && HeadOrder->Cur_order->end_time == Time)
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = 2;  // ������ͼ����
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = -3; // ͣ������
		}
		else if ((HeadOrder->Cur_order->status != 0 && HeadOrder->Cur_order->status != 3))
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = 2; // ������ͼ����
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = 3; // �����ͼ����
		}
		HeadOrder = HeadOrder->Nxt_order;
	}
	// ��ʼ������λ��
	RiderList *HeadRider = AllRiderLog;
	HeadRider = HeadRider->Nxt_rider;
	while (HeadRider)
	{
		//if (HeadRider->Cur_rider->Bag->Nxt_order)
		Map[HeadRider->Cur_rider->rider_x][HeadRider->Cur_rider->rider_y] = 4; // ���ֵ�ͼ����
		//HeadRider->Cur_rider->path_mode = predRiderPath(HeadRider->Cur_rider);
		HeadRider = HeadRider->Nxt_rider;
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
