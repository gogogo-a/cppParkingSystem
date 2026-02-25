#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User {
private:
    std::string adminID;
    std::string password;

public:
    Admin() : adminID("admin"), password("123456") {}
    
    bool login();                       // 管理员登录
    void showMenu() override;           // 重写菜单以包含管理功能
    void addCar();                      // 增加车辆
    void deleteCar();                   // 删除车辆
    void modifyCar();                   // 修改车辆
};

#endif
