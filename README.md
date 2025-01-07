# **MultiThread Calculator**

A multithreaded calculator application written in **C** that demonstrates the use of threads and parallelism to perform mathematical operations like addition, multiplication, factorials, and more.

---

## **Features**
- **Addition**: Parallel addition of numbers using multiple threads.
- **Multiplication**: Parallel multiplication of numbers.
- **Factorial Calculation**: Calculate the factorial of numbers in parallel.
- **Average Calculation**: Compute the average of numbers.
- **Dynamic Input**: Add numbers to the list during runtime.

---

## **Requirements**
- **C Compiler**: GCC or any C99-compliant compiler.
- **CMake**: Version 3.10 or higher.
- **POSIX Threads**: Required for multithreading.
  
### **Required Libraries**
- `pthread`: Used for multithreading.
  
To install required libraries on a **Debian-based** system (e.g., Ubuntu), use the following command:
```bash
sudo apt-get install libpthread-stubs0-dev
```
For **RedHat-based** systems (e.g., CentOS, Fedora), you can use:
```bash
sudo yum install glibc-devel
```

---

## **Usage**
### **1. Clone the Repository**
```bash
git clone https://github.com/yourusername/MultiThreadCalculator.git
cd MultiThreadCalculator
```

### **2. Build the Project**
```bash
mkdir build
cd build
cmake ..
make
```

### **3. Run the Program**
```bash
./bin/MultiThreadCalculator <thread_count>
```
- Replace `<thread_count>` with the number of threads you want to use. For example:
```bash
./bin/MultiThreadCalculator 4
```

### **4. Follow the Instructions**
The program will prompt you to:
1. Enter the number of elements.
2. Enter the numbers.
3. Choose operations (e.g., addition, multiplication, etc.).

---

## **Example**
```bash
./bin/MultiThreadCalculator 4
```
**Input:**
```
Enter the number of elements: 3
Enter the numbers:
Number 1: 2
Number 2: 4
Number 3: 6
Choose operation:
1. Add Numbers
2. Multiply Numbers
3. Calculate Factorial of Numbers
4. Calculate Average
5. Add a Number
6. Exit
```

**Output:**
```
The sum is: 12.00
The product is: 48.00
```
