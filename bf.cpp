#include "bf.hpp"

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cmath>
#include <bitset>
#include <utility>
#include <unordered_map>

//setlocale(LC_ALL, "RU");

std::string bf::task1(const std::string& n)
{
    //if (n > 61) throw std::invalid_argument("n must be less than 61");

    srand(time(nullptr));
    const size_t SIZE = std::stoull(n);

    std::string f{};
    for (size_t i = 0; i < (1ull << SIZE); i++)
    {
        f.push_back(rand() % 2 + '0');
    }

    return f;
}

// нахожу остаточную по аргументу от 0 до n-1
std::string bf::task2(const std::string& func, const size_t& value, const size_t& arg_num)
{
    // if ((1 << arg_num) > func.size()) 
       // throw std::invalid_argument("Invalid argument");

    std::string residual{};
    const size_t step = round((func.size() / (1ull << (arg_num + 1))));

    for (size_t i = value * step; i < func.size(); i += 2 * step)
        for (size_t j = 0; j < step; j++)
            residual.push_back(func[i+j]);

    return residual;
}

std::string bf::task3(const std::string& first, const std::string& second, const size_t& arg_num)
{
    // if ((first.size() + second.size()) < (1 << arg_num)) 
    //     throw std::invalid_argument("Invalid argument");
    // if (first.size() != second.size())
    //     throw std::invalid_argument("Invalid functions");

    std::string fun = first + second;
    const size_t step = round((fun.size() / (1ull << (arg_num))));

    std::string result{};
    for (size_t i = 0; i < first.size(); i += step)
    {
        for (size_t j = 0; j < step; j++) result.push_back(first[i+j]);
        for (size_t j = 0; j < step; j++) result.push_back(second[i+j]);
    }

    return result;
}

std::string bf::task4(const std::string& input)
{

    std::string given_function{task1("2")};

    // std::cout << "Вам дана функция: " << given_function << '\n';
    // std::cout << "Назовите ее имя, вам нужно ввести его словами\n";

    std::unordered_map<std::string, std::string> f_names = {
        {"Нулевая", "0000"},
        {"Конъюнкция", "0001"},
        {"Дизъюнкция", "0111"},
        {"Сложение", "0110"},
        {"Штрих Шеффера", "1110"},
        {"Стрелка Пирса", "1000"},
        {"Импликация", "1101"},
        {"Эквивалентность", "1001"},
        {"Коимпликация", "0010"},
        {"Обратная импликация", "1011"},
        {"Обратная коимпликация", "0100"},
        {"Отрицание первого аргумента", "1100"},
        {"Отрицание второго аргумента", "1010"},
        {"Первый аргумент", "0011"},
        {"Второй аргумент", "0101"},
        {"Единичная", "1111"}
    };

    std::string ans{};

    if (f_names[input] == given_function) ans = "Правильно!";
    else ans = "Неправильно!";

    return ans;
}

std::vector<bool> bf::task5(const std::string& func, const std::vector<bool>& essentials)
{
    size_t length = func.size();
    size_t args = 0;

    while(length > 1ull)
    {
        length /= 2ull;
        args++;
    }

    std::vector<bool> result(args, false);

    for (size_t i = 0; i < args; i++)
    {
        std::string nuller = task2(func, 0, i);
        std::string units = task2(func, 1, i);

        result[i] = (nuller == units);
    }

    return result;
}




std::string bf::task8(const std::string& f)
{
    std::string sdnf{};
    const size_t n = floor(log(f.size()) / log(2ull));

    for (size_t i = 0; i < (1ull << n); i++)
    {
        if (f[i] == '1')
        {
            std::string variables = "";

            const std::string binary = std::bitset<32>(i).to_string().substr(32-n);

            for (size_t j = 0; j < n; j++)
                variables += binary[j] == '0' ? "!x" + std::to_string(j + 1) + " & " : "x" + std::to_string(j + 1) + " & ";
            
            sdnf += "(" + variables.substr(0, variables.length() - 3) + ") | ";   
        }
    }

    return sdnf.length() > 3 ? sdnf.substr(0, sdnf.length() - 3) : "";
}

