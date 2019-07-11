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
	OrderList *newOrderList = (OrderList *)malloc(sizeof(OrderList));
	newOrderList->Cur_order = NewOrder;
	OrderList *backOrderList = List;
	while (backOrderList->Nxt_order)
		backOrderList = backOrderList->Nxt_order;
	backOrderList->Nxt_order = newOrderList;
	newOrderList->Pre_order = backOrderList;
	newOrderList->Nxt_order = NULL;
}
/*
	���ֶ���β���������
	NewRider���µ�����
	List�������б�
 */
void push_back_rider(Rider *NewRider, RiderList *List)
{
	RiderList *newRiderList = (RiderList *)malloc(sizeof(RiderList));
	newRiderList->Cur_rider = NewRider;
	RiderList *backRiderList = List;
	while (backRiderList->Nxt_rider)
		backRiderList = backRiderList->Nxt_rider;
	backRiderList->Nxt_rider = newRiderList;
	newRiderList->Pre_rider = backRiderList;
	newRiderList->Nxt_rider = NULL;
}
/*
	�����б���
 */
void swap_order(OrderList *List1, OrderList *List2)
{
	Order *tempOrder = List1->Cur_order;
	List1->Cur_order = List2->Cur_order;
	List2->Cur_order = tempOrder;
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