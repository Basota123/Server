#include "bf.hpp"

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cmath>
#include <bitset>
#include <utility>
#include <unordered_map>

const std::string bf::task1(const std::string& n)
{
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
const std::string bf::task2(const std::string& func, const size_t& value, const size_t& arg_num)
{
    std::string residual{};

    if ((1ull << arg_num) > func.size()) 
    {
        residual = "Не правильно введены вектор функции или аргумент";
        return residual;
    }

    const size_t step = round((func.size() / (1ull << (arg_num + 1))));

    for (size_t i = value * step; i < func.size(); i += 2 * step)
        for (size_t j = 0; j < step; j++)
            residual.push_back(func[i+j]);

    return residual;
}

const std::string bf::task3(const std::string& first, const std::string& second, const size_t& arg_num)
{
    const std::string fun = first + second;
    const size_t step = round((fun.size() / (1ull << (arg_num))));

    std::string result{};

    if ((first.size() + second.size()) < (1ull << arg_num)) 
    {
        result = "Не правильно введены вектора функций или аргумент!";
        return result;
    }
        
    else if (first.size() != second.size())
    {
        result = "Не правильно введены остаточные!";
        return result;
    }
        

    for (size_t i = 0; i < first.size(); i += step)
    {
        for (size_t j = 0; j < step; j++) result.push_back(first[i+j]);
        for (size_t j = 0; j < step; j++) result.push_back(second[i+j]);
    }

    return result;
}

const std::string bf::task4(const std::string& input, const std::string& given_function)
{
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

const std::string bf::task5(const std::string& func, const std::string& essentials, const std::string& fictitious)
{
    size_t length = func.size();
    size_t args = 0;

    while(length > 1ull)
    {
        length /= 2ull;
        args++;
    }

    std::vector<bool> result(args, false);

    std::string ans1{}, ans2{};

    for (size_t i = 0; i < args; i++)
    {
        const std::string nuller = task2(func, 0, i);
        const std::string units = task2(func, 1, i);

        result[i] = (nuller == units);
    }

    for (size_t i = 0; i < args; i++)
    {
        if (!result[i]) ans1 += std::to_string(i + 1);
        else ans2 += std::to_string(i + 1);
    }

    std::string answer1{}, answer2{};

    if (ans1 == essentials) answer1 = "Вы правильно определили существенные переменные! ";
    else answer1 = "Вы неправильно определили существенные переменные, попробуйте ещё раз! ";

    if (ans2 == fictitious) answer2 = "Вы правильно определили фиктивные переменные! ";
    else answer2 = "Вы неправильно определили фиктивные переменные, попробуйте ещё раз! ";
    
    return answer1 + answer2;
}

const std::string bf::task6(const std::string& function, const std::string& user_input)
{
    const std::string DNF = task12(function);
    std::string ans{};

    if (user_input == function) ans = "Правильно!";
    else ans = "Неправильно!";

    return ans;
}

const std::string bf::task7(const std::string& function, const std::string& user_input)
{
    const std::string KNF = bf::build_knf(function);
    std::string ans{};

    if (user_input == function) ans = "Правильно!";
    else ans = "Неправильно!";

    return ans;
}

const std::string bf::task8(const std::string& f)
{
    std::string sdnf{};

    const size_t n = floor(log(f.size()) / log(2ull));

    for (size_t i = 0; i < (1ull << n); i++)
    {
        if (f[i] == '1')
        {
            std::string variables = "";

            // использую битсет для для предствления числа i 
            // в двоичном формате с фиксированным размером битовой строки равным 32
            const std::string binary = std::bitset<32>(i).to_string().substr(32-n);

            for (size_t j = 0; j < n; j++)
                variables += binary[j] == '0' ? "!x" + std::to_string(j + 1) + " & " : "x" + std::to_string(j + 1) + " & ";
            
            sdnf += "(" + variables.substr(0, variables.length() - 3) + ") | ";   
        }
    }

    return sdnf.length() > 3 ? sdnf.substr(0, sdnf.length() - 3) : "";
}

const std::string bf::task9(const std::string& f)
{
    std::string sknf{};

    const size_t n = floor(log(f.size()) / log(2ull));

    for (size_t i = 0; i < (1ull << n); i++)
    {
        if (f[i] == '1')
        {
            std::string variables = "";

            // использую битсет для для предствления числа i 
            // в двоичном формате с фиксированным размером битовой строки равным 32
            const std::string binary = std::bitset<32>(i).to_string().substr(32-n);

            for (size_t j = 0; j < n; j++)
                variables += binary[j] == '1' ? "!x" + std::to_string(j + 1) + " | " : "x" + std::to_string(j + 1) + " | ";
            
            sknf += "(" + variables.substr(0, variables.length() - 3) + ") & ";   
        }
    }

    return sknf.length() > 3 ? sknf.substr(0, sknf.length() - 3) : "";
}

const std::string bf::task10(const std::string& f, const std::vector<bool>& vbool)
{
    std::vector<bool> bf_classes
    {
        is_nuller(f), 
        is_units(f), 
        is_self_dual(f), 
        is_monotonic(f), 
        is_linear(f)
    };

    std::string ans{};

    if (bf_classes == vbool) ans = "Правильно!";
    else ans = "Неправильно!";

    return ans;
}

// на фронте определим правильно ли пользователь
// указал замкнутый класс
const std::string bf::task11(const std::string& f, const std::vector<bool>& input, const std::string& user_classes)
{
    std::vector<bool> result(5, true);
    const std::vector<std::string> system = parse(f, ' ');

    std::string ans1{}, ans2{}, ans3{};

    for (size_t i = 0; i < result.size(); i++)
    {
        result[0] = (is_nuller(system[i]) & result[0]);
        result[1] = (is_units(system[i]) & result[1]);
        result[2] = (is_self_dual(system[i]) & result[2]);
        result[3] = (is_monotonic(system[i]) & result[3]);
        result[4] = (is_linear(system[i]) & result[4]);
    }

    if (input == result)
    {
        ans1 = "Вы правильно определили набор функции. ";

        if (
        result[0] == false && 
        result[1] == false && 
        result[2] == false && 
        result[3] == false && 
        result[4] == false
        )
        {
            ans2 = "Система б.ф. полная. ";
        }

        else
        {
            ans2 = "Система б.ф. неполная, определите класс, к которому пренадлежит. ";
        }
    }

    for (size_t i = 0; i < result.size(); i++)
        if (result[i]) ans3 += std::to_string(i + 1);
    
    else 
    {
        ans1 = "Вы неправильно определили набор функции. ";
        ans2 = "Попробуйте еще раз. ";
    }
    
    return ans1 + ans2 + ans3;
}

const std::string bf::task12(const std::string& fucntion)
{
    std::string dnf{""};
    const size_t n = std::log2(fucntion.size());

    for (size_t i = 0; i < fucntion.size(); i++)
    {
        if (fucntion[i] == '1')
        {
            std::string variables{""};

            for (size_t j = 0; j < n; ++j)
            {
                if ((i & (1 << j)) == 0) variables += "!x" + std::to_string(j + 1) + " & ";
                else variables += "x" + std::to_string(j + 1) + " & ";
            }

            dnf += "(" + variables.substr(0, variables.length() - 3) + ") | ";
        }
    }
    return dnf.substr(0, dnf.size() - 3);
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

const std::string bf::build_knf(const std::string& function)
{
    std::string dnf;
    size_t n = std::log2(function.size()); 

    
    for (size_t i = 0; i < function.size(); ++i) {
        
        if (function[i] == '1') 
        {
            std::string term;
            
            for (size_t j = 0; j < n; ++j) 
            {    
                if ((i & (1ull << j)) == 0) term += "!x" + std::to_string(j + 1) + " | "; 
                else term += "x" + std::to_string(j + 1) + " | ";    
            }
            dnf += "(" + term.substr(0, term.size() - 3) + ") & "; // Add the term to the DNF
        }
    }

    return dnf.substr(0, dnf.size() - 3); // Return the DNF without the last & symbol
}

const std::vector<std::string> bf::parse(const std::string& f, char&& c)
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

