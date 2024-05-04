#include <node.h>
#include <string>
#include <iostream>
#include <sstream>
#include "bf.hpp"

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Context;
using v8::Exception;

std::string get_input(const FunctionCallbackInfo<Value>& args);

void first_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    v8::String::Utf8Value str(isolate, args[0]);
    std::string n(*str);

    if (std::stoull(n) > 61)
    {
        isolate->ThrowException(Exception::RangeError(
            String::NewFromUtf8(
                isolate, 
                "n должно быть меньше 61")
                .ToLocalChecked()
        ));
        return;
    }

    std::string function = bf::task1(n);

    const char* function_name = function.c_str();

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, function_name).ToLocalChecked());
}

void second_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    std::string input{get_input(args)};

    std::vector<std::string> vstr = bf::parse(input, ' ');

    if ((1ull << (stoull(vstr[2]) + 1) > vstr[0].size()))
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
    std::string input{get_input(args)};

    std::vector<std::string> vstr = bf::parse(input,' ');

    std::string ans = bf::task4(vstr[0], vstr[1]);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, ans.c_str()).ToLocalChecked());
}

void fifth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    std::string input{get_input(args)};

    std::vector<std::string> vstr = bf::parse(input,' ');
    std::vector<bool> vbool{};

    for (size_t i = 0; i < vstr[1].size(); ++i) 
        vbool[i] = (vstr[1][i] - '0');

    bool result = bf::task5(vstr[0], vbool);

    std::stringstream ss{""};
    ss << std::boolalpha << result;

    const char* ans = ss.str().c_str();

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, ans).ToLocalChecked());
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


void tenth_task(const FunctionCallbackInfo<Value>& args);
void eleventh_task(const FunctionCallbackInfo<Value>& args);
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