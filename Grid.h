#ifndef GRID_H
#define GRID_H

#include <set>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>

// 使用 pair<x, y> 表示坐标
using Coordinate = std::pair<int, int>;

class Grid {
private:
    // 核心数据结构：只存储活细胞的坐标
    std::set<Coordinate> liveCells;

public:
    Grid();
    
    // 添加活细胞
    void addCell(int x, int y);
    
    // 执行一步模拟 (t -> t+1)
    void step();
    
    // 获取当前的活细胞数量
    size_t getPopulation() const;

    // 保存为 PBM 格式
    void saveToPBM(const std::string& filename) const;

    // 从简单的文本格式加载
    void loadFromFile(const std::string& filename);
};

#endif