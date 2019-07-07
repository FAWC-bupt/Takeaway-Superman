#include "./Global/header.h"

int main()
{
    clock_t start_clock, end_clock; // 用于计算程序运行时间
    if (inputFileOrder())
        ;
    else
        inputKeyOrder();

    while (Buffer->Nxt_order) // 结束条件是缓冲区为空
    {
        start_clock = clock();
        Time++;
        //将缓冲区中的订单放到全局订单记录中
        {
            OrderList *tempOrderList = Buffer->Nxt_order;
            while (tempOrderList)
            {
                if (tempOrderList->Cur_order->begin_time == Time)
                {
                    push_back_order(tempOrderList->Cur_order, AllOrderLog);
                    delete_order(tempOrderList);
                }
                tempOrderList = tempOrderList->Nxt_order;
            }
        }
        //招募骑手
        while (CompanyMoney >= 400)
        {
            hireRider();
        }
        //派单之前把骑手背包完成的订单弹出
        initRiderBag();
        //派单算法
        arrangeNewOrder();  // 此处遍历可优化
        //判断是否超时或破产
        isAnyOrderOverTime();
        //骑手移动
        AllRiderMove();
        //判断每一个订单是否完成
        //完成每一个需要完成的订单 但是在骑手背包里不弹出刚完成的订单 （输出文件时判断停靠使用）
        int isAnyOrderComplish = 0;
        RiderList *tempRider = AllRiderLog->Nxt_rider;
        while (tempRider)
        {
            OrderList *tempOrder = tempRider->Cur_rider->Bag->Nxt_order;
            while (tempOrder)
            {
                if (isComplishOrder(tempOrder))
                {
                    complishOrder(tempOrder);
                    isAnyOrderComplish = 1;
                }
                tempOrder = tempOrder->Nxt_order;
            }
            tempRider = tempRider->Nxt_rider;
        }
        //有订单完成时，命令行输出刷新一次
        if (isAnyOrderComplish)
        {
            system("clr");
            outputMap();
            outputKey();
        }
        //输出文件
        outputOnFile();
        end_clock() = clock();
        sleep(TIME_UNIT - (end_clock - start_clock));   // 准确2秒刷新
    }
    gameSuccess();
    // return 0;
}