#include "rpn_calculator.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

// ==================== 函数声明 ====================
void processExpression(const std::string& expression, RPNCalculator& calc);
void showHelp();
void showWelcome();
void batchCalculate(RPNCalculator& calc);
void interactiveMode(RPNCalculator& calc);
void printResult(double result);

// ==================== 工具函数 ====================

/**
 * @brief 打印格式化的结果
 * @param result 计算结果
 */
void printResult(double result) {
    if (result == static_cast<int>(result)) {
        std::cout << "🎯 结果: " << static_cast<int>(result) << std::endl;
    } else {
        std::cout << "🎯 结果: " << std::fixed << std::setprecision(6) << result << std::endl;
        std::cout.unsetf(std::ios_base::floatfield);
    }
}

/**
 * @brief 显示欢迎信息
 */
void showWelcome() {
    std::cout << "==========================================" << std::endl;
    std::cout << "        🧮 C++ RPN 计算器" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "逆波兰表示法 (Reverse Polish Notation)" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "特性:" << std::endl;
    std::cout << "  • 基础四则运算 (+ - * /)" << std::endl;
    std::cout << "  • 高级数学函数 (sqrt, pow, fib)" << std::endl;
    std::cout << "  • 完整的栈操作 (clear, show)" << std::endl;
    std::cout << "  • 智能错误处理" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "输入 'help' 查看详细帮助" << std::endl;
    std::cout << "输入 'batch' 查看计算示例" << std::endl;
    std::cout << "输入 'quit' 退出程序" << std::endl;
    std::cout << "==========================================" << std::endl;
}

// ==================== 核心功能函数 ====================

/**
 * @brief 处理 RPN 表达式
 * @param expression 输入的 RPN 表达式
 * @param calc 计算器实例
 */
void processExpression(const std::string& expression, RPNCalculator& calc) {
    if (expression.empty()) return;
    
    std::istringstream iss(expression);
    std::string token;
    bool hasOperation = false;
    
    while (iss >> token) {
        // 转换为小写以支持大小写不敏感的命令
        std::string lowerToken = token;
        std::transform(lowerToken.begin(), lowerToken.end(), lowerToken.begin(), ::tolower);
        
        try {
            if (lowerToken == "+" || lowerToken == "-" || lowerToken == "*" || lowerToken == "/" ||
                lowerToken == "sqrt" || lowerToken == "pow" || lowerToken == "fib") {
                // 数学运算
                calc.calculate(lowerToken);
                hasOperation = true;
                std::cout << "✓ 执行操作: " << token << std::endl;
            } 
            else if (lowerToken == "clear") {
                calc.clear();
                std::cout << "✅ 栈已清空" << std::endl;
                return;
            } 
            else if (lowerToken == "show" || lowerToken == "stack") {
                calc.displayStack();
                return;
            } 
            else if (lowerToken == "help" || lowerToken == "?") {
                showHelp();
                return;
            } 
            else if (lowerToken == "exit" || lowerToken == "quit" || lowerToken == "q") {
                std::cout << "👋 感谢使用！" << std::endl;
                exit(0);
            }
            else {
                // 尝试转换为数字
                try {
                    double value = std::stod(token);
                    calc.push(value);
                    std::cout << "📥 压入: " << value << std::endl;
                } catch (const std::exception&) {
                    throw std::runtime_error("无法识别的输入: '" + token + "'");
                }
            }
        } 
        catch (const std::exception& e) {
            std::cout << "❌ 错误: " << e.what() << std::endl;
            return;
        }
    }
    
    // 如果有运算操作但栈中还有多个值，显示提示
    if (hasOperation && calc.size() > 1) {
        std::cout << "💡 提示: 栈中还有 " << (calc.size() - 1) << " 个值未使用" << std::endl;
    }
}

/**
 * @brief 显示详细帮助信息
 */
