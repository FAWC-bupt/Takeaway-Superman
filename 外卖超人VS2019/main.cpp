
#include "../Global/header.h"

int main()
{
	AllOrderLog = creatOrderList(); // ȫ��������¼(����ͷ���)
	Buffer = creatOrderList();      // ������(����ͷ���)
	AllRiderLog = creatRiderList(); // ȫ�����ּ�¼(����ͷ���)
	clock_t start_clock, end_clock; // ���ڼ����������ʱ��
	if (inputFileOrder())
		;
	else
		inputKeyOrder();

	while (Buffer->Nxt_order || !isAllOrderFinished()) // ���������ǻ�����Ϊ��
	{
		start_clock = clock();
		Time++;
		//���������еĶ����ŵ�ȫ�ֶ�����¼��
		OrderList* tempOrderList = Buffer->Nxt_order;
		while (tempOrderList)
		{
			if (tempOrderList->Cur_order->begin_time == Time)
			{
				push_back_order(tempOrderList->Cur_order, AllOrderLog);
				tempOrderList = delete_order(tempOrderList);
				CompanyOrderSum++; // ��˾���ܶ���+1
			}
			tempOrderList = tempOrderList->Nxt_order;
		}
		//��ļ����

		while (CompanyMoney >= 400)
		{
			hireRider();
		}
		//�ɵ�֮ǰ�����ֱ�����ɵĶ�������
		initRiderBag();
		//�ɵ��㷨
		arrangeNewOrder(); // �˴��������Ż�
		//�ж��Ƿ�ʱ���Ʋ�
		isAnyOrderOverTime();
		//�����ƶ�
		AllRiderMove();
		//�ж�ÿһ�������Ƿ����
		//���ÿһ����Ҫ��ɵĶ��� ���������ֱ����ﲻ��������ɵĶ��� ������ļ�ʱ�ж�ͣ��ʹ�ã�
		int isAnyOrderComplish = 0;
		RiderList* tempRider = AllRiderLog->Nxt_rider;
		while (tempRider) // ����
		{
			OrderList* tempOrder = tempRider->Cur_rider->Bag->Nxt_order;
			while (tempOrder) // ����
			{
				if (isComplishOrder(tempOrder, tempRider))
				{
					tempOrder = complishOrder(tempOrder);
					isAnyOrderComplish = 1;
				}
				tempOrder = tempOrder->Nxt_order;
			}
			tempRider = tempRider->Nxt_rider;
		}
		//�ж������ʱ�����������ˢ��һ��
		if (isAnyOrderComplish)
		{
			system("cls");
			outputMap();
			outputKey();
		}
		//����ļ�
		outputOnFile();
		end_clock = clock();
		// Sleep(TIME_UNIT * 1000 - (end_clock - start_clock)); // ׼ȷ2��ˢ��
	}
	gameSuccess();
	return 0;
}