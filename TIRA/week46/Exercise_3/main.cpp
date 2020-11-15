#include <iostream>
#include <chrono>
#include <vector>

const int disks = 3;  // Make this constant much smaller to run program.
void move(int count, int start, int finish, int temp);

/*
Pre:  None.
Post: The simulation of the Towers of Hanoi has terminated.
*/
int main()
{
    std::vector<long> times;
    for(int i = 7 ; i < 16; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        move(i, 1, 3, 2);
        auto stop = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        times.emplace_back(diff.count());
    }

    for (auto time : times)
    {
        std::cout << time << std::endl;
    }
    return 0;
}

void move(int count, int start, int finish, int temp)
{
   if (count > 0) {
      move(count - 1, start, temp, finish);
      
      move(count - 1, temp, finish, start);
   }
}
