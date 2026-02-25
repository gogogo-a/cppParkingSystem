#include "user.h"
#include <iostream>
#include <fstream>
#include <vector>

void User::showMenu() {
    int choice;
    while (true) {
        std::cout << "\n--- 普通用户 [" << username << "] 菜单 ---" << std::endl;
        std::cout << "1. 查看我的车辆及费用" << std::endl;
        std::cout << "2. 查询特定车辆详情" << std::endl;
        std::cout << "3. 停车时长统计" << std::endl;
        std::cout << "4. 车辆入库 (绑定账号)" << std::endl;
        std::cout << "0. 返回主菜单" << std::endl;
        std::cout << "请输入选择: ";
        std::cin >> choice;

        switch (choice) {
            case 1: showAllCars(); break;
            case 2: searchCar(); break;
            case 3: showTimeStats(); break;
            case 4: Car::addCar(username); break;
            case 0: return;
            default: std::cout << "无效输入，请重试。" << std::endl;
        }
    }
}

bool User::login() {
    std::string id, pw;
    std::cout << "请输入用户名: "; std::cin >> id;
    std::cout << "请输入密码: "; std::cin >> pw;

    std::ifstream infile("users.txt");
    std::string fileID, filePW;
    while (infile >> fileID >> filePW) {
        if (id == fileID && pw == filePW) {
            username = id;
            std::cout << "登录成功！欢迎 " << username << std::endl;
            return true;
        }
    }
    std::cout << "用户名或密码错误！" << std::endl;
    return false;
}

void User::regist() {
    std::string id, pw;
    std::cout << "请设置用户名: "; std::cin >> id;
    std::cout << "请设置密码: "; std::cin >> pw;

    // 检查是否重名
    std::ifstream infile("users.txt");
    std::string fileID, filePW;
    while (infile >> fileID >> filePW) {
        if (id == fileID) {
            std::cout << "用户名已存在，请换一个。" << std::endl;
            return;
        }
    }
    infile.close();

    std::ofstream outfile("users.txt", std::ios::app);
    outfile << id << " " << pw << std::endl;
    outfile.close();
    std::cout << "注册成功！请登录。" << std::endl;
}

void User::showAllCars() {
    Car::showInfor(username, false);
}

void User::searchCar() {
    Car::findCar(username, false);
}

void User::showTimeStats() {
    Car::timeAmount(username, false);
}
