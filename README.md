# FileStream and TMString Class Replicas

## Overview
This repository contains custom implementations of:
- `OutputFileStream` and `InputFileStream` classes for file handling, replicating C++'s file stream classes.
- `TMString` class, a custom string class replicating common string operations in C++.

---

## Class Details

### 1. OutputFileStream Class

The `OutputFileStream` class handles writing to files with modes such as:
- **append**: Opens file in append mode.
- **overwrite**: Overwrites the file.
- **binary**: Opens file in binary mode (for both append and overwrite).

#### Key Methods
- **open**: Opens a file with the specified mode.
- **close**: Closes the open file.
- **fail**: Returns `1` if the last operation failed, `0` otherwise.
- **operator<<**: Overloads `<<` for writing characters, strings, and integers to a file.
- **write**: Writes raw data to the file.

#### Example Usage
```cpp
OutputFileStream f("output.txt", OutputFileStream::append);
f << "Hello, World!" << '\n';
f << 123 << '\n';
f.close();
```

### 2. InputFileStream Class

The `InputFileStream` class handles reading from files with modes such as:

- reading: Opens the file for reading.
- binary: Opens the file in binary read mode.

`Key Methods`
- **open**: Opens a file in read or binary mode.
- **close**: Closes the file.
- **fail**: Returns 1 if the last operation failed, 0 otherwise.
- **operator>>**: Overloads >> for reading characters, strings, and integers.
- **read**: Reads raw data from the file.


#### Example Usage
```cpp
InputFileStream f("output.txt");
int number;
string text;
f >> text;
f >> number;
f.close();
```

### 3. TMString Class

The `TMString` class is a custom string class that supports string operations like comparison, concatenation, and assignment.

`Key Operators`

Comparison Operators: <, >, <=, >=, ==, !=
Concatenation Operators: +=, +
Assignment Operators: =

### Example Usage
```cpp
TMString a = "Hello";
TMString b = "World";
TMString c = a + b;
cout << c << endl; // Outputs "HelloWorld"
```

Compilation and Execution
Compiling the Code
To compile and run the code, execute the following commands:

```sh
g++ -o main main.cpp FileStream.cpp TMString.cpp
```

### Example Main Program

```#include "FileStream.cpp"
#include "TMString.cpp"
#include <iostream>

int main() {
    // Demonstrate FileStream
    OutputFileStream outFile("example.txt", OutputFileStream::overwrite);
    outFile << "Hello, World!" << '\n';
    outFile.close();

    InputFileStream inFile("example.txt");
    TMString content;
    inFile >> content;
    inFile.close();
    std::cout << "Content read from file: " << content << std::endl;

    // Demonstrate TMString
    TMString a = "Hello";
    TMString b = "World";
    TMString c = a + b;
    std::cout << "Concatenated string: " << c << std::endl;

    return 0;
}
```

# Contact
##### Email: itskanishk36@gmail.com
##### LinkedIn: https://www.linkedin.com/in/kanishk-chouhan/
