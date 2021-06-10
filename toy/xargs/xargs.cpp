#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <stdlib.h>
#include <sys/stat.h>

#define SIZE 2048

inline bool exists_path (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0); 
}

std::string get_file_path (const std::string& name) {
    std::string path = std::string(getenv("PATH"));
    std::stringstream ss(path);
    std::string buf;
    while (std::getline(ss, buf, ':')) {
        if(exists_path(buf + "/" + name)) {
            return buf + "/" + name;
        }
    }
    return name;
}

int main(int args, char** argv) {
    char rbuf[SIZE];

    std::string line = "";

    while(read(0, rbuf, SIZE)) {
        line.append(std::string(rbuf));
    }

    std::vector<std::string> v;

    std::stringstream ss(line);
    std::string buf;
    while (std::getline(ss, buf, '\n')) {
        v.push_back(buf);
    }

    for(const auto strs: v) {
        std::vector<std::string> it_v;
        std::stringstream it_ss(strs);
        std::string it_buf;
        while (std::getline(it_ss, it_buf, '\n')) {
            it_v.push_back(it_buf);
        }
        pid_t pid = fork();
        if(pid < 0) {
            exit(2);
        }

        // child
        if(pid == 0) {
            // char* param[args];
            // for(int i = 1; i < args; ++i) {
            //     param[i-1] = argv[i];
            // }
            // param[args-1] = NULL;
            char* param[args + int(it_v.size())];
            for(int i = 0; i < args-1; ++i) {
                param[i] = argv[i+1];
            }
            for(int i = args-1; i < args+it_v.size()-1; ++i) {
                param[i] = (char*)(it_v[i-args+1].c_str());
            }
            param[args + it_v.size()-1] = (char*)0;
            execv(get_file_path(param[0]).c_str(), param);
        } else {
            wait(0); 
        }
    }

    return 0;
}