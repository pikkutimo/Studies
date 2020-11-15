#include <iostream>

int gcd(int, int);

int main()
{
    int x{0};
    int y{0};

    std::cout << "Please input two positive integers separated by space and let the program find the greatest common denominator." << std::endl;
    
    std::cin >> x >> y;
       
    try
    {
        std::cout << "The greatest common denominator of " << x << " and " << y << " is " << gcd(x, y) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

int gcd(int x, int y)
{
    while (x != y)  
    {  
        if (x > y)      
            x = x - y;      
        else    
            y = y - x;      
    }
    
    return x;
}