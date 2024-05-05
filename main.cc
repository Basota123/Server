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

struct TripleInput
{
    std::string first;
    std::string second;
    std::string third;
};

using str_pair_t = std::pair<std::string, std::string>;

const std::string get_input(const FunctionCallbackInfo<Value>& args);
const str_pair_t get_double_input_for_games(const FunctionCallbackInfo<Value>& args);
const TripleInput get_triple_input(const FunctionCallbackInfo<Value>& args);


void first_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const v8::String::Utf8Value str(isolate, args[0]);
    const std::string n(*str);

    const std::string function = bf::task1(n);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, function.c_str()).ToLocalChecked());
}

void second_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const std::string input{get_input(args)};

    const std::vector<std::string> vstr = bf::parse(input, ' ');

    const std::string function_name{bf::task2(vstr[0], std::stoull(vstr[1]), std::stoi(vstr[2]) - 1)};

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, function_name.c_str()).ToLocalChecked());

}

void third_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    const std::string input{get_input(args)};

    const std::vector<std::string> vstr = bf::parse(input, ' ');

    const std::string function = bf::task3(vstr[0], vstr[1], std::stoull(vstr[2]));

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, function.c_str()).ToLocalChecked());
}

void fourth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const str_pair_t input = get_double_input_for_games(args);

    const std::string ans = bf::task4(input.first, input.second);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, ans.c_str()).ToLocalChecked());
}

void fifth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const auto input = get_triple_input(args);

    const std::string result = bf::task5(input.first, input.second, input.third);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, result.c_str()).ToLocalChecked());
}

void sixth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const str_pair_t input = get_double_input_for_games(args);
    const std::string ans = bf::task6(input.first, input.second);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, ans.c_str()).ToLocalChecked());
}

void seventh_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const str_pair_t input = get_double_input_for_games(args);
    const std::string ans = bf::task7(input.first, input.second);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, ans.c_str()).ToLocalChecked());
}

void eighth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    const std::string input{get_input(args)};

    const std::string ans = bf::task8(input);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, ans.c_str()).ToLocalChecked());
}

void ninth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    const std::string input{get_input(args)};

    const std::string ans = bf::task9(input);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, ans.c_str()).ToLocalChecked());
}

void tenth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const str_pair_t input = get_double_input_for_games(args);

    std::vector<bool> vbool{};

    for (size_t i = 0; i < input.second.size(); ++i) 
        vbool.push_back(input.second[i] - '0');

    const std::string result = bf::task10(input.first, vbool);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, result.c_str()).ToLocalChecked());
}

void eleventh_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const auto input = get_double_input_for_games(args);
    std::vector<bool> vbool{};

    for (size_t i = 0; i < input.second.size(); ++i) 
        vbool.push_back(input.second[i] - '0');

    const std::string result = bf::task11(input.first, vbool);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, result.c_str()).ToLocalChecked());
}

void twelfth_task(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    const std::string input{get_input(args)};

    const std::string result = bf::task12(input);

    args.GetReturnValue().Set(String::NewFromUtf8(
    isolate, result.c_str()).ToLocalChecked());
}


void Initialize(Local<Object> exports) 
{
    NODE_SET_METHOD(exports, "first_task", first_task);
    NODE_SET_METHOD(exports, "second_task", second_task);
    NODE_SET_METHOD(exports, "third_task", third_task);
    NODE_SET_METHOD(exports, "fourth_task", fourth_task);
    NODE_SET_METHOD(exports, "fifth_task", fifth_task);
    NODE_SET_METHOD(exports, "sixth_task", sixth_task);
    NODE_SET_METHOD(exports, "seventh_task", seventh_task);
    NODE_SET_METHOD(exports, "eighth_task", eighth_task);
    NODE_SET_METHOD(exports, "ninth_task", ninth_task);
    NODE_SET_METHOD(exports, "tenth_task", tenth_task);
    NODE_SET_METHOD(exports, "eleventh_task", eleventh_task);
    NODE_SET_METHOD(exports, "twelfth_task", twelfth_task);
}   

NODE_MODULE(addon, Initialize)


const std::string get_input(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    
    v8::String::Utf8Value str(isolate, args[0]);
    std::string input(*str);

    return input;
}

const str_pair_t get_double_input_for_games(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    v8::String::Utf8Value str1(isolate, args[0]);    
    v8::String::Utf8Value str2(isolate, args[1]);    

    std::string first_input(*str1);
    std::string second_input(*str2);

    str_pair_t game_input{first_input, second_input};

    return game_input;
}

const TripleInput get_triple_input(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    TripleInput input;

    v8::String::Utf8Value str1(isolate, args[0]);    
    v8::String::Utf8Value str2(isolate, args[1]);   
    v8::String::Utf8Value str3(isolate, args[2]);   

    std::string f(*str1);
    std::string s(*str2);
    std::string t(*str3);

    input.first = f;
    input.second = s;
    input.third = t;

    return input;
}