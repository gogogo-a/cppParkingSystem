#include "admin.h"
#include <iostream>

bool Admin::login() {
    std::string id, pw;
    std::cout << "请输入管理员ID: "; std::cin >> id;
    std::cout << "请输入密码: "; std::cin >> pw;

    std::ifstream infile("admin.txt");
    if (!infile) {
        // 如果文件不存在，回退到默认账号密码并创建文件
        if (id == "admin" && pw == "123456") {
            std::ofstream outfile("admin.txt");
            outfile << "admin 123456";
            outfile.close();
            std::cout << "登录成功（默认配置）！" << std::endl;
            return true;
        }
    } else {
        std::string fileID, filePW;
        if (infile >> fileID >> filePW) {
            if (id == fileID && pw == filePW) {
                std::cout << "登录成功！" << std::endl;
                return true;
            }
        }
    }
    std::cout << "身份验证失败！" << std::endl;
    return false;
}

void Admin::showMenu() {
    int choice;
    while (true) {
        std::cout << "\n--- 管理员系统菜单 ---" << std::endl;
        std::cout << "1. 增加车辆信息 (管理入库)" << std::endl;
        std::cout << "2. 修改任意车辆信息" << std::endl;
        std::cout << "3. 任意车辆出库" << std::endl;
        std::cout << "4. 查看全场车辆及费用" << std::endl;
        std::cout << "5. 全局查找车辆信息" << std::endl;
        std::cout << "6. 全局停车时长统计" << std::endl;
        std::cout << "0. 退出管理员模式" << std::endl;
        std::cout << "请输入选择: ";
        std::cin >> choice;

        switch (choice) {
            case 1: addCar(); break;
            case 2: modifyCar(); break;
            case 3: deleteCar(); break;
            case 4: Car::showInfor("admin", true); break;
            case 5: Car::findCar("admin", true); break;
            case 6: Car::timeAmount("admin", true); break;
            case 0: return;
            default: std::cout << "无效输入，请重试。" << std::endl;
        }
    }
}

void Admin::addCar() {
    Car::addCar("admin"); // 管理员添加的车辆默认归属 admin
}

void Admin::deleteCar() {
    Car::delCar("admin", true);
}

void Admin::modifyCar() {
    Car::modCar("admin", true);
}
