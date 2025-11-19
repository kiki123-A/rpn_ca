#include "rpn_calculator.h"
#include <iostream>
#include <cmath>
#include <sstream>

// ==================== 基础栈操作实现 ====================

void RPNCalculator::push(double value) {
    stack_.push(value);
}

double RPNCalculator::pop() {
    if (stack_.empty()) {
        throw std::runtime_error("栈为空");
    }
    double value = stack_.top();
    stack_.pop();
    return value;
}

void RPNCalculator::clear() {
    while (!stack_.empty()) {
        stack_.pop();
    }
}

void RPNCalculator::displayStack() const {
    if (stack_.empty()) {
        std::cout << "📭 栈: [空]" << std::endl;
        return;
    }
    
    std::stack<double> temp = stack_;
    std::vector<double> elements;
    
    // 将栈内容复制到vector以便正确显示
    while (!temp.empty()) {
        elements.push_back(temp.top());
        temp.pop();
    }
    
    std::cout << "🗂️  栈 (顶→底): ";
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "📊 栈大小: " << stack_.size() << std::endl;
}

bool RPNCalculator::empty() const {
    return stack_.empty();
}

size_t RPNCalculator::size() const {
    return stack_.size();
}

// ==================== 数学运算实现 ====================

void RPNCalculator::calculate(const std::string& operation) {
    if (operation == "+") {
        // 加法: a + b
        double b = pop();
        double a = pop();
        push(a + b);
        std::cout << "🔢 计算: " << a << " + " << b << " = " << (a + b) << std::endl;
    } 
    else if (operation == "-") {
        // 减法: a - b
        double b = pop();
        double a = pop();
        push(a - b);
        std::cout << "🔢 计算: " << a << " - " << b << " = " << (a - b) << std::endl;
    } 
    else if (operation == "*") {
        // 乘法: a × b
        double b = pop();
        double a = pop();
        push(a * b);
        std::cout << "🔢 计算: " << a << " × " << b << " = " << (a * b) << std::endl;
    } 
    else if (operation == "/") {
        // 除法: a ÷ b
        double b = pop();
        if (b == 0) {
            throw std::runtime_error("除零错误");
        }
        double a = pop();
        push(a / b);
        std::cout << "🔢 计算: " << a << " ÷ " << b << " = " << (a / b) << std::endl;
    } 
    else if (operation == "sqrt") {
        sqrt();
    } 
    else if (operation == "pow") {
        power();
    } 
    else if (operation == "fib") {
        fibonacci();
    } 
    else {
        throw std::runtime_error("未知操作符: '" + operation + "'");
    }
}

// ==================== 高级数学函数实现 ====================

void RPNCalculator::sqrt() {
    if (stack_.empty()) {
        throw std::runtime_error("栈为空，无法进行平方根运算");
    }
    
    double a = pop();
    if (a < 0) {
        throw std::runtime_error("不能对负数开平方根");
    }
    
    double result = std::sqrt(a);
    push(result);
    std::cout << "🔢 计算: √" << a << " = " << result << std::endl;
}

void RPNCalculator::power() {
    if (stack_.size() < 2) {
        throw std::runtime_error("需要两个操作数进行幂运算");
    }
    
    double exponent = pop();
    double base = pop();
    double result = std::pow(base, exponent);
    push(result);
    std::cout << "🔢 计算: " << base << "^" << exponent << " = " << result << std::endl;
}

void RPNCalculator::fibonacci() {
    if (stack_.empty()) {
        throw std::runtime_error("栈为空，无法计算斐波那契数列");
    }
    
    double n_double = pop();
    int n = static_cast<int>(n_double);
    
    // 检查是否为整数
    if (n != n_double) {
        throw std::runtime_error("斐波那契数列输入必须为整数");
    }
    
    if (n < 0) {
        throw std::runtime_error("斐波那契输入必须为非负数");
    }
    
    if (n == 0) {
        push(0);
        std::cout << "🔢 计算: fib(0) = 0" << std::endl;
    } 
    else if (n == 1) {
        push(1);
        std::cout << "🔢 计算: fib(1) = 1" << std::endl;
    } 
    else {
        double a = 0, b = 1;
        for (int i = 2; i <= n; ++i) {
            double temp = a + b;
            a = b;
            b = temp;
        }
        push(b);
        std::cout << "🔢 计算: fib(" << n << ") = " << b << std::endl;
    }
}

// ==================== 结果获取实现 ====================

double RPNCalculator::getResult() const {
    if (stack_.empty()) {
        throw std::runtime_error("栈为空");
    }
    return stack_.top();
}
