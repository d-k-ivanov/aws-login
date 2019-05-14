/*
* ---------------------------------------------------------------------------
*       Project :  aws-login
*       File    :  aws-login.cpp
*       Created :  4/4/2019 2:00:00 AM +0300
*       Author  :  Dmitriy Ivanov
* ---------------------------------------------------------------------------
*  Copyright (c) 2019 Dmitriy Ivanov
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
* ===========================================================================
*/

#include <cxxopts.hpp>

// STL
#include <iostream>
#include <filesystem>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    cxxopts::Options options(fs::path(argv[0]).filename().string(), "Description");
    options
        .positional_help("[optional args]")
        .show_positional_help();

    options.add_options()
        ("h,help", "Show help")
        ("l,list", "List of known AWS credentials");

    options.custom_help("[-h] [-l]");
    auto result = options.parse(argc, argv);

    if (result.count("help")) std::cout << options.help() << std::endl;

    std::system("pause");
    return 0;
}
