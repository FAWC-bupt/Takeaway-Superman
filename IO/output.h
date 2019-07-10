
#include "../Global/header.h"

// TODO: ��ӡ���ֹ켣�Ե�����
/*
	ͣ���жϲ����
*/
void printNearBy(Rider* nowRider, FILE* fPtr)
{
	int i;
	const int dx[] = { -1, 1, 0, 0 };
	const int dy[] = { 0, 0, 1, -1 };
	int restFlag = 0, dustFlag = 0;

	for (i = 0; i <= 3; i++)
	{
		restFlag = 0;
		dustFlag = 0;
		int now_x = nowRider->rider_x + dx[i];
		int now_y = nowRider->rider_y + dy[i];
		OrderList* tmpOrder = nowRider->Bag->Nxt_order;
		while (tmpOrder)
		{
			if (tmpOrder->Cur_order->rest_x == now_x && tmpOrder->Cur_order->rest_y == now_y && tmpOrder->Cur_order->end_time == Time) // ˵����λ�÷�����Ϊ�������������
			{
				restFlag = 1;
			}
			if (tmpOrder->Cur_order->cust_x == now_x && tmpOrder->Cur_order->cust_y == now_y && tmpOrder->Cur_order->end_time == Time) // ˵����λ�÷�����Ϊ�������������
			{
				dustFlag = 1;
			}
			if (dustFlag && restFlag)
				fprintf(fPtr, "�Ϳ� %d %d", now_x, now_y);
			else if (restFlag)
				fprintf(fPtr, "���� %d %d", now_x, now_y);
			else if (dustFlag)
				fprintf(fPtr, "ʳ�� %d %d", now_x, now_y);
			tmpOrder = tmpOrder->Nxt_order;
		}
	}
}
/*
	������ļ���
*/
void outputOnFile()
{
	FILE* fPtr = fopen("output.txt", "a");
	if (fPtr == NULL)
	{
		printf("Can't not open the output.txt");
		return;
	}
	fprintf(fPtr, "ʱ��:%d\n", Time);
	fprintf(fPtr, "Ǯ:%d\n", CompanyMoney);
	fprintf(fPtr, "�ӵ���:%d\n", CompanyOrderSum);
	fprintf(fPtr, "�����:%d;", CompanyOrderFinish);
	fprintf(fPtr, "�ᵥ:");
	// ����ȫ�������ж��Ƿ��д�ʱ�̽ᵥ��
	OrderList* HeadOrder = AllOrderLog;
	HeadOrder = HeadOrder->Nxt_order;
	int flag = 0; // �ж��Ƿ�Ϊ��һ������Ķ�����
	while (HeadOrder)
	{
		if (HeadOrder->Cur_order->end_time == Time && HeadOrder->Cur_order->status == 3)
		{
			if (!flag)
			{
				flag = 1;
				fprintf(fPtr, "%d", HeadOrder->Cur_order->id);
			}
			else
			{
				fprintf(fPtr, " %d", HeadOrder->Cur_order->id);
			}
		}
		HeadOrder = HeadOrder->Nxt_order;
	}
	fprintf(fPtr, ";\n");
	fprintf(fPtr, "��ʱ��:%d;", CompanyOrderOverTime);
	fprintf(fPtr, "����:");
	// ������ʱ���Ƿ��з�����
	HeadOrder = AllOrderLog;
	HeadOrder = HeadOrder->Nxt_order;
	flag = 0;
	while (HeadOrder)
	{
		if (Time - HeadOrder->Cur_order->begin_time == FINE_FIRST_TIME + 1 && HeadOrder->Cur_order->status != 3) // ��ʼʱ������ڵ���31��δ���
		{
			if (!flag)
			{
				flag = 1;
				fprintf(fPtr, "%d", HeadOrder->Cur_order->id);
			}
			else
			{
				fprintf(fPtr, " %d", HeadOrder->Cur_order->id);
			}
		}
		HeadOrder = HeadOrder->Nxt_order;
	}
	fprintf(fPtr, ";\n");
	// ���������״̬
	RiderList* HeadRider = AllRiderLog;
	HeadRider = HeadRider->Nxt_rider;
	while (HeadRider)
	{
		fprintf(fPtr, "����%dλ��:%d,%d;", HeadRider->Cur_rider->id, HeadRider->Cur_rider->rider_x, HeadRider->Cur_rider->rider_y);
		fprintf(fPtr, "ͣ��:");
		printNearBy(HeadRider->Cur_rider, fPtr);
		HeadRider = HeadRider->Nxt_rider;
		fprintf(fPtr, ";\n");
	}
	fclose(fPtr);
}
/*
	�����ֵ���ʽ�������Ļ�ϣ�ע��ˢ��Ƶ�ʲ�ͬ������
*/
void outputKey()
{
	printf("ʱ��: %d\n", Time);
	printf("Ǯ: %d\n", CompanyMoney); // ����ָ�ֽ�û�м��������ʲ�
	printf("�ӵ���: %d\n", CompanyOrderSum);
	printf("�����: %d\n", CompanyOrderFinish);
	printf("��ʱ��: %d;", CompanyOrderOverTime);
}
/*
	�Ե�ͼ����ʽ�������Ļ��
*/
void outputMap() // �Ϳ���ʽû����
{
	int i, j, k;

	initMap(); // ��ʼ����ͼ
	// ��ʼ����������
	OrderList* HeadOrder = AllOrderLog;
	HeadOrder = HeadOrder->Nxt_order;
	while (HeadOrder)
	{
		// ����ͣ������Э��
		if ((HeadOrder->Cur_order->status != 0 && HeadOrder->Cur_order->status != 3) || (HeadOrder->Cur_order->status == 3 && HeadOrder->Cur_order->end_time == Time))
		{
			Map[HeadOrder->Cur_order->rest_x][HeadOrder->Cur_order->rest_x] = 2; // ������ͼ����
			Map[HeadOrder->Cur_order->cust_x][HeadOrder->Cur_order->cust_x] = 3; // �����ͼ����
		}
		HeadOrder = HeadOrder->Nxt_order;
	}
	// ��ʼ������λ��
	RiderList* HeadRider = AllRiderLog;
	HeadRider = HeadRider->Nxt_rider;
	while (HeadRider)
	{
		Map[HeadRider->Cur_rider->rider_x][HeadRider->Cur_rider->rider_y] = 4; // ���ֵ�ͼ����
		HeadRider = HeadRider->Nxt_rider;
	}

	for (i = 0; i <= 16; i++)
	{
		if (i % 2 == 0)
		{ // �з��ӵ���
			for (k = 0; k <= 3; k++)
			{
				for (j = 0; j <= 16; j++)
				{
					if (j % 2 == 0)
					{
						if (k == 0)
						{
							printf("__________");
						}
						else if (k == 1)
						{
							printf("|        |");
						}
						else if (k == 2)
						{
							printf("|  ");
							/*
							if (Map[i][j] == 0) { // ��·
								printf("    ");
							}
							*/
							if (Map[i][j] == 1)
							{ // ����
								printf("    ");
							}
							else if (Map[i][j] == 2)
							{ // ����
								printf("����");
							}
							else
							{ // ����
								printf("����");
							}
							printf("  |");
						}
						else
						{
							printf("|________|");
						}
					}
					else
					{
						if (k == 2)
						{
							if (Map[i][j] == 0)
							{ // ��·
								printf("    ");
							}
							else if (Map[i][j] == 4)
							{ // ����
								printf("����");
							}
						}
						else
						{
							printf("    ");
						}
					}
				}
				printf("\n");
			}
		}
		else
		{ // �޷��ӵ���
			for (j = 0; j <= 16; j++)
			{
				if (j % 2 == 0)
				{
					printf("   ");
					if (Map[i][j] == 0)
					{
						printf("    ");
					}
					if (Map[i][j] == 4)
					{
						printf("����");
					}
					printf("   ");
				}
				else
				{
					printf("    ");
				}
			}
			printf("\n");
		}
	}
}
