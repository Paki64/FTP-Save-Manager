#include <fstream>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ini.h"

namespace fs = std::filesystem;
using std::string;

    // NINTENDO 3DS
    static bool enable_saves;
    static bool enable_ext;
    static string save_3ds_root_name;
    static bool dry_run_3ds;
    static string console_3ds_root_sav;
    static string console_3ds_root_ext;
    static string citra_root_sav;
    static string citra_root_ext;


void init(){
    inih::INIReader r{"./config.ini"};

    // NINTENDO 3DS
    string console = "NINTENDO 3DS";
    enable_saves = r.Get<bool>(console, "Enabled_saves");
    enable_ext = r.Get<bool>(console, "Enabled_ext");
    save_3ds_root_name = r.Get<string>(console, "Checkpoint_save_name");
    dry_run_3ds = r.Get<bool>(console, "Dry_run_sync");
    console_3ds_root_sav = r.Get<string>(console, "Dump_save_location");
    console_3ds_root_ext = r.Get<string>(console, "Dump_ext_location");
    citra_root_sav = r.Get<string>(console, "Citra_sync_save_location");
    citra_root_ext = r.Get<string>(console, "Citra_sync_ext_location");
    
}


void sav_3ds(){

    for (const auto & console : fs::directory_iterator(console_3ds_root_sav)){
        if(is_directory(console) && enable_saves){

            string console_id = console.path();
            console_id = console_id.substr(console_3ds_root_sav.size(),8);

            string citra_id = console_id+"00";
            string::size_type i = citra_id.find("x");
            citra_id = citra_id.erase(i,1);
            for (auto & c: citra_id) c = (char)tolower(c);

            string console_path = ((string) console.path() + "/"+save_3ds_root_name);
            string citra_path = citra_root_sav+"/"+citra_id+"/data/00000001";

            //std::cout << console_path << std::endl;
            //std::cout << citra_path << std::endl << std::endl;
            
            fs::path ex_test = citra_path;
            if(!fs::is_directory(ex_test)){
                if(fork()==0){
                    //std::cout << "CREATED DIRECTORY: " + citra_path << std::endl;
                    execlp("mkdir", "", "-p", citra_path.c_str(), (char*) NULL);
                }
            else wait(NULL);
            }

            if(fork()==0){
                const char *env[] = {"--progress", "--no-prompt", "--force", "--resolve new", "--create-folder", NULL};
                if(dry_run_3ds){
                    execlp("pyftpsync", "", "sync", "-n", console_path.c_str(), citra_path.c_str(), (char*) NULL, env, NULL);
                }
                else execlp("pyftpsync", "", "sync", console_path.c_str(), citra_path.c_str(), (char*) NULL, env, NULL);
            }
            else wait(NULL);
        }
    }

}



void ext_3ds(){

    for (const auto & console : fs::directory_iterator(console_3ds_root_ext)){
        if(is_directory(console) && enable_ext){

            string console_id = console.path();
            console_id = console_id.substr(console_3ds_root_ext.size()+1,7);

            string citra_id = "00"+(string)console_id;
            string::size_type i = citra_id.find("x");
            citra_id = citra_id.erase(i,1);
            for (auto & c: citra_id) c = (char)tolower(c);

            string console_path = ((string) console.path() + "/"+save_3ds_root_name);
            string citra_path = citra_root_ext+"/"+citra_id+"/user";

            //std::cout << console_path << std::endl;
            //std::cout << citra_path << std::endl << std::endl;
            
            fs::path ex_test = citra_path;
            if(!fs::is_directory(ex_test)){
                if(fork()==0){
                    std::cout << "CREATED DIRECTORY: " + citra_path << std::endl;
                    execlp("mkdir", "", "-p", citra_path.c_str(), (char*) NULL);
                }
            else wait(NULL);
            }

            if(fork()==0){
                const char *env[] = {"--progress", "--no-prompt", "--force", "--resolve new", "--create-folder", NULL};
                if(dry_run_3ds){
                    execlp("pyftpsync", "", "sync", "-n", console_path.c_str(), citra_path.c_str(), (char*) NULL, env, NULL);
                }
                else execlp("pyftpsync", "", "sync", console_path.c_str(), citra_path.c_str(), (char*) NULL, env, NULL);
            }
            else wait(NULL);
        }
    }

}


int main(int argc, char *argv[]){

    init();
    sav_3ds();
    ext_3ds();

    exit(0);
}