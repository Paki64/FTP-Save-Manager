#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

#include "ini.h"

using std::string;


    static inih::INIReader r{"./config.ini"};
    static pid_t res = getpid();


int ftp_3ds(){

    string console = "NINTENDO 3DS";
    bool enable = r.Get<bool>(console, "Enabled_FTP");
    if(enable){
        string remote_root = "ftp://anonymous:@"+r.Get<string>(console, "FTP_address")+":"+r.Get<string>("NINTENDO 3DS", "FTP_port");
        bool dry_run = r.Get<bool>(console, "Dry_run_FTP");
        int ex;
        int ex_val;

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
        wait(&ex);
        ex_val = WEXITSTATUS(ex);

        // NDS
        if(ex_val==0){
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
        }

        // CONSOLE
        if(ex_val==0){
            res = fork();
            if(res == 0 && ex){
                string remote = remote_root + "/" + r.Get<string>(console, "Dump_FTP_location");
                string local = r.Get<string>(console, "Dump_save_location");
                const char *env[] = {"--no-prompt", "--progress", "--no-prompt", "--force", "--resolve=new", "--dry-run", "--create-folder", NULL};
                
                if(dry_run){
                    execlp("pyftpsync", "", "sync", "-n", local.c_str(), remote.c_str(), (char*) NULL, env, NULL);
                    }
                else execlp("pyftpsync", "", "sync", local.c_str(), remote.c_str(), (char*) NULL, env, NULL);
            }
            wait(NULL);
        return ex_val;
        }
    }
    return -1;
}



int main(){

    // SYNC ENABLERS: Syncing folders without FTP could lead to conflicts (thanks 3DS timestamp)
    int ex_3ds = -1;
    int ex;

    // FTP CONNECTIONS
    // 3DS
    res = fork();
    if(res==0){
        ex = ftp_3ds();
        exit(ex);
    }
    else wait(&ex);
    ex_3ds = WEXITSTATUS(ex);


    // INTERNAL SYNCS
    if(ex_3ds==0){
        res = fork();
        if(res==0){
            const char* arg;
            execl("./savesync", arg, (char*) NULL);
        }
        wait(NULL);
    }

    exit(0);
}