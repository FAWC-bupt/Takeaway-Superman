#include "../Global/header.h"

/*
	��ļ����,�������ֵ�id��ע�⣬ǰ��������CompanyMoney>=400
	return(int):���ֵ�id
 */
int hireRider()
{
	CompanyMoney -= 300; // ��Ǯ
	CompanyRiderCount++; // ����������
	Rider* newRider = (Rider*)malloc(sizeof(Rider));
	// ��ʼ��������
	newRider->id = CompanyRiderCount - 1;
	newRider->rider_x = COMPANY_X;
	newRider->rider_y = COMPANY_Y;
	newRider->Bag = creatOrderList(); // ���ֵı�����һ����������
	newRider->path_mode = 6;
	//����������ӵ������б�
	push_back_rider(newRider, AllRiderLog);
	return newRider->id;
}
/*
	��������id����Orderָ��
	int rider_id:����id
	return(Order *):���ֵ�ǰ������ָ��
 */
Order* getRiderCurOrder(int rider_id)
{
	RiderList* p = AllRiderLog;
	while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
		p = p->Nxt_rider;
	return p->Cur_rider->Bag->Cur_order;
}
/*
	��������id����OrderListָ��
	int rider_id:����id
	return(OrderList *):���ֵ�ǰ������ָ��
 */
OrderList* getRiderCurBag(int rider_id)
{
	RiderList* p = AllRiderLog;
	while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
		p = p->Nxt_rider;
	return p->Cur_rider->Bag;
}

/*
	��������λ�ã�ע�⴫�������Ϊָ��
	int rider_id:����id
	int *x:���ֺ�����ָ��
	int *y:����������ָ��
 */
void getRiderCurPos(int rider_id, int* x, int* y)
{
	RiderList* p = AllRiderLog;
	while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
		p = p->Nxt_rider;
	*x = p->Cur_rider->rider_x;
	*y = p->Cur_rider->rider_y;
}
/*
	��������id��Ŀ�ĵأ��������꣩���������ֵ�ǰλ�ã������ң������£��ƶ�һ����λ��Ĭ���Ѿ��ж��Ƿ�ͣ�����������¼��
	int rider_id:����id
	int pos_x:Ŀ�ĵغ�����
	int pos_y:Ŀ�ĵ�������
 */
void riderMove(int rider_id, int pos_x, int pos_y)
{
	int* cur_x, * cur_y, i, j;
	RiderList* p = AllRiderLog->Nxt_rider;
	while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
		p = p->Nxt_rider;
	cur_x = &(p->Cur_rider->rider_x);
	cur_y = &(p->Cur_rider->rider_y);
	i = *cur_x;
	j = *cur_y;
	// TODO: �����ƶ���Ԫ
	// ������
	if (*cur_y < pos_y - 1 || *cur_y > pos_y + 1)
	{
		if (i % 2 == 1 && j % 2 == 0) // �ں����·��
		{
			if (*cur_y > pos_y + 1) // ���ұ߾�Ҫ������
				(*cur_y) -= 2;
			else if (*cur_y < pos_y - 1) // �����Ҫ������
				(*cur_y) += 2;
		}
		else if (i % 2 == 0 && j % 2 == 1) // �������·��
		{
			if (*cur_y > pos_y + 1) // ���ұ߾�Ҫ������
			{
				if (pos_x > *cur_x || (pos_x == *cur_x && pos_x == 0)) // Ŀ�����»�ͬ��
				{
					(*cur_x)++;
					(*cur_y)--;
				}
				else // Ŀ������
				{
					(*cur_x)--;
					(*cur_y)--;
				}
			}
			else if (*cur_y < pos_y + 1) // ����߾�Ҫ������
			{
				if (pos_x > *cur_x || (pos_x == *cur_x && pos_x == 0)) // Ŀ�����»�ͬ��
				{
					(*cur_x)++;
					(*cur_y)++;
				}
				else// Ŀ������
				{
					(*cur_x)--;
					(*cur_y)++;
				}
			}
		}
		else // �쳣�������
		{
			// // TODO: ������ֹ������
			// printf("զ�����ܵ��������ˣ�\n");
			// //exit(0);
			gameOver(5);
		}
	}
	// ������
	else if (i < pos_x - 1 || i > pos_x + 1)
	{
		if (i % 2 == 0 && j % 2 == 1) // �������·��
		{
			if (*cur_x > pos_x + 1) // ���±߾�Ҫ������
				(*cur_x) -= 2;
			else if (*cur_x < pos_x - 1) // ���ϱ�Ҫ������
				(*cur_x) += 2;
		}
		else if (i % 2 == 1 && j % 2 == 0) // �ں����·��
		{
			if (*cur_x > pos_x + 1) // ���±߾�Ҫ������
			{
				if (pos_y > * cur_y || (pos_y == *cur_y && pos_y == 0)) // Ŀ�����һ�ͬ��
				{
					(*cur_y)++;
					(*cur_x)--;
				}
				else  // Ŀ������
				{
					(*cur_y)--;
					(*cur_x)--;
				}
			}
			if (*cur_x < pos_x + 1) // ���ϱ߾�Ҫ������
			{
				if (pos_y > * cur_y || (pos_y == *cur_y && pos_y == 0)) // Ŀ�����һ�ͬ��
				{
					(*cur_y)++;
					(*cur_x)++;
				}
				else // Ŀ������
				{
					(*cur_y)--;
					(*cur_x)++;
				}
			}
		}
		else // �쳣�������
			// // TODO: ������ֹ������
			// printf("զ�����ܵ��������ˣ�\n");
			// //exit(0);
			gameOver(5);
	}
}

/*
	�������ֽ����ƶ�����Ϊ��������һ���֣��޲����ͷ���ֵ
	Ŀǰ�Ĳ������ɱ�����ĵ�һ����
 */
void AllRiderMove()
{
	RiderList* tempRider = AllRiderLog->Nxt_rider;
	while (tempRider)
	{
		int posX, posY;
		OrderList* findOrder = tempRider->Cur_rider->Bag->Nxt_order; //�ҵ������һ������
		if (findOrder)
		{
			if (findOrder->Cur_order->status == 1) //�ҵ���һ��������Ӧ��λ��
			{
				posX = findOrder->Cur_order->rest_x;
				posY = findOrder->Cur_order->rest_y;
			}
			else if (findOrder->Cur_order->status == 2)
			{
				posX = findOrder->Cur_order->cust_x;
				posY = findOrder->Cur_order->cust_y;
			}
			riderMove(tempRider->Cur_rider->id, posX, posY); //�����ƶ�
		}
		tempRider = tempRider->Nxt_rider; //������һ������
	}
}