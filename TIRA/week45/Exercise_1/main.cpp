#include "queue.h"
#include "node.h"
#include "utilities.h"

int main(int argc, char* argv[])
{
    Queue_entry temp;
    Queue unemploymentLine;
    Queue soupLine;

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

    Queue *copyOfQueue = new Queue(unemploymentLine);
    std::cout << "Is the created copy empty: " << copyOfQueue->empty() << std::endl;

    delete copyOfQueue;

    std::cout << "Is the soupline empty: " << soupLine.empty() << std::endl;

    soupLine = unemploymentLine;

    std::cout << "Is the soupline empty: " << soupLine.empty() << std::endl;

    return 0;
}