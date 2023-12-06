#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

#include "ini.h"

using std::string;


    static inih::INIReader r{"./config.ini"};
    static pid_t res = getpid();


void ftp_3ds(){

    string console = "NINTENDO 3DS";
    bool enable = r.Get<bool>(console, "Enabled_FTP");
    if(enable){
        string remote_root = "ftp://anonymous:@"+r.Get<string>(console, "FTP_address")+":"+r.Get<string>("NINTENDO 3DS", "FTP_port");
        bool dry_run = r.Get<bool>(console, "Dry_run_FTP");


        // EMULATION
        res = fork();
        if(res == 0){
            string remote = remote_root + "/" + r.Get<string>(console, "FTP_emu_location");
            string local = r.Get<string>("GENERAL", "Emu_Dump_location");
            const char *env[] = {"--no-prompt", "--progress", "--no-prompt", "--force", "--resolve=new", "--dry-run", "--create-folder", NULL};
            
            if(dry_run){
                execlp("pyftpsync", "", "sync", "-n", local.c_str(), remote.c_str(), (char*) NULL, env, NULL);
                }
            else execlp("pyftpsync", "", "sync", local.c_str(), remote.c_str(), (char*) NULL, env, NULL);
        }
        wait(NULL);

        // NDS
        res = fork();
        if(res == 0){
            string remote = remote_root + "/" + r.Get<string>(console, "FTP_nds_location");
            string local = r.Get<string>("GENERAL", "NDS_Dump_location");
            const char *env[] = {"--no-prompt", "--progress", "--no-prompt", "--force", "--resolve=new", "--dry-run", "--create-folder", NULL};
            
            if(dry_run){
                execlp("pyftpsync", "", "sync", "-n", local.c_str(), remote.c_str(), (char*) NULL, env, NULL);
                }
            else execlp("pyftpsync", "", "sync", local.c_str(), remote.c_str(), (char*) NULL, env, NULL);
        }
        wait(NULL);

        // CONSOLE
        res = fork();
        if(res == 0){
            string remote = remote_root + "/" + r.Get<string>(console, "Dump_FTP_location");
            string local = r.Get<string>(console, "Dump_save_location");
            const char *env[] = {"--no-prompt", "--progress", "--no-prompt", "--force", "--resolve=new", "--dry-run", "--create-folder", NULL};
            
            if(dry_run){
                execlp("pyftpsync", "", "sync", "-n", local.c_str(), remote.c_str(), (char*) NULL, env, NULL);
                }
            else execlp("pyftpsync", "", "sync", local.c_str(), remote.c_str(), (char*) NULL, env, NULL);
        }
        wait(NULL);

    }
}



int main(){



    // FTP CONNECTIONS
    // 3DS
    res = fork();
    if(res==0){
        ftp_3ds();
        exit(0);
    }
    else wait(NULL);


    // INTERNAL SYNCS
    res = fork();
    if(res==0){
        const char* arg;
        execl("./savesync", arg, (char*) NULL);
    }
    wait(NULL);


    exit(0);
}