void showHelp() {
    std::cout << "\n📖 RPN 计算器详细帮助" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    std::cout << "\n🔢 基础数学运算:" << std::endl;
    std::cout << "  +       加法       5 3 +     → 8" << std::endl;
    std::cout << "  -       减法       10 4 -    → 6" << std::endl;
    std::cout << "  *       乘法       3 4 *     → 12" << std::endl;
    std::cout << "  /       除法       15 3 /    → 5" << std::endl;
    
    std::cout << "\n⚡ 高级数学函数:" << std::endl;
    std::cout << "  sqrt    平方根     25 sqrt   → 5" << std::endl;
    std::cout << "  pow     幂运算     2 3 pow   → 8" << std::endl;
    std::cout << "  fib     斐波那契   6 fib     → 8" << std::endl;
    
    std::cout << "\n🗂️  栈操作命令:" << std::endl;
    std::cout << "  clear   清空栈" << std::endl;
    std::cout << "  show    显示栈内容" << std::endl;
    std::cout << "  stack   显示栈内容(别名)" << std::endl;
    
    std::cout << "\n🎯 系统命令:" << std::endl;
    std::cout << "  help    显示此帮助" << std::endl;
    std::cout << "  ?       显示帮助(快捷方式)" << std::endl;
    std::cout << "  batch   批量计算示例" << std::endl;
    std::cout << "  quit    退出程序" << std::endl;
    std::cout << "  exit    退出程序(别名)" << std::endl;
    std::cout << "  q       退出程序(快捷方式)" << std::endl;
    
    std::cout << "\n💡 使用技巧:" << std::endl;
    std::cout << "  • 命令不区分大小写" << std::endl;
    std::cout << "  • 支持整数和浮点数" << std::endl;
    std::cout << "  • 表达式可以分多行输入" << std::endl;
    std::cout << "  • 使用空格分隔数字和操作符" << std::endl;
    
    std::cout << "\n📚 复杂表达式示例:" << std::endl;
    std::cout << "  (2 + 3) × 4        → 2 3 + 4 *" << std::endl;
    std::cout << "  10 - (6 ÷ 2)       → 10 6 2 / -" << std::endl;
    std::cout << "  (1+2)×(3+4)        → 1 2 + 3 4 + *" << std::endl;
    std::cout << "  √(9 + 16)          → 9 16 + sqrt" << std::endl;
    
    std::cout << "==========================================" << std::endl;
}

/**
 * @brief 批量计算示例
 * @param calc 计算器实例
 */
void batchCalculate(RPNCalculator& calc) {
    std::vector<std::string> batchExprs = {
        "5 5 +",
        "10 2 /", 
        "3 4 *",
        "15 7 -",
        "2 3 pow",
        "25 sqrt",
        "6 fib",
        "1 2 + 3 * 4 /",
        "5 1 2 + 4 * + 3 -",
        "2 3 + 4 5 + *"
    };
    
    std::vector<std::string> descriptions = {
        "简单加法: 5 + 5",
        "除法运算: 10 / 2",
        "乘法运算: 3 × 4", 
        "减法运算: 15 - 7",
        "幂运算: 2³",
        "平方根: √25",
        "斐波那契: F(6)",
        "复杂表达式: (1+2)×3÷4",
        "复合表达式: 5 + (1+2)×4 - 3",
        "嵌套表达式: (2+3)×(4+5)"
    };
    
    std::cout << "\n🔢 批量计算演示" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    for (size_t i = 0; i < batchExprs.size(); ++i) {
        std::cout << "\n#" << (i + 1) << " " << descriptions[i] << std::endl;
        std::cout << "表达式: " << batchExprs[i] << std::endl;
        
        try {
            processExpression(batchExprs[i], calc);
            if (!calc.empty()) {
                double result = calc.getResult();
                printResult(result);
            }
        } 
        catch (const std::exception& e) {
            std::cout << "❌ " << e.what() << std::endl;
        }
        
        calc.clear();
        if (i < batchExprs.size() - 1) {
            std::cout << "------------------------------------------" << std::endl;
        }
    }
    
    std::cout << "\n==========================================" << std::endl;
    std::cout << "✅ 批量演示完成！" << std::endl;
}

/**
 * @brief 交互式模式主循环
 * @param calc 计算器实例
 */
void interactiveMode(RPNCalculator& calc) {
    std::string input;
    int calculationCount = 0;
    
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, input);
        
        // 清理输入
        input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);
        
        if (input.empty()) {
            continue;
        }
        
        // 转换为小写检查命令
        std::string lowerInput = input;
        std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
        
        if (lowerInput == "quit" || lowerInput == "exit" || lowerInput == "q") {
            std::cout << "👋 感谢使用 RPN 计算器！" << std::endl;
            std::cout << "📊 本次会话完成了 " << calculationCount << " 次计算" << std::endl;
            break;
        } 
        else if (lowerInput == "batch") {
            batchCalculate(calc);
        } 
        else if (lowerInput == "help" || lowerInput == "?") {
            showHelp();
        }
        else {
            try {
                processExpression(input, calc);
                if (!calc.empty()) {
                    calculationCount++;
                    printResult(calc.getResult());
                }
            } 
            catch (const std::exception& e) {
                std::cout << "❌ " << e.what() << std::endl;
            }
        }
    }
}

// ==================== 主函数 ====================

/**
 * @brief 程序主入口
 * @return 程序退出代码
 */
int main() {
    // 设置输出格式
    std::cout << std::unitbuf;  // 无缓冲输出
    
    try {
        RPNCalculator calc;
        showWelcome();
        interactiveMode(calc);
    } 
    catch (const std::exception& e) {
        std::cerr << "💥 程序发生严重错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
