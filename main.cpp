#include <iostream>
#include <fstream>
#include <vector>

#include "VirtualMachine.h"
#include "RuntimeFrame.h"

template <typename T>
std::vector<T> ReadFile(const std::string& filename)
{
    // open the file:
    std::ifstream file(filename, std::ios::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    const std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<T> fileData(fileSize);
    file.read(reinterpret_cast<char *>(&fileData[0]), fileSize);
    fileData.push_back(Op::Code::Return);
    return fileData;
}

int main(int argc, char** argv)
{
    /*
    if (argc < 2)
    {
        std::cerr << "Usage is 'noble <filename>'\n";
        return -1;
    }
    */
    const std::string fileName = "test";//argv[1];

    Noble::VM::Frame frame;
    frame.ops = ReadFile<Op::Type>(fileName + ".naf");
    frame.constants = ReadFile<ValueType>(fileName + ".ndf");

    Noble::VM::VirtualMachine vm;
    vm.RunFrame(frame);

    return 0;
}