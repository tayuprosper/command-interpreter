#include <iostream>
#include "parser.cpp"
#include <unordered_map>
#include "executecmd.cpp"
#include <string>
using namespace std;

enum class COMMANDS
{
    LS,
    L,
    PWD,
    TOUCH,
    ECHO,
    MKDIR,
    CAT,
    UNKNOWN,
    MAKE,
    CD,
    CODE,
    IFCONFIG,
    SUDO,
    CLEAR,
    NANO,
    GCC,
};

COMMANDS get_commannd(string cmd)
{
    static const unordered_map<string, COMMANDS> command_map{
        {"ls", COMMANDS::LS},
        {"l", COMMANDS::L},
        {"pwd", COMMANDS::PWD},
        {"mkdir", COMMANDS::MKDIR},
        {"touch", COMMANDS::TOUCH},
        {"cat", COMMANDS::CAT},
        {"make", COMMANDS::MAKE},
        {"cd", COMMANDS::CD},
        {"code", COMMANDS::CODE},
        {"ifconfig", COMMANDS::IFCONFIG},
        {"sudo", COMMANDS::SUDO},
        {"clear", COMMANDS::CLEAR},
        {"gcc", COMMANDS::GCC},
        {"nano", COMMANDS::NANO},
        {"echo", COMMANDS::ECHO}};

    auto comd = command_map.find(cmd);
    if (comd != command_map.end())
        return comd->second;
    return COMMANDS::UNKNOWN;
}

int main()
{
    string s;
    string current_dir;
    char buffer[128];
    FILE* pwd = popen("pwd", "r");
    if (!pwd) {current_dir = "Unknown/user";}else{
        while(fgets(buffer, sizeof(buffer),pwd) != nullptr){
            current_dir.append(string(buffer));
        }
        current_dir.pop_back();
    }

    
    while(s != "exit"){
    // cout << current_dir << " > ";
    getline(std::cin, s);
               //get a command
    if (s.size() <= 0)          // if no command entered print error
    {
        cout << "Error: command is empty\n";
        exit(EXIT_FAILURE);
    }


    vector<string> res = get_tokens(s);         //tokenise the command with related arguments

    if ((get_commannd(res.at(0)) == COMMANDS::UNKNOWN))
    {
        cout << "Error: Unknown command, type main --h for valid commands\n\n";
        exit(EXIT_FAILURE);
    }

    // // cout << "command valid\n running command...\n";
    execute(res);
    }
    // }else{
    //     cout << "Error in the command\n";
    // }

    return 0;
}