std::string bf::task9(const std::string& f)
{
    std::string sknf{};
    const size_t n = floor(log(f.size()) / log(2ull));

    for (size_t i = 0; i < (1ull << n); i++)
    {
        if (f[i] == '1')
        {
            std::string variables = "";

            const std::string binary = std::bitset<32>(i).to_string().substr(32-n);

            for (size_t j = 0; j < n; j++)
                variables += binary[j] == '1' ? "!x" + std::to_string(j + 1) + " | " : "x" + std::to_string(j + 1) + " | ";
            
            sknf += "(" + variables.substr(0, variables.length() - 3) + ") & ";   
        }
    }

    return sknf.length() > 3 ? sknf.substr(0, sknf.length() - 3) : "";
}

std::vector<bool> bf::task10(const std::string& f)
{
    return std::vector
    {
        is_nuller(f), 
        is_units(f), 
        is_self_dual(f), 
        is_monotonic(f), 
        is_linear(f)
    };
}

std::vector<bool> bf::task11(const std::string& f)
{
    std::vector<bool> result = {false, false, false, false, false};
    const std::vector<std::string> system = parse(f, ',');

    for (size_t i = 0; i < result.size(); i++)
    {
        result[0] = is_nuller(system[i]);
        result[1] = is_units(system[i]);
        result[2] = is_self_dual(system[i]);
        result[3] = is_monotonic(system[i]);
        result[4] = is_linear(system[i]);
    }

    bool complete = true;
    for (bool res : result) {
        if (res) {
            complete = false;
            break;
        }
    }

    result.push_back(complete);

    return result;
}




bool bf::is_nuller(const std::string& f)
{
    return f[0] == '0';
}

bool bf::is_units(const std::string& f)
{
    return f[f.size() - 1] == '1';
}

bool bf::is_self_dual(const std::string& f)
{
    const size_t n = f.size();

    for (size_t i = 0; i < n; ++i)
        if (f[i] != f[n - 1- i])
            return false;

    return true;
}

bool bf::is_monotonic(const std::string& f)
{
    const size_t n = f.size();

    for (size_t i = 0; i < n; i++)
        for (std::size_t j = i + 1; j < n; j++)
            if (((f[i] - '0') > (f[j] - '0')) && (i & j) == i) 
                return false;
    
    return true;
}


bool bf::is_linear(const std::string& f)
{
    const size_t n = f.size();
    for (size_t i = 0; i < n; i++)
        for (size_t j = i+1; j < n; j++) 
            for (size_t k = j+1; k < n; k++) 
                for (size_t l = k+1; l < n; l++) 
                    if ((f[i] - '0') ^ (f[j] - '0') ^ (f[k] - '0') ^ (f[l] - '0'))
                        return false;

    return true;
}


std::vector<std::string> bf::parse(const std::string& f, char&& c)
{
    std::vector<std::string> result;
    std::string temp;

    for (size_t i = 0; i < f.length(); i++)
    {
        if (f[i] != c) 
        {
            temp.push_back(f[i]);
        } 
        else 
        {
            result.push_back(temp);
            temp.clear();
        }
    }

    if (!temp.empty()) 
    {
        result.push_back(temp);
    }

    return result;
}

// std::vector<std::vector<size_t>> bf::generate_truth_table(const size_t& n, const std::string& boolfunc)
// {
//     std::vector<std::vector<size_t>> truth_table(pow(2, n), std::vector<size_t>(n + 1));
//     for (size_t i = 0; i < (1ull << n); i++)
//     {
//         for (size_t j = n - 1ull; j >= 0ull; --j)
//         {
//             truth_table[i][j] = (i >> j) & 1ull;
//         }
//         truth_table[i][n] = boolfunc[i] - '0';
//     }
//     return truth_table;
// }