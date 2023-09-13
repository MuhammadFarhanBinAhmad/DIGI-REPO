#include "uShell2.h"
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <limits>

void uShell2::exit(TokenList const &tokenList)
{
    if (tokenList.empty())
    {
        return;
    }
    if (tokenList.size() > 1)
    {
        try
        {
            //convert command to int
            m_exitCode = std::stoi(tokenList[1]);
        }
        catch (std::exception const &)
        {
            std::cout << "Error: Invalid exit code format.\n";
        }
    }
    m_exit = true;
}

void uShell2::changePrompt(TokenList const &tokenList)
{
    if (tokenList.empty())
    {
        return;
    }
    if (tokenList.size() >= 1 )
    {
        //change prompt using mergetoken
        m_prompt = mergeTokens(tokenList,1);
    }


}
void uShell2::execute(TokenList const &tokenList, unsigned startParam, unsigned endParam)
{
    if (endParam < startParam)
    {
        return;
    }
    std::string cmd = tokenList[startParam];
    std::vector<const char *> args;
    
    //Extract command and arguments
    for(unsigned i = startParam ; i < endParam ; i++)
    {
        args.push_back(tokenList[i].c_str());
    }
    args.push_back(nullptr);

    //Find executable file
    std::string executable = cmd;

    if (executable[0] != '/' && executable.substr(0,2) != "./")
    {
        //Search for Executable in PATH
        char *pathEnvStr = getenv("PATH");
        if (pathEnvStr != nullptr)
        {
            std::string pathEnvStr(pathEnvStr);
            size_t start = 0;
            size_t end = pathEnvStr.find(':');
            while(end != std::string::npos)
            {
                std::string path = pathEnvStr.substr(start,end - start);
                std::string fullPath = path + "/" + cmd;

                if (access(fullPath.c_str(),X_OK) == 0)
                {
                    executable = fullPath;
                    break;
                }

                start = end - 1;
                end = pathEnvStr.find(':',start);
            }
        }
    }

    //Make child process
    pid_t childpid = fork();
    if (childpid == -1)
    {
        std::cout << "Error: Fail to fork\n";
        return;
    }
    else if (childpid == 0)
    {
        execvp(executable.c_str(), const_cast<char **>(args.data()));
        std::cout << "Error: Forking child process failed.\n";
        exit(tokenList);
    }
    else
    {
        int status = 0;
        waitpid(childpid,&status,0);
        m_exitCode = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }

}
void uShell2::doExternalCmd(TokenList const &tokenList)
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    pid_t childpid = fork();

    if (childpid == -1)
    {
        std::cout << "Error: Fail to fork child\n";
    }
    else if (childpid == 0 )
    {
        execute(tokenList,0,tokenList.size() - 1);
        exit(tokenList);
    }
    else
    {
        int stats =0;
        waitpid(childpid,&stats,0);
        m_exitCode = WIFEXITED(stats) ? WEXITSTATUS(stats) : -1;
    }

}
uShell2::uShell2(bool bFlag) : uShell(bFlag)
{
    m_verbose = bFlag;
    m_internalCmdList2["exit"] = &uShell2::exit;
    m_internalCmdList2["changeprompt"] = &uShell2::changePrompt;

}

int uShell2::run()
{
    while(!m_exit)
    {
        std::cout << m_prompt << "> ";
        std::string user_Input;
        getline(std::cin, user_Input, '\n');

        if (!getInput(user_Input))
        {
            m_exit = true;
            break;
        }

        TokenList tok_List;
        tokenize(user_Input, tok_List);

        if (m_verbose)
        {
            //printVerbose(user_Input);
        }
        if (!replaceVars(tok_List))
        {
            continue;
        }
        if (tok_List.empty())
        {
            continue; // Continue to the next iteration
        }

        if (tok_List[0].find("changeprompt")) 
		{
            changePrompt(tok_List);
        }
        // // Check for internal commands in uShell2
        // if (m_internalCmdList2.find(tok_List[0]) != m_internalCmdList2.end())
        // {
        //     // Call the appropriate internal command
        //     fInternalCmd2 cmdFunc = m_internalCmdList2[tok_List[0]];
        //     (this->*cmdFunc)(tok_List);
        // }
        // else
        // {
        //     // Execute external command
        //     doExternalCmd(tok_List);
        // }
    }
    return m_exitCode;
}
