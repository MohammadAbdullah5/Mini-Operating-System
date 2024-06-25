#include <iostream>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <cstdlib>
#include <csignal>
#include <cstring>
using namespace std;

float totalRAM;
float totalHDD;
int totalCores;
int availableCores;
float availableRAM;
float availableHDD;

void boot()
{
    cout << "RAM: " << totalRAM << "GB" << " Hard Drive: " << totalHDD << " Processing Cores: " << totalCores << endl;
    cout << "Booting..." << endl;
    sleep(1);
    cout << "Booted" << endl;
    sleep(1);
    system("clear");

    cout << "                                                                                                                       " << endl;
    cout << "                                                                                                                       " << endl;
    cout << "                                                Abdullah's Macintosh                                                   " << endl;
    cout << "                                                                                                                       " << endl;
    cout << "                                                                                                                       " << endl;
    cout << "                                                                                                                       " << endl;
    sleep(2);
    system("clear");
}

void goodbye()
{
    sleep(1);
    system("clear");

    cout << "                                                                                                                       " << endl;
    cout << "                                                                                                                       " << endl;
    cout << "                                                Abdullah's Macintosh                                                   " << endl;
    cout << "                                                  Have a nice day                                                      " << endl;
    cout << "                                                                                                                       " << endl;
    cout << "                                                                                                                       " << endl;
    sleep(2);
    system("clear");
}

int showMenu()
{
    int choice;
    system("clear");
    cout << "Abdullah-Macbook" << endl;
    cout << "1. Calculator" << endl;
    cout << "2. Notepad" << endl;
    cout << "3. Clock" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose your option.....";
    cin >> choice;
    return choice;
}

void *allocateToCalculator(void *arg)
{
    pid_t pid = fork();
    mkfifo("total_to_required", 0666);
    mkfifo("required_to_total", 0666);
    int ppid;
    if (pid == 0) 
    { 
        execlp("gnome-terminal", "gnome-terminal", "--", "./Calculator.exe", NULL);
    } 

    else if (pid > 0) 
    { 
        sleep(1);
        int fd_total_to_required = open("total_to_required", O_RDONLY);
        int requiredRAM, requiredHDD, requiredCore;
        read(fd_total_to_required, &requiredRAM, sizeof(requiredRAM));
        read(fd_total_to_required, &requiredHDD, sizeof(requiredHDD));
        read(fd_total_to_required, &requiredCore, sizeof(requiredCore));
        close(fd_total_to_required);

        if (requiredRAM <= availableRAM && requiredHDD <= availableHDD && requiredCore <= availableCores)
        {
            availableRAM -= requiredRAM;
            availableHDD -= requiredHDD;
            availableCores -= requiredCore;

            const char* message = "Resources available";
            fd_total_to_required = open("total_to_required", O_WRONLY);
            write(fd_total_to_required, message, strlen(message));
            close(fd_total_to_required);

            int fd_required_to_total = open("required_to_total", O_RDONLY);
            char buffer[256];
            while (true)
            {
                ssize_t bytesRead = read(fd_required_to_total, buffer, sizeof(buffer));
                close(fd_required_to_total);
                if (bytesRead > 0)
                {
                    buffer[bytesRead] = '\0';
                    if (strcmp(buffer, "Completed") == 0)
                        break;
                }
            }

            close(fd_required_to_total);

            availableRAM += requiredRAM;
            availableHDD += requiredHDD;
            availableCores += requiredCore;
        }

        else
        {
            const char* message = "Resources not available";
            fd_total_to_required = open("total_to_required", O_WRONLY);
            write(fd_total_to_required, message, strlen(message));
            close(fd_total_to_required);
            cout << "Resources not available" << endl;
            return nullptr;
        }
    }
    else
    {
        cout << "Fork failed" << endl;
    }

    return nullptr;
}

