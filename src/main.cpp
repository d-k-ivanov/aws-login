/*
* ---------------------------------------------------------------------------
*       Project :  aws-login
*       File    :  aws-login.cpp
*       Created :  4/4/2019 2:00:00 AM +0300
*       Author  :  Dmitry Ivanov
* ---------------------------------------------------------------------------
*  Copyright (c) 2021 Dmitry Ivanov
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

    int exitCode = 0;

    cxxopts::Options options(fs::path(argv[0]).filename().string(), "Description");
    options
        .positional_help("[optional args]")
        .show_positional_help();

    options.add_options()
        ("h,help",   "Show help")
        ("l,list",   "List known AWS credentials")
        ("u,use",    "Use AWS credentials")
        ("a,add",    "Add AWS credentials")
        ("d,delete", "Delete AWS credentials");

    options.custom_help("[-h] [-l] [-u] [-a] [-d]");

    try {
        auto result = options.parse(argc, argv);

        if (result.count("help") || argc == 1 ) {
            std::cout << options.help() << '\n';
            std::system("pause");
            exit(0);
        }
        else if (result.count("list")) {
            std::cout << "List known AWS credentials\n";
        }
        else if (result.count("use")) {
            std::cout << "Use AWS credentials\n";
        }
        else if (result.count("add")) {
            std::cout << "Add AWS credentials\n";
        }
        else if (result.count("delete")) {
            std::cout << "Delete AWS credentials\n";
        }
    }
    catch(const cxxopts::OptionException & e) {
        std::cout << "Error: " << e.what() << " Showing help message...\n";
        std::cout << options.help() << '\n';
        exitCode = 1;
    }

    std::system("pause");
    return exitCode;
}
