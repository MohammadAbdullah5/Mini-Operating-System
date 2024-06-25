#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>  
#include <sys/wait.h>
using namespace std;

void allocateResources()
{
    int requiredRAM = 256;
    int requiredHDD = 10;
    int requiredCore = 1;

    int fd_total_to_required = open("total_to_required", O_WRONLY);

    write(fd_total_to_required, &requiredRAM, sizeof(requiredRAM));
    write(fd_total_to_required, &requiredHDD, sizeof(requiredHDD));
    write(fd_total_to_required, &requiredCore, sizeof(requiredCore));

    close(fd_total_to_required);
}

int main()
{
    allocateResources();
    sleep(1);
    char buffer[256];
    int fd_total_to_required = open("total_to_required", O_RDONLY);
    ssize_t bytesRead = read(fd_total_to_required, buffer, sizeof(buffer));
    close(fd_total_to_required);
    if (bytesRead > 0)
    {
        buffer[bytesRead] = '\0';
        if (strcmp(buffer, "Resources not available") == 0)
        {
            return 0;
        }
        else
        {
            int firstOperand;
            int secondOperand;
            string operato; 
            bool flag = true;
        
            while (flag)
            {
                cout << "Enter first operand: ";
                cin >> firstOperand;
        
                cout << "Enter second operand: ";
                cin >> secondOperand;
        
                cout << "Enter operator (+, -, *, /, %): ";
                cin >> operato;
        
                if(operato == "+")
                {
                    cout << "Sum: " << firstOperand + secondOperand << endl;
                }
                else if(operato == "-")
                {
                    cout << "Difference: " << firstOperand - secondOperand << endl;
                }
                else if(operato == "*")
                {
                    cout << "Product: " << firstOperand * secondOperand << endl;
                }
                else if(operato == "/")
                {
                    cout << "Quotient: " << firstOperand / secondOperand << endl;
                }
                else if(operato == "%")
                {
                    cout << "Modulus: " << firstOperand % secondOperand << endl;
                }
                else
                {
                    cout << "Invalid operator" << endl;
                }
                string choice;
                cout << "Do you want to continue? (y/n): ";
                cin >> choice;
        
                if(choice == "n")
                {
                    flag = false;
                }
            }
            cout << "Exiting Calculator." << endl;
            mkfifo("required_to_total", 0666);
            
            int fd_required_to_total = open("required_to_total", O_WRONLY);
            
            const char* message = "Completed";
            write(fd_required_to_total, message, strlen(message));
            close(fd_required_to_total);
        
            exit(0);
        }
    }
    return 0;
}