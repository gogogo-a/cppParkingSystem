#include <iostream>
#include "admin.h"

void showWelcome() {
    std::cout << "========================================" << std::endl;
    std::cout << "      欢迎使用停车场管理系统       " << std::endl;
    std::cout << "========================================" << std::endl;
}

int main() {
    User commonUser;
    Admin adminUser;
    int roleChoice;

    while (true) {
        showWelcome();
        std::cout << "1. 普通用户登录" << std::endl;
        std::cout << "2. 普通用户注册" << std::endl;
        std::cout << "3. 管理员登录" << std::endl;
        std::cout << "0. 退出系统" << std::endl;
        std::cout << "请选择: ";
        
        if (!(std::cin >> roleChoice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (roleChoice == 1) {
            if (commonUser.login()) {
                commonUser.showMenu();
            }
        } else if (roleChoice == 2) {
            User::regist();
        } else if (roleChoice == 3) {
            if (adminUser.login()) {
                adminUser.showMenu();
            }
        } else if (roleChoice == 0) {
            std::cout << "感谢使用，再见！" << std::endl;
            break;
        } else {
            std::cout << "无效选项，请重新选择。" << std::endl;
        }
    }

    return 0;
}
