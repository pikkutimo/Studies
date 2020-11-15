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
    n = 4;
    std::cout << "d) f(" << n << ") = " << solve(n) << std::endl; 
    n = 5;
    std::cout << "e) f(" << n << ") = " << solve(n) << std::endl; 
    n = 6;
    std::cout << "f) f(" << n << ") = " << solve(n) << std::endl;  

    return 0;
}

int solve(int n)
{
    if (n <= 1)
        return n;
    if (n % 2 == 0)
        return n + solve(n/2);
    else
        return solve((n+1)/2) + solve((n-1)/2);
}