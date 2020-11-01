#include "queue.h"
#include "node.h"
#include "utilities.h"

int main(int argc, char* argv[])
{
    Queue_entry temp;
    Extended_queue unemploymentLine;

    std::cout << std::boolalpha;
    std::cout << "Is the created queue empty: " << unemploymentLine.empty() << std::endl;

    unemploymentLine.append(3);
    unemploymentLine.append(6);
    unemploymentLine.append(9);
    unemploymentLine.append(12);
    unemploymentLine.append(15);

    unemploymentLine.retrieve(temp);
    std::cout << "In the front of the line: " << temp << std::endl;

    unemploymentLine.serve();
    std::cout << "Is the created queue empty: " << unemploymentLine.empty() << std::endl;

    unemploymentLine.retrieve(temp);
    std::cout << "In the front of the line: " << temp << std::endl;

    std::cout << "Is the soupline empty: " << unemploymentLine.empty() << std::endl;
    std::cout << "Is the soupline full: " << unemploymentLine.full() << std::endl;

    return 0;
}