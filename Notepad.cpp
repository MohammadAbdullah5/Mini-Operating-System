#include <iostream>
#include <fstream>
#include <string>
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

void displayMenu() {
    cout << "Simple Text Editor - Menu\n";
    cout << "1. Create a new file\n";
    cout << "2. Open an existing file\n";
    cout << "3. Save the current file\n";
    cout << "4. Exit\n";
}

void createNewFile() {
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;

    ofstream file(filename.c_str());
    if (file.is_open()) {
        cout << "File created successfully: " << filename << endl;
        file.close();
    } else {
        cerr << "Error: Unable to create file." << endl;
    }
}

void openFile() {
    
    string filename;
    cout << "Enter the filename to open: ";
    cin >> filename;

    ifstream file(filename.c_str());
    if (file.is_open()) {
        cout << "Contents of " << filename << ":" << endl;
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file." << endl;
    }
    
}

void saveFile() {
    string filename;
    cout << "Enter the filename to save: ";
    cin >> filename;

    ofstream file(filename.c_str());
    if (file.is_open()) {
        cout << "Enter text (type 'exit' to finish):\n";
        string line;
        cin.ignore(); // Clear the input buffer
        while (getline(cin, line) && line != "exit") {
            file << line << endl;
        }
        file.close();
        cout << "File saved successfully: " << filename << endl;
    } else {
        cerr << "Error: Unable to save file." << endl;
    }
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
            int choice;
            string fileContents; // Stores the contents of the file being edited

            do 
            {
                displayMenu();
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) 
                {
                    case 1:
                        createNewFile();
                        break;
                    case 2:
                        openFile();
                        break;
                    case 3:
                        saveFile();
                        break;
                    case 4:
                        cout << "Exiting the program.\n";
                        break;
                    default:
                        cerr << "Invalid choice. Please try again.\n";
                }
            } while (choice != 4);
        }
        mkfifo("required_to_total", 0666);
            
        int fd_required_to_total = open("required_to_total", O_WRONLY);
            
        const char* message = "Completed";
        write(fd_required_to_total, message, strlen(message));
        close(fd_required_to_total);
        
        exit(0);
    }
    return 0;
}
