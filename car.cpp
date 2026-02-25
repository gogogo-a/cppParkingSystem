#include "car.h"
#include <algorithm>
#include <iostream>

const std::string FILE_NAME = "cars.txt";

void Car::addCar(std::string currentUser) {
    std::string num, type, col;
    std::cout << "请输入车牌号: "; std::cin >> num;
    std::cout << "请输入车型: "; std::cin >> type;
    std::cout << "请输入颜色: "; std::cin >> col;
    time_t now = time(0);

    Car newCar(num, type, col, now, currentUser);
    std::vector<Car> cars = {newCar};
    saveInfor(cars, true);
    std::cout << "车辆入库成功！入库时间: " << timeToString(now) << " 所属用户: " << currentUser << std::endl;
}

void Car::saveInfor(const std::vector<Car>& cars, bool append) {
    std::ofstream outfile;
    if (append) {
        outfile.open(FILE_NAME, std::ios::app);
    } else {
        outfile.open(FILE_NAME, std::ios::out);
    }

    if (!outfile) {
        std::cerr << "文件打开失败！" << std::endl;
        return;
    }

    for (const auto& car : cars) {
        outfile << car.carNum << " " << car.carType << " " << car.color << " " << car.entryTime << " " << car.owner << std::endl;
    }
    outfile.close();
}

std::vector<Car> Car::loadAll() {
    std::vector<Car> cars;
    std::ifstream infile(FILE_NAME);
    if (!infile) return cars;

    std::string num, type, col, own;
    time_t t;
    while (infile >> num >> type >> col >> t >> own) {
        cars.emplace_back(num, type, col, t, own);
    }
    infile.close();
    return cars;
}

void Car::showInfor(std::string currentUser, bool isAdmin) {
    std::vector<Car> allCars = loadAll();
    std::vector<Car> cars;
    
    if (isAdmin) {
        cars = allCars;
    } else {
        for (const auto& c : allCars) {
            if (c.owner == currentUser) cars.push_back(c);
        }
    }

    if (cars.empty()) {
        std::cout << "暂无车辆信息。" << std::endl;
        return;
    }

    std::cout << std::left << std::setw(15) << "车牌号" 
              << std::setw(10) << "类型" 
              << std::setw(10) << "颜色" 
              << std::setw(25) << "入场时间";
    if (isAdmin) std::cout << std::setw(10) << "车主";
    std::cout << "当前费用(元)" << std::endl;
    std::cout << std::string(85, '-') << std::endl;

    time_t now = time(0);
    for (const auto& car : cars) {
        double diff = difftime(now, car.entryTime);
        double hours = diff / 3600.0;
        double fee = std::max(5.0, hours * 2.0);

        std::cout << std::left << std::setw(15) << car.carNum 
                  << std::setw(10) << car.carType 
                  << std::setw(10) << car.color 
                  << std::setw(25) << timeToString(car.entryTime);
        if (isAdmin) std::cout << std::setw(10) << car.owner;
        std::cout << std::fixed << std::setprecision(2) << fee << std::endl;
    }
}

void Car::findCar(std::string currentUser, bool isAdmin) {
    std::string num;
    std::cout << "请输入要查找的车牌号: "; std::cin >> num;
    std::vector<Car> cars = loadAll();
    
    auto it = std::find_if(cars.begin(), cars.end(), [&](const Car& c) { 
        return c.carNum == num && (isAdmin || c.owner == currentUser); 
    });
    if (it != cars.end()) {
        std::cout << "找到车辆信息:" << std::endl;
        std::cout << "车牌: " << it->carNum << " | 类型: " << it->carType << " | 颜色: " << it->color 
                  << " | 车主: " << it->owner << " | 入场时间: " << timeToString(it->entryTime) << std::endl;
    } else {
        std::cout << "未找到该车辆或无权限查看。" << std::endl;
    }
}

void Car::delCar(std::string currentUser, bool isAdmin) {
    std::string num;
    std::cout << "请输入要出库的车牌号: "; std::cin >> num;
    std::vector<Car> cars = loadAll();
    
    auto it = std::find_if(cars.begin(), cars.end(), [&](const Car& c) {
        return c.carNum == num && (isAdmin || c.owner == currentUser);
    });

    if (it != cars.end()) {
        cars.erase(it);
        saveInfor(cars, false);
        std::cout << "车辆 " << num << " 已成功出库。" << std::endl;
    } else {
        std::cout << "未找到该车辆或无权限操作。" << std::endl;
    }
}

void Car::modCar(std::string currentUser, bool isAdmin) {
    std::string num;
    std::cout << "请输入要修改的车牌号: "; std::cin >> num;
    std::vector<Car> cars = loadAll();
    
    auto it = std::find_if(cars.begin(), cars.end(), [&](const Car& c) {
        return c.carNum == num && (isAdmin || c.owner == currentUser);
    });

    if (it != cars.end()) {
        std::cout << "输入新车型 (当前: " << it->carType << "): "; std::cin >> it->carType;
        std::cout << "输入新颜色 (当前: " << it->color << "): "; std::cin >> it->color;
        saveInfor(cars, false);
        std::cout << "信息修改成功！" << std::endl;
    } else {
        std::cout << "未找到该车辆或无权限操作。" << std::endl;
    }
}

void Car::timeAmount(std::string currentUser, bool isAdmin) {
    std::vector<Car> allCars = loadAll();
    std::vector<Car> cars;
    
    if (isAdmin) {
        cars = allCars;
    } else {
        for (const auto& c : allCars) {
            if (c.owner == currentUser) cars.push_back(c);
        }
    }

    if (cars.empty()) {
        std::cout << "暂无车辆统计数据。" << std::endl;
        return;
    }

    time_t now = time(0);
    int moreThanDay = 0;
    int lessThanDay = 0;

    for (const auto& car : cars) {
        double seconds = difftime(now, car.entryTime);
        double days = seconds / (24 * 3600);
        if (days >= 1.0) moreThanDay++;
        else lessThanDay++;
        
        std::cout << "车牌: " << car.carNum << " | 车主: " << car.owner << " | 停留时长: " 
                  << (int)(seconds / 3600) << "小时 " << ((int)(seconds) % 3600 / 60) << "分钟" << std::endl;
    }

    std::cout << "\n统计结果:" << std::endl;
    std::cout << "超过一天的车辆总数: " << moreThanDay << std::endl;
    std::cout << "不足一天的车辆总数: " << lessThanDay << std::endl;
}

std::string Car::timeToString(time_t t) {
    char buf[64];
    struct tm* tstruct = localtime(&t);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tstruct);
    return std::string(buf);
}
