#pragma once

#include "common.hpp"

enum class Privilege {
    Kernel = 0,
    Ring1 = 1,
    Ring2 = 2,
    User = 3
};

enum class DescType {
    System = 0,
    CodeorData = 1
};

enum class Executable {
    Disable = 0,
    Enable = 1
};

// for data segment
enum class Direction {
    Up = 0,
    Down = 1
};

// for code segment
// if Enable, this segment can be executed from equal or lower privilege level
// if Disable, this segment can only be executed from the setting privilege
enum class Conforming {
    Disable = 0,
    Enable = 1
};

enum class AllowReadOrWrite{
    Disable = 0,
    Enable = 1
};

enum class Granularity {
    Byte = 0,
    Page = 1
};

enum class Size {
    bit_16 = 0,
    bit_32 = 1
};

class GDT {
    private:
    public:
        void Load();
        void createEntry();
        void AddEntry();
        static void test();
};
