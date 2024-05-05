#pragma once

#include <string>
#include <vector>

class bf
{
public:
    static const std::string task1(const std::string&);
    static const std::string task2(const std::string&, const size_t&, const size_t&);
    static const std::string task3(const std::string&, const std::string&, const size_t&);
    static const std::string task4(const std::string&, const std::string&);
    static const std::string task5(const std::string&, const std::string&, const std::string&);
    static const std::string task6(const std::string&, const std::string&);
    static const std::string task7(const std::string&, const std::string&);
    static const std::string task8(const std::string&);
    static const std::string task9(const std::string&);
    static const std::string task10(const std::string&, const std::vector<bool>&);
    static const std::string task11(const std::string&, const std::vector<bool>&, const std::string&);
    static const std::string task12(const std::string&);

    static const std::string build_knf(const std::string&);
    
private:
// вспомогательные методы для задания 10, 11
    static bool is_nuller(const std::string&);
    static bool is_units(const std::string&);
    static bool is_self_dual(const std::string&);
    static bool is_monotonic(const std::string&);
    static bool is_linear(const std::string&);
    

public:
// парсинг строки с множеством функций
    static const std::vector<std::string> parse(const std::string&, char&&);
    // static std::string create_dnf(const std::string&);
    

};

