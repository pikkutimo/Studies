#include <iostream>

const int disks = 9;  // Make this constant much smaller to run program.
void move(int count, int start, int finish, int temp);

/*
Pre:  None.
Post: The simulation of the Towers of Hanoi has terminated.
*/
int main()
{
   move(disks, 1, 3, 2);
}

void move(int count, int start, int finish, int temp)
/*    move: iterative version
Pre:  Disk count is a valid disk to be moved.
Post: Moves count disks from start to finish using temp for temporary
      storage.
*/
{
   int swap;            //  temporary storage to swap towers
   while (count > 0) {  //  Replace the if statement with a loop.
      move(count - 1, start, temp, finish);  //  first recursive call
      std::cout << "Move disk " << count << " from " << start
           << " to " << finish << "." << std::endl;
      count--;  //  Change parameters to mimic the second recursive call.
      swap = start;
      start = temp;
      temp = swap;
   }
}