#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <iomanip>

class Car {
protected:
    std::string carNum;   // 车牌号
    std::string carType;  // 类型
    std::string color;    // 颜色
    time_t entryTime;     // 入场时间
    std::string owner;    // 所属用户

public:
    Car() : entryTime(0) {}
    Car(std::string num, std::string type, std::string col, time_t t, std::string own = "admin")
        : carNum(num), carType(type), color(col), entryTime(t), owner(own) {}

    // 核心功能
    static void addCar(std::string currentUser = "admin");           // 添加信息
    static void delCar(std::string currentUser = "admin", bool isAdmin = false); // 删除信息
    static void findCar(std::string currentUser = "admin", bool isAdmin = false); // 查找信息
    static void modCar(std::string currentUser = "admin", bool isAdmin = false); // 修改信息
    static void timeAmount(std::string currentUser = "admin", bool isAdmin = false); // 时间统计
    static void showInfor(std::string currentUser = "admin", bool isAdmin = false); // 信息显示
    static void saveInfor(const std::vector<Car>& cars, bool append = false); // 信息保存

    // 辅助函数
    static std::vector<Car> loadAll(); // 从文件读取所有车辆
    static std::string timeToString(time_t t);
    
    // Getters
    std::string getNum() const { return carNum; }
    std::string getType() const { return carType; }
    std::string getColor() const { return color; }
    time_t getEntryTime() const { return entryTime; }
    std::string getOwner() const { return owner; }
};

#endif
