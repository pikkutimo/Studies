#include <iostream>
#include <chrono>

int fibonacci(int);
long long numberOfCalls = 0;

int main(int argc, char* argv[])
{
    for (int i = 1; i < 40; ++i)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << i;
        fibonacci(i);
        auto stop = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << " required " << numberOfCalls << " calls and took " << diff.count() << " microseconds" << std::endl;
        numberOfCalls = 0;
    }
    return 0;
}

int fibonacci(int n)
/*    fibonacci: recursive version
Pre:  The parameter n is a nonnegative integer.
Post: The function returns the nth Fibonacci number.
*/
{
    numberOfCalls++;

    if (n <= 0)  return 0;
    else if (n == 1)  return 1;
    else              return fibonacci(n - 1) + fibonacci(n - 2);
}