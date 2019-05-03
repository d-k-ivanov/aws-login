/*
* ---------------------------------------------------------------------------
*       Project :  aws-login
*       File    :  aws-login.cpp
*       Created :  4/4/2019 2:00:00 AM +0300
*       Author  :  Dmitriy Ivanov
* ---------------------------------------------------------------------------
* Copyright (c) 2019 Dmitriy Ivanov
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* ===========================================================================
*/


#include <iostream>
#include <string>
#include <map>

int main()
{
    std::map<std::string, int> Users{ { "Dmitriy", 35 }, { "Ivan", 25 }, { "Alex", 38 } };
    std::cout << "Initial user map:\n";
    for (const auto&[key, value] : Users)
        std::cout << key << ", " << value << '\n';
    std::cout << "\n";

    std::cout << "Update user map #1:\n";
    std::map UsersUpdate{ Users };
    if (auto[iter, isAdded] = UsersUpdate.insert_or_assign("John", 19); !isAdded)
        std::cout << iter->first << " updated...\n";

    for (const auto&[key, value] : UsersUpdate)
        std::cout << key << ", " << value << '\n';
    std::cout << "\n";

    std::cout << "Update user map #2:\n";
    if (auto[iter, isAdded] = UsersUpdate.insert_or_assign("John", 20); !isAdded)
        std::cout << iter->first << " updated...\n";

    for (const auto&[key, value] : UsersUpdate)
        std::cout << key << ", " << value << '\n';
    std::cout << "\n";

    std::system("pause");
    return 0;
}
