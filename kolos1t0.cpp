#include <iostream>
#include <fstream>

struct MyStruct {
    int i;
    double d;
};

MyStruct* createArray(int size, const MyStruct& prototype) {
    MyStruct* arr = new MyStruct[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = prototype;
    }
    return arr;
}

void writeArrayToFile(const char* filename, int size, const MyStruct& prototype) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }

    file << size << "\n";
    for (int i = 0; i < size; ++i) {
        file << prototype.i << " " << prototype.d << "\n";
    }

    file.close();
}

MyStruct* readArrayFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for reading." << std::endl;
        return nullptr;
    }

    int size;
    file >> size;
    MyStruct* arr = new MyStruct[size];
    for (int i = 0; i < size; ++i) {
        file >> arr[i].i >> arr[i].d;
    }

    file.close();
    return arr;
}

int main() {
    const char* filename = "array.txt";
    MyStruct prototype = { 1, 3.14 };
    MyStruct* arr = createArray(83, prototype);

    writeArrayToFile(filename, 83, prototype);

    MyStruct* arr2 = readArrayFromFile(filename);

    bool areArraysIdentical = true;
    for (int i = 0; i < 83; ++i) {
        if (arr[i].i != arr2[i].i || arr[i].d != arr2[i].d) {
            areArraysIdentical = false;
            break;
        }
    }

    std::cout << "Are the arrays identical? " << (areArraysIdentical ? "Yes" : "No") << std::endl;

    delete[] arr;
    delete[] arr2;

    return 0;
}