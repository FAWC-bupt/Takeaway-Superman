#include "../Global/header.h"

/*
	��������ɾ��ͷ������
	List����������
 */
void pop_front_order(OrderList *List)
{
	OrderList *p = List->Nxt_order;
	List->Nxt_order = List->Nxt_order->Nxt_order;
	List->Nxt_order->Pre_order = List;
	free(p);
}
/*
	���β������
	NewOrder����ӵĶ���
	List�������б�
 */
void push_back_order(Order *NewOrder, OrderList *List)
{
	OrderList *NewOrderList = (OrderList *)malloc(sizeof(OrderList));
	NewOrderList->Cur_order = NewOrder;
	OrderList *BackOrderList = List;
	while (BackOrderList->Nxt_order)
		BackOrderList = BackOrderList->Nxt_order;
	BackOrderList->Nxt_order = NewOrderList;
	NewOrderList->Pre_order = BackOrderList;
	NewOrderList->Nxt_order = NULL;
}
/*
	���ֶ���β���������
	NewRider���µ�����
	List�������б�
 */
void push_back_rider(Rider *NewRider, RiderList *List)
{
	RiderList *NewRiderList = (RiderList *)malloc(sizeof(RiderList));
	NewRiderList->Cur_rider = NewRider;
	RiderList *BackRiderList = List;
	while (BackRiderList->Nxt_rider)
		BackRiderList = BackRiderList->Nxt_rider;
	BackRiderList->Nxt_rider = NewRiderList;
	NewRiderList->Pre_rider = BackRiderList;
	NewRiderList->Nxt_rider = NULL;
}
/*
	�����б���
 */
void swap_order(OrderList *List1, OrderList *List2)
{
	Order *TempOrder = List1->Cur_order;
	List1->Cur_order = List2->Cur_order;
	List2->Cur_order = TempOrder;
}
/*
	ɾ�����������ظö�����ǰһ������
	tOrder��Ŀ�궩��
 */
OrderList *delete_order(OrderList *tOrder)
{
	OrderList *tempOrder = tOrder->Pre_order;
	tOrder->Pre_order->Nxt_order = tOrder->Nxt_order;
	if (tOrder->Nxt_order) //������������ڣ��ı��������ǰһ������ָ��
		tOrder->Nxt_order->Pre_order = tOrder->Pre_order;
	free(tOrder);
	return tempOrder;
}