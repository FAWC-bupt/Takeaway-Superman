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

int predRiderPath(Rider *nowRider)
{
	int pos_x = -1, pos_y = -1;
	int cur_x, cur_y;
	if (nowRider->Bag->Nxt_order && nowRider->Bag->Nxt_order->Cur_order->status == 1) //�ҵ�pos_x��pos_y�������������Ͱ����һ������;
	{
		pos_x = nowRider->Bag->Nxt_order->Cur_order->rest_x;
		pos_y = nowRider->Bag->Nxt_order->Cur_order->rest_y;
	}
	else if (nowRider->Bag->Nxt_order && nowRider->Bag->Nxt_order->Cur_order->status == 2)
	{
		pos_x = nowRider->Bag->Nxt_order->Cur_order->cust_x;
		pos_y = nowRider->Bag->Nxt_order->Cur_order->cust_y;
	}
	cur_y = nowRider->rider_y;
	cur_x = nowRider->rider_x;
	// ֹͣ״̬
	if (pos_x == -1 && pos_y == -1)
		return 6;
	// ������
	else if (cur_y < pos_y - 1 || cur_y > pos_y + 1)
	{
		if (cur_x % 2 == 1 && cur_y % 2 == 0) // �ں����·��
		{
			if (cur_y > pos_y + 1)		// ���ұ߾�Ҫ������
				return 3;				//��
			else if (cur_y < pos_y - 1) // �����Ҫ������
				return 0;				//��
		}
		else if (cur_x % 2 == 0 && cur_y % 2 == 1) // �������·��
		{
			if (cur_y > pos_y + 1) // ���ұ߾�Ҫ������
			{
				if (pos_x >= cur_x || (pos_x == cur_x && pos_x == 0)) // Ŀ�����»�ͬ��
					return 4;										  //����
				else												  // Ŀ������
					return 1;										  //����
			}
			else if (cur_y < pos_y + 1) // ���ұ߾�Ҫ������
			{
				if (pos_x > cur_x || (pos_x == cur_x && pos_x == 0)) // Ŀ�����»�ͬ��
					return 5;										 //����
				else												 // Ŀ������
					return 2;										 //����
			}
		}
	}
	// ������
	else if (cur_x < pos_x - 1 || cur_x > pos_x + 1)
	{
		if (cur_x % 2 == 0 && cur_y % 2 == 1) // �������·��
		{
			if (cur_x > pos_x + 1)		// ���±߾�Ҫ������
				return 0;				//��
			else if (cur_x < pos_x - 1) // ���ϱ�Ҫ������
				return 3;				//��
		}
		else if (cur_x % 2 == 1 && cur_y % 2 == 0) // �ں����·��
		{
			if (cur_x > pos_x + 1) // ���±߾�Ҫ������
			{
				if (pos_y > cur_y || (pos_y == cur_y && pos_y == 0)) // Ŀ�����һ�ͬ��
					return 1;										 //����
				else												 // Ŀ������
					return 4;										 //����
			}
			if (cur_x < pos_x + 1) // ���ϱ߾�Ҫ������
			{
				if (pos_y > cur_y || (pos_y == cur_y && pos_y == 0)) // Ŀ�����һ�ͬ��
					return 2;										 //����
				else												 // Ŀ������
					return 5;										 //����
			}
		}
	}
}

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
		if (HeadOrder->Cur_order->status == 2 && HeadOrder->Cur_order->end_time == Time)
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = -2; // ͣ������
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = 3;
		}
		else if (HeadOrder->Cur_order->status == 3 && HeadOrder->Cur_order->end_time == Time)
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_y] = 2;  // ������ͼ����
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_y] = -3; // ͣ������
		}
		else if ((HeadOrder->Cur_order->status != 0 && HeadOrder->Cur_order->status != 3) || (HeadOrder->Cur_order->status == 3 && HeadOrder->Cur_order->end_time == Time))
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
