#include <iostream>
#include <iomanip> // Include the <iomanip> header for std::put_time
#include <chrono>
#include <sys/wait.h>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
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

            auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
            system("clear");

            cout << "                                                                                                " << endl;
            cout << "                                                                                                " << endl;
            cout << "                         Abdullah's Macintosh                                                   " << endl;
            cout << "                      " << put_time(localtime(&time), "%c") << "\n\n" << "                                                                         " << endl;
            cout << "                                                                                                " << endl;
            cout << "                                                                                                " << endl;
            cout << "Press enter to return...";
            cin.get();

            cout << "Exiting Clock." << endl;
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

