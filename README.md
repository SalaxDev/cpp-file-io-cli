# File I/O Command

[![Windows](https://img.shields.io/badge/Windows-7+-blue?logo=windows)](https://www.microsoft.com/windows)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C++-20+-00599C?logo=c%2B%2B)](https://isocpp.org/)

fioc Is a C/C++ CLI Tool That Handles Simple Commands Such As Creating Folder, Reading Files, Creating Directory, etc...

```bash
# Create files
fioc --file-create hello.txt "Hello World"

# Create Folders
fioc --new-folder hello/world

# Get Help And Other Commands
fioc --help
```

## 🛠️ Installation
## Option 1: Download Binary
Grab the latest fioc.exe from Releases and drop it anywhere in your PATH.
#### Note That Program is not Signed and Antivirus Will Give Virus Warning

## Option 2: Build from Source
```bash

git clone https://github.com/SalaxDev/fioc.git
cd fioc
cmake . -B build -DCMAKE_BUILD_TYPE=Release
```
