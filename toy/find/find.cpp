#include <dirent.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <chrono>

const char* current_dir = ".";
const char* parent_dir = "..";

#define DIR_SIZE 4096

void find(char* path, char* file) {
    DIR* d = opendir(path);
    if(d) {
        dirent* de = NULL;

        for(de=readdir(d); de!=NULL; de=readdir(d)) {
            char new_path[DIR_SIZE];

            if(de->d_type == DT_DIR) {
                if(strcmp(de->d_name,current_dir) && strcmp(de->d_name,parent_dir)){
                    strcpy(new_path, path);
                    if(path[strlen(path)-1] != '/') {
                        new_path[strlen(path)] = '/';
                        strcpy(new_path+strlen(path)+1, de->d_name);
                        new_path[strlen(path)+de->d_namlen + 1] = '/';
                        new_path[strlen(path)+de->d_namlen + 2] = '\0';  
                    } else {
                        strcpy(new_path+strlen(path), de->d_name);
                        new_path[strlen(path)+de->d_namlen] = '/';  
                        new_path[strlen(path)+de->d_namlen + 1] = '\0';
                    }
                    find(new_path, file);
                }
            }
            else if(!strcmp(de->d_name, file)) {
                strcpy(new_path, path);
                if(path[strlen(path)-1] != '/') {
                    new_path[strlen(path)] = '/';
                    strcpy(new_path+strlen(path)+1, de->d_name);
                    new_path[strlen(path)+de->d_namlen + 1] = '\0'; 
                } else {
                    strcpy(new_path+strlen(path), de->d_name);
                    new_path[strlen(path)+de->d_namlen] = '\0';
                }
                std::cout << new_path << std::endl;
            }
        }
        close(d->__dd_fd);
    } else {
        std::cout << "Cannot open directory from the path of " << path << std::endl;
        perror(0);
    }
}

int main(int args, char** argv) {
    if(args != 3) {
        std::cout << "3 arguments are needed..." << std::endl;
        exit(1);
    } 

    auto start = std::chrono::system_clock::now();      // 計測スタート時刻を保存
    find(argv[1], argv[2]);
    auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
    auto dur = end - start;        // 要した時間を計算
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    // 要した時間をミリ秒（1/1000秒）に変換して表示
    std::cout << msec << " milli sec \n";

}