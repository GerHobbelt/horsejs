// HorseCmd.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

int main()
{
    //start
    //读取./build.json ,找到sdkPath和appPath，启动sdkPath下的HorseJs.exe，并把appPath传给HorseJs.exe
    
    //build
    //把appPath下的所有文件都以资源的形式打包到HorseJs.exe文件中，最后给HorseJs.exe改名
    //相应的还会处理icon和签名的事
    std::cout << "Hello World!\n";
}
