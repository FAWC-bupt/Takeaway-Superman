#include "../Global/header.h"

/*
	ÿ��ˢ��ʱ�����ж��Ƿ��г�ʱ���������Ʋ��������Ϸ
*/
void isAnyOrderOverTime()
{
	OrderList *headOrder = AllOrderLog;
	headOrder = headOrder->Nxt_order;
	while (headOrder)
	{
		if (headOrder->Cur_order->status == 3)
		{
			headOrder = headOrder->Nxt_order;
			continue;
		} // ����������ɶ���

		int difference = Time - headOrder->Cur_order->begin_time;			  // ʱ���
		if (difference == DEAD_TIME + 1 && headOrder->Cur_order->status == 0) //�ܵ�
		{
			if (OutputFlag == 1)
				gameOver(1);
			else if (OutputFlag == 2)
				IsEnd = 4;
		}
		if (difference == FINE_SECOND_TIME + 1) // �����ϵ�
		{
			if (OutputFlag == 1)
				gameOver(2);
			else if (OutputFlag == 2)
				IsEnd = 3;
		}
		else if (difference == FINE_FIRST_TIME + 1) // ����,�ʽ�Ϊ��
		{
			CompanyMoney -= FINE_MONEY;
			CompanyOrderOverTime++;
			if (CompanyMoney < 0)
				if (OutputFlag == 1)
					gameOver(0);
				else if (OutputFlag == 2)
					IsEnd = 3;
		}
		headOrder = headOrder->Nxt_order;
	}
}
/*
	�������ʱ���ü���
	nowOrder(OrderList *)��Ŀǰ�������Ķ�����ע�⣬ΪOrderListָ�����Orderָ��
*/
OrderList *complishOrder(OrderList *nowOrder) // ����˳���ж���A������ɻ��������������
{
	OrderList *headOrder = AllOrderLog->Nxt_order;
	while (headOrder)
	{
		if (headOrder->Cur_order->id == nowOrder->Cur_order->id) // ����ȫ�ּ�¼�иö���״̬
		{
			if (nowOrder->Cur_order->status == 2) // TODO: ͣ����¼
			{
				headOrder->Cur_order->status = 3; // ��������
				nowOrder->Cur_order->status = 3;
				nowOrder->Cur_order->end_time = Time;
				headOrder->Cur_order->end_time = Time;
				//pop_front_order(nowOrder); // ������������
				CompanyOrderFinish++;
				if (Time - nowOrder->Cur_order->begin_time <= FINE_FIRST_TIME)
					CompanyMoney += MONEY_GAIN_ONE;
				return nowOrder;
			}
			else if (nowOrder->Cur_order->status == 1)
			{
				headOrder->Cur_order->status = 2;
				nowOrder->Cur_order->status = 2; // ����״̬���͵�
				nowOrder->Cur_order->turn_time = Time;
				headOrder->Cur_order->turn_time = Time;
				//OrderList *newOrder = nowOrder;
				Order *tOrder = nowOrder->Cur_order;
				push_back_order(tOrder, nowOrder);
				return delete_order(nowOrder);
			}
		}
		headOrder = headOrder->Nxt_order;
	}
}

/*
	�ж϶����Ƿ�ᵥ
	nowOrder(OrderList *)��Ŀǰ�������Ķ�����ע�⣬ΪOrderListָ�����Orderָ��
	NowRider(Rider *)��Ŀǰ�����֣�ע�⣬ΪRiderListָ��
 */
int isComplishOrder(OrderList *NowOrder, RiderList *NowRider)
{
	int judge = 0;
	if (NowOrder->Cur_order->status == 1)
		judge = abs((NowOrder->Cur_order->rest_x) - (NowRider->Cur_rider->rider_x)) + abs((NowOrder->Cur_order->rest_y) - (NowRider->Cur_rider->rider_y));
	else if (NowOrder->Cur_order->status == 2)
		judge = abs((NowOrder->Cur_order->cust_x) - (NowRider->Cur_rider->rider_x)) + abs((NowOrder->Cur_order->cust_y) - (NowRider->Cur_rider->rider_y));
	else
	{
		if (OutputFlag == 1)
			gameOver(3);
		else if (OutputFlag == 2)
			IsEnd = 3;
	}
	if (judge == 1)
		return 1;
	return 0;
}
/*
	���¶��������ɵ�
*/
void arrangeNewOrder()
{
	OrderList *newOrder = AllOrderLog->Nxt_order;
	while (newOrder)
	{
		if (newOrder->Cur_order->status == 0)
			getBestRider(newOrder->Cur_order);
		newOrder = newOrder->Nxt_order;
	}
}
