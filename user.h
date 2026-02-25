#ifndef USER_H
#define USER_H

#include "car.h"
#include <string> // Added for std::string

class User {
protected:
    std::string username;
    
public:
    User() : username("guest") {}
    virtual void showMenu();            // 显示普通用户菜单
    bool login();                       // 登录
    static void regist();              // 注册
    void showAllCars();                 // 查看名下车辆
    void searchCar();                   // 查询车辆信息
    void showTimeStats();               // 停车时长统计
};

#endif
