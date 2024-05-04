#pragma once

#include <string>
#include <vector>

class bf
{
public:
    static std::string task1(const std::string&);
    static std::string task2(const std::string&, const size_t&, const size_t&);
    static std::string task3(const std::string&, const std::string&, const size_t&);
    static std::string task4(const std::string&, const std::string&);
    static bool task5(const std::string&, const std::vector<bool>&);
    static std::string task6(const std::string&);
    static std::string task7(const std::string&);
    static std::string task8(const std::string&);
    static std::string task9(const std::string&);
    static std::vector<bool> task10(const std::string&);
    static std::vector<bool> task11(const std::string&);


private:
// вспомогательные методы для задания 10, 11
    static bool is_nuller(const std::string&);
    static bool is_units(const std::string&);
    static bool is_self_dual(const std::string&);
    static bool is_monotonic(const std::string&);
    static bool is_linear(const std::string&);

public:
// парсинг строки с множеством функций
    static std::vector<std::string> parse(const std::string&, char&&);

    // static std::vector<std::vector<size_t>> generate_truth_table(const size_t&, const std::string&);

};

