#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<unordered_map>

using namespace std;

#define FORMAT "[%s@%s %s]#"
#define COMMAND_SIZE 1024

//1.命令行参数表
#define MAX_ARGC 128
char* g_argv[MAX_ARGC];
int g_argc;

//2.环境变量表
#define MAX_ENVS 100
char* g_env[MAX_ENVS];
int g_envs;

//3. 别名映射表
std::unordered_map<std::string, std::string> alias_list;

//4. 关于重定向
#define NONE_REDIR 0
#define INPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3

int redir = NONE_REDIR;
string filename;

//当前绝对路径
char cwd[1024];
char cwdenv[1024];

//last exit code
int lastcode = 0;

const char* GetUserName()
{
    const char* name = getenv("USER");
    return name == NULL ? "None" : name;
}
const char* GetHostName()
{
    const char* hostname = getenv("HOSTNAME");
    return hostname == NULL ? "None" : hostname;
}
const char* GetPwd()
{
    //const char* pwd = getenv("PWD");
    const char* pwd = getcwd(cwd, sizeof(cwd));
    if(pwd != NULL) 
    {
        snprintf(cwdenv, sizeof(cwdenv), "PWD=%s", cwd);
        putenv(cwdenv);
    }
    return pwd == NULL ? "None" : pwd;
}

const char* GetHome()
{
    const char* home = getenv("HOME");
    return home == NULL ? "" : home;
}

void InitEnv()
{
    extern char **environ;
    memset(g_env, 0, sizeof(g_env));
    g_envs = 0;

    //本来要从配置文件来
    //1. 获取环境变量
    for(int i = 0; environ[i]; ++i)
    {
		// 1.1 申请空间
        g_env[i] = new char[strlen(environ[i]) + 1];
        strcpy(g_env[i], environ[i]);
        g_envs++;
    }
    
    //测试用例
    g_env[g_envs++] = (char*)"test=11111111111";
    g_env[g_envs] = NULL;

	//2. 导成环境变量
    for(int i = 0; g_env[i]; ++i)
    {
        putenv(g_env[i]);
    }
    environ = g_env;
}

string DirName(const char* pwd)
{
#define SLASH "/"
    string dir = pwd;
    if(dir == SLASH) return SLASH;
    auto pos = dir.rfind(SLASH);
    if(pos == string::npos) return "BUG";
    return dir.substr(pos + 1);
}

void MakeCommandLine(char cmd_prompt[], int size)
{
    //snprintf(cmd_prompt, size, FORMAT, GetUserName(), GetHostName(), GetPwd());
    snprintf(cmd_prompt, size, FORMAT, GetUserName(), GetHostName(), DirName(GetPwd()).c_str());
}

void PrintCommandLine()
{
    char prompt[COMMAND_SIZE];
    MakeCommandLine(prompt, sizeof(prompt));
    cout << prompt;
    fflush(stdout);
}

bool GetCommandLine(char* out, int size)
{
    char* c = fgets(out, size, stdin);
    if(c == NULL) return false;
    out[strlen(out) - 1] = 0;
    if(strlen(out) == 0) return false;
    return true;
}
//命令行分析 "ls -a -l" -> "ls" "-a" "-l"
bool CommandParse(char* commandline)
{
#define SEP " "
    g_argc = 0;
    g_argv[g_argc++] = strtok(commandline, SEP);
    while((bool)(g_argv[g_argc++] = strtok(nullptr, SEP)));
    g_argc--;
    return g_argc > 0 ? true : false;
}

void Cd()
{
    if(g_argc == 1)
    {
        string home = GetHome();
        if(home.empty()) return;
        chdir(home.c_str());
    }
    else
    {
        string where = g_argv[1];
        if(where == "-")
        {
            //
        }
        else if(where == "~")
        {
            //
        }
        else
        {
            chdir(where.c_str());
        }
    }
}

void Echo()
{
    if(g_argc == 2)
    {
        string opt = g_argv[1];
        if(opt == "$?")
        {
            cout << lastcode << endl;
            lastcode = 0;
        }
        else if(opt[0] == '$')
        {
            string env_name = opt.substr(1);
            const char* env_value = getenv(env_name.c_str());
            if(env_value)
                cout << env_value << endl;
        }
        else
        {
            cout << opt << endl;
        }
    }
}

bool CheckAndExecBuiltin()
{
    string cmd = g_argv[0];
    if(cmd == "cd")
    {
        Cd();
        return true;
    }
    else if(cmd == "echo")
    {
        Echo();
        return true;
    }
    else if(cmd == "export")
    {
        //
    }
    else if(cmd == "alias")
    {
        // string nickname = g_argv[1];
        // alias_list.insert(k, v);
    }
    return false;
}

void Execute()
{
    pid_t id = fork();
    if(id == 0)
    {
        //child
        //子进程检测重定向情况
        int fp = -1;
        if (redir == INPUT_REDIR)
        {
            fp = open(filename.c_str(), O_RDONLY);
            if (fp < 0) exit(1);
            
            dup2(fp, 0);
            close(fp);
        }
        else if (redir == OUTPUT_REDIR)
        {
            fp = open(filename.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0666);
            if (fp < 0) exit(2);

            dup2(fp, 1);
            close(fp);
        }
        else if (redir == APPEND_REDIR)
        {
            fp = open(filename.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0666);
            if (fp < 0) exit(2);

            dup2(fp, 1);
            close(fp);
        }
        execvp(g_argv[0], g_argv);
        exit(1);
    }
    //father 
    int status = 0;
    pid_t rid = waitpid(id, &status, 0);
    if(rid > 0)
    {
        lastcode = WEXITSTATUS(status);
    }
}

void TrimSpace(char cmd[], int& end)
{
    while (isspace(cmd[end]))
        end++;
}

void RedirCheck(char cmd[])
{
    redir = NONE_REDIR;
    filename.clear();

    int start = 0;
    int end = strlen(cmd) - 1;
    
    //"ls -a -l >> file.txt" > >> <
    while (start < end)
    {
        if (cmd[end] == '<')
        {
            cmd[end++] = '\0';
            TrimSpace(cmd, end);
            redir = INPUT_REDIR;
            filename = cmd + end;
            break;
        }
        else if (cmd[end] == '>')
        {
            if (end > start && cmd[end - 1] == '>')
            {
                // >>
                redir = APPEND_REDIR;
            }
            else
            {
                // >
                redir = OUTPUT_REDIR;
            }
            cmd[end++] = '\0';
            TrimSpace(cmd, end);
            filename = cmd + end;
        }
        else
        {
            end--;
        }
    }
}

int main()
{
	//shell 启动的时候，从系统中获取环境变量
    //现环境变量信息应该从父shell统一来
	InitEnv();

    while(true)
    {
		//1. 输出命令行提示符
        PrintCommandLine();

		//2. 获取用户输入的命令
        char commandline[COMMAND_SIZE];
        if(!GetCommandLine(commandline, sizeof(commandline)))
            continue;

        //3. 重定向分析 "ls -a -l > file.txt" -> "ls -a -l" "file.txt" -> 判定重定向方式
        RedirCheck(commandline);
        

		 //4. 命令行分析 "ls -a -l" -> "ls" "-a" "-l"
        if(!CommandParse(commandline))
            continue;

        //5. 检测并处理内键命令
        if(CheckAndExecBuiltin())
            continue;
		
		//6. 执行命令	
        Execute();
    }
    return 0;
}