void *allocateToNotepad(void *arg)
{
    pid_t pid = fork();
    mkfifo("total_to_required", 0666);
    mkfifo("required_to_total", 0666);
    int ppid;
    if (pid == 0) 
    { 
        execlp("gnome-terminal", "gnome-terminal", "--", "./notepad.exe", NULL);
    } 

    else if (pid > 0) 
    { 
        sleep(1);
        int fd_total_to_required = open("total_to_required", O_RDONLY);
        int requiredRAM, requiredHDD, requiredCore;
        read(fd_total_to_required, &requiredRAM, sizeof(requiredRAM));
        read(fd_total_to_required, &requiredHDD, sizeof(requiredHDD));
        read(fd_total_to_required, &requiredCore, sizeof(requiredCore));
        close(fd_total_to_required);

        if (requiredRAM <= availableRAM && requiredHDD <= availableHDD && requiredCore <= availableCores)
        {
            availableRAM -= requiredRAM;
            availableHDD -= requiredHDD;
            availableCores -= requiredCore;

            const char* message = "Resources available";
            fd_total_to_required = open("total_to_required", O_WRONLY);
            write(fd_total_to_required, message, strlen(message));
            close(fd_total_to_required);

            int fd_required_to_total = open("required_to_total", O_RDONLY);
            char buffer[256];
            while (true)
            {
                ssize_t bytesRead = read(fd_required_to_total, buffer, sizeof(buffer));
                close(fd_required_to_total);
                if (bytesRead > 0)
                {
                    buffer[bytesRead] = '\0';
                    if (strcmp(buffer, "Completed") == 0)
                        break;
                }
            }

            close(fd_required_to_total);

            availableRAM += requiredRAM;
            availableHDD += requiredHDD;
            availableCores += requiredCore;
        }

        else
        {
            const char* message = "Resources not available";
            fd_total_to_required = open("total_to_required", O_WRONLY);
            write(fd_total_to_required, message, strlen(message));
            close(fd_total_to_required);
            cout << "Resources not available" << endl;
            return nullptr;
        }
    }
    else
    {
        cout << "Fork failed" << endl;
    }

    return nullptr;
}

void *allocateToClock(void *arg)
{
    pid_t pid = fork();
    mkfifo("total_to_required", 0666);
    mkfifo("required_to_total", 0666);
    int ppid;
    if (pid == 0) 
    { 
        execlp("gnome-terminal", "gnome-terminal", "--", "./Clock.exe", NULL);
    } 

    else if (pid > 0) 
    { 
        sleep(1);
        int fd_total_to_required = open("total_to_required", O_RDONLY);
        int requiredRAM, requiredHDD, requiredCore;
        read(fd_total_to_required, &requiredRAM, sizeof(requiredRAM));
        read(fd_total_to_required, &requiredHDD, sizeof(requiredHDD));
        read(fd_total_to_required, &requiredCore, sizeof(requiredCore));
        close(fd_total_to_required);

        if (requiredRAM <= availableRAM && requiredHDD <= availableHDD && requiredCore <= availableCores)
        {
            availableRAM -= requiredRAM;
            availableHDD -= requiredHDD;
            availableCores -= requiredCore;

            const char* message = "Resources available";
            fd_total_to_required = open("total_to_required", O_WRONLY);
            write(fd_total_to_required, message, strlen(message));
            close(fd_total_to_required);

            int fd_required_to_total = open("required_to_total", O_RDONLY);
            char buffer[256];
            while (true)
            {
                ssize_t bytesRead = read(fd_required_to_total, buffer, sizeof(buffer));
                close(fd_required_to_total);
                if (bytesRead > 0)
                {
                    buffer[bytesRead] = '\0';
                    if (strcmp(buffer, "Completed") == 0)
                        break;
                }
            }

            close(fd_required_to_total);

            availableRAM += requiredRAM;
            availableHDD += requiredHDD;
            availableCores += requiredCore;
        }

        else
        {
            const char* message = "Resources not available";
            fd_total_to_required = open("total_to_required", O_WRONLY);
            write(fd_total_to_required, message, strlen(message));
            close(fd_total_to_required);
            cout << "Resources not available" << endl;
            return nullptr;
        }
    }
    else
    {
        cout << "Fork failed" << endl;
    }

    return nullptr;
}


int main()
{
    cout << "Enter RAM, Hard Drive and Processing Cores: ";
    cin >> totalRAM >> totalHDD >> totalCores;
    availableCores = totalCores;
    availableRAM = totalRAM;
    availableHDD = totalHDD;
    boot();
    while (true)
    {
        int choice = showMenu();
        pthread_t thread;
        if (choice == 1)
        {
            pthread_create(&thread, nullptr, allocateToCalculator, nullptr);
            pthread_detach(thread);
            pthread_join(thread, nullptr);
        }

        else if (choice == 2)
        {
            pthread_create(&thread, nullptr, allocateToNotepad, nullptr);
            pthread_detach(thread);
            pthread_join(thread, nullptr);
        }

        else if (choice == 3)
        {
            pthread_create(&thread, nullptr, allocateToClock, nullptr);
            pthread_detach(thread);
            pthread_join(thread, nullptr);
        }

        else
        {
            break;
        }
    }
    goodbye();
}
