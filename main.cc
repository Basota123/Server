#include <node.h>
#include <string>
#include <iostream>
#include <sstream>
#include "bf.hpp"
#include <utility>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Context;
using v8::Exception;


using str_pair_t = std::pair<std::string, std::string>;

std::string get_input(const FunctionCallbackInfo<Value>& args);
str_pair_t get_double_input_for_games(const FunctionCallbackInfo<Value>& args);

void first_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    v8::String::Utf8Value str(isolate, args[0]);
    std::string n(*str);

    std::string function = bf::task1(n);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, function.c_str()).ToLocalChecked());
}

void second_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    std::string input{get_input(args)};

    std::vector<std::string> vstr = bf::parse(input, ' ');

    if ((1ull << (stoull(vstr[2]) - 1) > vstr[0].size()))
    {
        isolate->ThrowException(Exception::RangeError(
            String::NewFromUtf8(
                isolate, 
                "Не правильный аргумент")
                .ToLocalChecked()
        ));
        return;
    }

    std::string function_name{bf::task2(vstr[0], std::stoull(vstr[1]), std::stoi(vstr[2]) - 1)};

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, function_name.c_str()).ToLocalChecked());

}

void third_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    std::string input{get_input(args)};

    std::vector<std::string> vstr = bf::parse(input, ' ');

    if ((vstr[0].size() + vstr[1].size()) < (1ull << std::stoull(vstr[2])))
    {
        isolate->ThrowException(Exception::Error(
            String::NewFromUtf8(
                isolate, 
                "Не правильный аргумент")
                .ToLocalChecked()
        ));
        return;
    }

    else if (vstr[0].size() != vstr[1].size())
    {
        isolate->ThrowException(Exception::Error(
            String::NewFromUtf8(
                isolate, 
                "Не правильные функции")
                .ToLocalChecked()
        ));
        return;
    }

    std::string function = bf::task3(vstr[0], vstr[1], std::stoull(vstr[2]));

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, function.c_str()).ToLocalChecked());
}

void fourth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    str_pair_t input = get_double_input_for_games(args);

    std::string ans = bf::task4(input.first, input.second);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, ans.c_str()).ToLocalChecked());
}

void fifth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    // std::string input{get_input(args)};

    // std::vector<std::string> vstr = bf::parse(input,' ');

    str_pair_t input = get_double_input_for_games(args);

    std::string result = bf::task5(input.first, input.second);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, result.c_str()).ToLocalChecked());
}


void sixth_task(const FunctionCallbackInfo<Value>& args);
void seventh_task(const FunctionCallbackInfo<Value>& args);

void eighth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    std::string input{get_input(args)};

    std::string ans = bf::task8(input);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, ans.c_str()).ToLocalChecked());
}

void ninth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    std::string input{get_input(args)};

    std::string ans = bf::task9(input);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, ans.c_str()).ToLocalChecked());
}

void tenth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    str_pair_t input = get_double_input_for_games(args);

    std::vector<bool> vbool{};

    for (size_t i = 0; i < input.second.size(); ++i) 
        vbool.push_back(input.second[i] - '0');

    std::string result = bf::task10(input.first, vbool);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, result.c_str()).ToLocalChecked());
}

void eleventh_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    str_pair_t input = get_double_input_for_games(args);

    std::vector<bool> vbool{};

    for (size_t i = 0; i < input.second.size(); ++i) 
        vbool.push_back(input.second[i] - '0');

    std::string result = bf::task11(input.first, vbool);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, result.c_str()).ToLocalChecked());
}

void twelfth_task(const FunctionCallbackInfo<Value>& args);


void Initialize(Local<Object> exports) 
{
    NODE_SET_METHOD(exports, "first_task", first_task);
    NODE_SET_METHOD(exports, "second_task", second_task);
    NODE_SET_METHOD(exports, "third_task", third_task);
    NODE_SET_METHOD(exports, "fourth_task", fourth_task);
    NODE_SET_METHOD(exports, "fifth_task", fifth_task);


    NODE_SET_METHOD(exports, "eighth_task", eighth_task);
    NODE_SET_METHOD(exports, "ninth_task", ninth_task);
    NODE_SET_METHOD(exports, "tenth_task", tenth_task);
}   

NODE_MODULE(addon, Initialize)


std::string get_input(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    std::string input{};

    for (int i = 0; i < args.Length(); i++)
    {
        if (args[i]->IsString())
        {
            v8::String::Utf8Value str(isolate, args[i]);
            input += *str;
        }
    }

    return input;
}

str_pair_t get_double_input_for_games(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    v8::String::Utf8Value str1(isolate, args[0]);    
    v8::String::Utf8Value str2(isolate, args[1]);    

    std::string first_input(*str1);
    std::string second_input(*str2);

    str_pair_t game_input{first_input, second_input};

    return game_input;
}

