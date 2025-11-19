#ifndef RPN_CALCULATOR_H
#define RPN_CALCULATOR_H

#include <vector>
#include <string>
#include <stack>
#include <stdexcept>
#include <cmath>

/**
 * @class RPNCalculator
 * @brief 逆波兰表示法计算器核心类
 * 
 * 实现基于栈的RPN计算器，支持基础四则运算和高级数学函数
 */
class RPNCalculator {
private:
    std::stack<double> stack_;  ///< 操作数栈

public:
    // ==================== 基础栈操作 ====================
    
    /**
     * @brief 将数值压入栈中
     * @param value 要压入的数值
     */
    void push(double value);
    
    /**
     * @brief 从栈中弹出数值
     * @return 弹出的数值
     * @throws std::runtime_error 如果栈为空
     */
    double pop();
    
    /**
     * @brief 清空栈
     */
    void clear();
    
    /**
     * @brief 显示栈内容
     */
    void displayStack() const;
    
    /**
     * @brief 检查栈是否为空
     * @return true如果栈为空，否则false
     */
    bool empty() const;
    
    /**
     * @brief 获取栈大小
     * @return 栈中元素数量
     */
    size_t size() const;
    
    // ==================== 数学运算 ====================
    
    /**
     * @brief 执行数学运算
     * @param operation 操作符 (+, -, *, /, sqrt, pow, fib)
     * @throws std::runtime_error 如果操作符无效或运算错误
     */
    void calculate(const std::string& operation);
    
    // ==================== 高级数学函数 ====================
    
    /**
     * @brief 平方根运算
     * @throws std::runtime_error 如果对负数开平方根
     */
    void sqrt();
    
    /**
     * @brief 幂运算
     */
    void power();
    
    /**
     * @brief 斐波那契数列计算
     * @throws std::runtime_error 如果输入为负数
     */
    void fibonacci();
    
    // ==================== 结果获取 ====================
    
    /**
     * @brief 获取当前栈顶结果
     * @return 栈顶数值
     * @throws std::runtime_error 如果栈为空
     */
    double getResult() const;
};

#endif // RPN_CALCULATOR_H
