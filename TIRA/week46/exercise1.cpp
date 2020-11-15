#include <iostream>

int solve(int);

int main()
{
    int n = 1;
    std::cout << "a) f(" << n << ") = " << solve(n) << std::endl;
    n = 2;
    std::cout << "b) f(" << n << ") = " << solve(n) << std::endl; 
    n = 3;
    std::cout << "c) f(" << n << ") = " << solve(n) << std::endl; 
    n = 99;
    std::cout << "d) f(" << n << ") = " << solve(n) << std::endl; 
    n = 100;
    std::cout << "e) f(" << n << ") = " << solve(n) << std::endl; 
    n = 128;
    std::cout << "f) f(" << n << ") = " << solve(n) << std::endl;  

    return 0;
}

int solve(int n)
{
    if (n <= 0)
        return 0;
    if (n % 2 == 0)
        return solve(n/2);
    else
        return 1 + solve(n-1);
}