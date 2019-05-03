/*
* ---------------------------------------------------------------------------
*       Project :  aws-login
*       File    :  unicode.cpp
*       Created :  04.05.2019 2:26:28 +0300
*       Author  :  Dmitriy Ivanov
*       Company :  Ormco
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

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    std::string str = "Pa’s väi wöl Θέλει נחמדה いろはにほ 다람쥐 ā łódź Съешь Češće žušč เป็นมนุ بىشەم  中国智造 視野無限廣";
    std::cout << str << '\n';
    std::system("pause");
    return 0;
}
