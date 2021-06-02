#include <dirent.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <vector>

std::string current_dir = ".";
std::string parent_dir = "..";

#define DIR_SIZE 4096

void find(std::string path, std::string file) {
    DIR* d = opendir(path.c_str());
    if(d) {
        dirent* de = NULL;
        std::vector<std::thread*> tv = {};

        for(de=readdir(d); de!=NULL; de=readdir(d)) {
            std::string new_path;

            if(de->d_type == DT_DIR) {
                if((de->d_name != current_dir) && (de->d_name != parent_dir)){
                    new_path.append(path);
                    if(path[path.length()-1] != '/') {
                        new_path.push_back('/');
                    } 
                    new_path.append(de->d_name);
                    new_path.push_back('/'); 
                    tv.push_back(new std::thread(find, new_path, file));
                }
            }
            else if(de->d_name == file) {
                new_path.append(path);
                if(path[path.length()-1] != '/') {
                    new_path.push_back('/');
                }
                new_path.append(de->d_name);
                std::cout << new_path << std::endl;
            }
        }
        for(std::thread* th : tv) {
            th->join();
            delete th;
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
    find(std::string(argv[1]), std::string(argv[2]));
    auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
    auto dur = end - start;        // 要した時間を計算
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    // 要した時間をミリ秒（1/1000秒）に変換して表示
    std::cout << msec << " milli sec \n";
}