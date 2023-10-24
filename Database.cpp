#include<iostream>
#include<fstream>
#include <cstdio>
#include <string>
#include <cstring>

void createCollection(std::string input);
void deleteCollection(std::string input);
void addKeyValue (std::string input);
void renameCollection(std::string input);
void printCollection(std::string input);
void homeMenu();
void optionSelect(std::string func, std::string name);

int main() {
    bool running = true;
    while(running) {
        homeMenu();
    }


    return 0;
}

void createCollection(std::string input) {
    std::string fileName = input + ".txt";
    std::fstream temp;

    temp.open(fileName, std::ios::in);
    if (temp) {
        std::cout << "A collection named " << fileName << " already exists.\n"
                                                          "Pick a different name or edit it with the EditCollection function.\n\n";
        temp.close();
        return;
    }

    temp.open(fileName, std::ios::out);
    if (!temp) {
        std::cout << "Error while creating the file\n\n";
    } else {
        std::cout << "A collection named" << fileName << "was created successfully\n\n";
        temp.close();
    }
}

void deleteCollection(std::string input) {
    std::fstream temp;
    std::string fileName = input + ".txt";

    temp.open(fileName, std::ios::in);
    if (!temp) {
        std::cout << "No collection found with name " << fileName << "\n"
                     "Check your spelling and try again\n\n";
        temp.close();
        return;
    }

    temp.close();

    const char *finalName = fileName.c_str();

    remove(finalName);
    std::cout << "The collection " << finalName <<
              " and all the key:value couples inside it were removed.\n\n";
}

void addKeyValue (std::string input) {
    std::fstream temp;
    std::string fileName = input + ".txt";
    std::string keyValue = ".";

    temp.open(fileName, std::ios::out | std::ios::app);
    if (!temp) {
        std::cout << "No collection found with name " << fileName << "\n"
                     "Check your spelling and try again\n\n";
        temp.close();
        return;
    }

    while (true) {
        keyValue = "";
        std::cout << "insert key:value couple, or press Return to go back: \n\n";
        std::getline(std::cin, keyValue);
        if(keyValue == "") {break;}

        temp << keyValue << '\n';
        std::cout << keyValue << " was added to collection " << input << "\n"
        "Type a new key:value couple to add or hit return to go back";
    }

    temp.close();
}

void renameCollection (std::string input) {
    const char* oldName = (input + ".txt").c_str();
    std::string tempName;
    std::fstream temp;

    temp.open(oldName, std::ios::in);
    if (!temp) {
        std::cout << "No collection found with name " << oldName << "\n"
                    "Check your spelling and try again\n\n";
        temp.close();
        return;
    }
    temp.close();

    std::cout << "input new name for collection " << oldName << "\n";
    std::getline(std::cin, tempName);

    const char* newName = (tempName + ".txt").c_str();

    if (std::rename(oldName, newName) != 0)
        perror("Error renaming collection\n\n");
    else
        std::cout << "Collection " << oldName << " was renamed to " << newName << " successfully.\n\n";
}

void printCollection (std::string input) {
    std::fstream temp;
    std::string collectionName = input + ".txt";
    std::string line;

    temp.open(collectionName, std::ios::in);
        if (!temp) {
            std::cout << "No collection found with name " << collectionName << "\n"
                         "Check your spelling and try again\n\n";
            temp.close();
            return;
    }

    temp.seekg(0, std::ios::beg);
    while (temp) {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        // Read a Line from File
        while (std::getline(temp, line)) {
            std::cout << line << std::endl;
        }
    }
    temp.close();
}

void homeMenu() {
    std::cout << "Welcome to your database app, please choose a command:\n"
                 "create -Name: creates a new collection of name Name\n"
                 "delete -Name: deletes an existing collection of name Name\n"
                 "rename -Name: renames the collection of name Name\n"
                 "add -Name: adds one or more key-value couples to collection of name Name\n"
                 "print -Name: prints all the key-value couples inside collection of name -Name\n";

    std::string userInput;
    std::string funcToCall;
    std::string nameOfFile;
    bool spaceRead = false;

    std::getline(std::cin, userInput);
    int iteration = 0;

    for (char c : userInput) {
        if (c == ' ') {
            spaceRead = true;
            continue;
        }
        if (!spaceRead) {
            funcToCall += c;
        } else {
            nameOfFile += c;
        }
    }
    optionSelect(funcToCall, nameOfFile);
}

void optionSelect(std::string func, std::string name) {
    if (func == "create") {
        createCollection(name);
    } else if (func=="delete") {
        deleteCollection(name);
    } else if (func == "rename") {
        renameCollection(name);
    } else if (func == "add") {
        addKeyValue(name);
    } else if (func == "print") {
        printCollection(name);
    } else {
        std::cout << "Input unclear.\n\n";
    }
}