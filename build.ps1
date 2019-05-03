# Copyright (c) 2019 Dmitriy Ivanov
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Environment
$old_dir = Get-Location
${arch}    = (Get-CimInstance Win32_operatingsystem).OSArchitecture.split('-')[0]
${binPath} = (Join-Path $PSScriptRoot "bin")

function Set-VCVars {
    <#
    .SYNOPSIS
        Script to initialize all VC Variables.
    .DESCRIPTION
        Script to initialize all VC Variables.
    .PARAMETER Arch
        Architecture.
    .PARAMETER SDK
        Version of Windows SDK.
    .PARAMETER Platform
        Microsoft platform None, store or uwp.
    .PARAMETER VC
        Version Visual Studio.
    .PARAMETER Spectre
        Use for VS 2017 libraries with spectre mitigations.
    .PARAMETER Help
        Show help message.
    .INPUTS
        None
    .OUTPUTS
        None
    .NOTES
        Version:        1.0
        Author:         Dmitriy Ivanov
        Creation Date:  2019-01-14
    .EXAMPLE
        VC-Vars-All x86_amd64
        VC-Vars-All x86_amd64 10.0.10240.0
        VC-Vars-All x86_arm uwp 10.0.10240.0
        VC-Vars-All x86_arm onecore 10.0.10240.0 -vcvars_ver=14.0
        VC-Vars-All x64 8.1
        VC-Vars-All x64 store 8.1
    #>
    [CmdletBinding()]

    param (
        [ValidateNotNullOrEmpty()]
        [string]$Arch = "x86",
        [ValidateNotNullOrEmpty()]
        [string]$SDK = "8.1",
        [string]$Platform,
        [string]$VC,
        [switch]$Spectre,
        [switch]$Help
    )

    if ($Help) {
        Write-Host '
        Syntax:
            VC-Vars-All [-Arch <string>] [-SDK <string>] [-Platform <string>] [-VC <string>] [-Spectre] [-Help]
        where :
            [Arch]    : x86 | amd64 | x86_amd64 | x86_arm | x86_arm64 | amd64_x86 | amd64_arm | amd64_arm64
            [SDK]     : full Windows 10 SDK number (e.g. 10.0.10240.0) or "8.1" to use the Windows 8.1 SDK.
            [Platform]: {empty} | store | uwp
            [VC]      : {none} for default VS 2017 VC++ compiler toolset |
                        "14.0" for VC++ 2015 Compiler Toolset |
                        "14.1x" for the latest 14.1x.yyyyy toolset installed (e.g. "14.11") |
                        "14.1x.yyyyy" for a specific full version number (e.g. 14.11.25503)
            [Spectre] : Flag to set -vcvars_spectre_libs=spectre
            [Help]    : Flag to show this help message, all other parameters will be ignored
        '
        return
    }

    $VC_Distros = @(
        'C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat'
        'C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat'
        'C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsall.bat'
        'C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat'
        'C:\Program Files (x86)\Microsoft Visual Studio\2019\Preview\VC\Auxiliary\Build\vcvarsall.bat'
        'C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat'
        'C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat'
        'C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat'
        'C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat'
    )

    $cmd_string = "cmd /c "

    foreach($distro in $VC_Distros) {
        if (Test-Path "$distro") {
            $cmd_string += "`'`"" + $distro + "`" " + $Arch
            break
        }
    }

    if ($Platform) {
        $cmd_string += " " + $Platform
    }

    $cmd_string += " " + $SDK

    if ($VC) {
        $cmd_string += " -vcvars_ver=" + $VC
    }

    if ($Spectre) {
        $cmd_string += " -vcvars_spectre_libs=spectre"
    }

    $cmd_string += "` & set'"

    Write-Host "$cmd_string"

    Invoke-Expression $cmd_string |
    ForEach-Object {
        if ($_ -match "=") {
            $v = $_.split("="); set-item -force -path "ENV:\$($v[0])" -value "$($v[1])"
        }
    }
}

function build {
    Set-VCVars x64
    If (Get-Command ninja.exe -ErrorAction SilentlyContinue | Test-Path) {
        # Ninja
        cmake  -G "Ninja" -DCMAKE_CXX_COMPILER="cl.exe" -DCMAKE_C_COMPILER="cl.exe" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_MAKE_PROGRAM="ninja.exe" ..
    } ElseIF (Test-Path "C:\Program Files (x86)\Microsoft Visual Studio\2019\"){
        # VS 2019
        cmake -G "Visual Studio 16 2019" -A x64 ..
    } ElseIF (Test-Path "C:\Program Files (x86)\Microsoft Visual Studio\2017\"){
        # VS 2017
        cmake -G "Visual Studio 15 2017" -A x64 ..
    } Else {
        # Any available
        cmake ..
    }
    If ((Get-Command ninja.exe -ErrorAction SilentlyContinue | Test-Path)      -Or `
        (Test-Path "C:\Program Files (x86)\Microsoft Visual Studio\2019\")     -Or `
        (Test-Path "C:\Program Files (x86)\Microsoft Visual Studio\2017\")) {
            # VS Found
            cmake --build . --config "Release"
    } Else {
            # Any available
            cmake --build .
    }
}

New-Item build -ItemType Directory -ErrorAction SilentlyContinue
Set-Location build
build
Set-Location ${old_dir}
Remove-Item -Recurse -Force ./build
