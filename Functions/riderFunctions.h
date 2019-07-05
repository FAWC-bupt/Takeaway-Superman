#include "./Global/header.h"

/*
    招募骑手,返回骑手的id，注意，前提条件是CompanyMoney>=400
 */
int hireRider()
{
    CompanyMoney -= 300; // 扣钱
    CompanyRiderCount++; // 加骑手数量
    RiderList *p = AllRiderLog, *tmp = (RiderList *)malloc(sizeof(RiderList));
    Rider *newRider = (Rider *)malloc(sizeof(Rider));
    while (p->Nxt_rider)
    {
        p = p->Nxt_rider;
    }
    // 初始化新骑手
    newRider->id = p->Cur_rider->id + 1;
    newRider->rider_x = COMPANY_X;
    newRider->rider_y = COMPANY_Y;
    newRider->Bag = creatOrderList(); // 骑手的背包是一个订单链表
    //将该骑手添加到骑手列表
    p->Nxt_rider = tmp;
    tmp->Pre_rider = p;
    tmp->Cur_rider = newRider;
    tmp->Nxt_rider = NULL;
    return newRider->id;
}
/*
    输入骑手id返回Order指针
    rider_id:骑手id
    return(Order *):棋手当前订单的指针
 */
Order *getRiderCurOrder(int rider_id)
{
    RiderList *p = AllRiderLog;
    while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
    {
        p = p->Nxt_rider;
    }
    return p->Cur_rider;
}
/*
    输入骑手id返回OrderList指针
    rider_id:骑手id
    return(OrderList *):棋手当前背包的指针
 */
OrderList *getRiderCurBag(int rider_id)
{
    RiderList *p = AllRiderLog;
    while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
    {
        p = p->Nxt_rider;
    }
    return p->Cur_rider->Bag;
}

/*
    返回骑手位置，注意传入坐标的指针
    rider_id:骑手id
    int *x:骑手横坐标指针
    int *y:骑手纵坐标指针
 */
void riderPos(int rider_id, int *x, int *y)
{
    RiderList *p = AllRiderLog;
    while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
    {
        p = p->Nxt_rider;
    }
    *x = p->Cur_rider->rider_x;
    *y = p->Cur_rider->rider_y;
}
/*
    入骑手id和目的地（房子坐标），根据骑手当前位置，先左右,后上下，移动一个单位
    rider_id:骑手id
    int pos_x:目的地横坐标
    int pos_y:目的地纵坐标
 */
void riderMove(int rider_id, int pos_x, int pos_y)
{
    int cur_x, cur_y;
    RiderList *p = AllRiderLog;
    while (p->Cur_rider != NULL && p->Cur_rider->id != rider_id)
    {
        p = p->Nxt_rider;
    }
    cur_x = p->Cur_rider->rider_x;
    cur_y = p->Cur_rider->rider_y;
    /* 
        横纵坐标一奇一偶的都是路，坐标都是偶数的是房间，坐标都是奇数的是路口
        房子上面和下面的路（横着的）：(偶，奇) 房子左面和右面的路（竖着的）：(奇，偶)
        TODO:更改骑手的位置，仅移动一个单位
     */
}
