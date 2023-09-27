/*!************************************************************************
\file   uShell.cpp
\author Muhammad Farhan Bin Ahmad(2200544)
\par    email: b.muhammadfarhan@digipen.edu
\par    Course: CSD 2182
\par    OS Part 1.3
\date   09-15-2023

\brief 	Create a basic shell program called uShell. A shell program behaves typically in a similar fashion to a command prompt.
        This is a continuation from part 1. Now we can changeprompt, exit the program upon command, and search for file
**************************************************************************/

#include "uShell3.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

uShell3::ProcessInfo::ProcessInfo() : PID(0), bActive(false)
{
}
uShell3::ProcessInfo::ProcessInfo(int id, bool state)
{
    PID = id;
    bActive = state;
}
void uShell3::finish(TokenList const & tokenList)
{
    //Standard check
    if (tokenList.empty() || tokenList.size() <= 2)
    {
        std::cerr << "Error: Invalid usage of finish command. Usage: finish <process index>" << std::endl;
        return;
    }

    int process_Index;

    //Process index from token list
    try
    {
        process_Index = std::stoi(tokenList[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: Invalid process index. Usage: finish <process index>" << std::endl;
        return;
    }

    if (process_Index < 0 || process_Index >= static_cast<int>(m_bgProcessList.size()))
    {
        std::cerr << "Error: Invalid process index. Process index out of range." << std::endl;
        return;
    }

    ProcessInfo &process = m_bgProcessList[process_Index];

    if (!process.bActive)
    {
        std::cerr << "Error: Process " << process.PID << " is no longer a child process." << std::endl;
        return;
    }

    int status = 0;
    pid_t result = waitpid(process.PID,&status,0);

    if (result == -1)
    {
        std::cerr << "Error: Waiting for process " << process.PID << " failed." << std::endl;
        return;
    }

    //Print out status of process
    if (WIFEXITED(status))
    {
        int exit_Stat = WEXITSTATUS(status);
        std::cout << "Process " << process.PID << " exited with exit status " << exit_Stat << "." << std::endl;
    }
    else if (WIFSIGNALED(status))
    {
        int signal_Number = WTERMSIG(status);
        std::cout << "Process " << process.PID << " terminated by signal " << signal_Number << "." << std::endl;
    }
    else
    {
        std::cerr << "Error: Unknown exit status for process " << process.PID << "." << std::endl;
    }

    // Set the process as inactive
    process.bActive = false;



}
bool uShell3::exist (TokenList const & tokenList, unsigned startParam, unsigned endParam)
{
    //standard check
    if (tokenList.empty() || startParam > endParam)
    {
        return false;
    }

    std::string cmdName = tokenList[startParam];

    //Check if command carries an absolute path
    if (cmdName.find('/') != std::string::npos)
    {
        //access(const char *path, int mode) - basically check if a paticular file/directory exist
        //F_OK - Check if file exist
        //R_OK - Check if file can be read
        //W_OK - Check if file can be written
        //X_OK - Check of file can be executed x_x

        //Check if file exist at this path
        if (access(cmdName.c_str(),F_OK) == 0)
        {
            return true;
        }

        //File dont exist?Rabs man. Need set up enviroment and loop through to find if file exist
        const char *path_Env = getenv("PATH");

        if (path_Env != nullptr)
        {
            std::string path_EndStr(path_Env);
            size_t startPos = 0;
            size_t endPos = path_EndStr.find(":");

            //Extract directory from PATH
            while (endPos != std::string::npos)
            {
                std::string path_Dir = path_EndStr.substr(startPos,endPos - startPos);
                std::string path_Full = path_Dir + '/' + cmdName;

                //Check if file exist in this path
                if (access(path_Full.c_str(),F_OK) == 0)
                {
                    return true;
                }

                //Move to next directory in PATH
                startPos = endPos+1;
                endPos = path_EndStr.find(':',startPos);
            }
        }
    }

    return false;
}
void uShell3::doExternalCmd(TokenList const & tokenList)
{
    if (tokenList.empty())
    {
        return;
    }

    // Check if the first token is a pipe "|"
    if (tokenList.front() == "|")
    {
        std::cerr << "Error: Invalid use of pipe at the beginning of a command." << std::endl;
        return;
    }

    //Count amount of pipe in tokenlist

    int pipe_Count = 0;
    for (const std::string &token : tokenList)
    {
        if (token == "|")
        {
            pipe_Count++;
        }
    }

    //Create list to store pipe info
    std::vector<PipeInfo> pipeInfo_List(pipe_Count);

    //Track pipe information
    int pipe_Start= -1;
    int pipe_End = -1;

    for (unsigned i =0; i < tokenList.size();i++)
    {
        if (tokenList[i] == "|")
        {
            //Check for of theres an empty string in the between the pipes
            if (pipe_Start == pipe_End +1)
            {
                std::cerr << "Error: Syntax error in pipe command." << std::endl;
                return;
            }

            //Create pipe for this command
            if (pipe(pipeInfo_List[pipe_Start].descriptor) == -1)
            {
                std::cerr << "Error: Pipe creation failed." << std::endl;
                return;
            }

            //Save position of the pipe toke in the token list
            pipeInfo_List[pipe_Start].posInToken = i;

            //Update start and end
            pipe_Start = pipe_End + 1;
            pipe_End = i;
        }

        else if (pipe_Start == -1)
        {
            //update pipe end
            pipe_End = i;
        }
    }

    //Process each command
    int prev_PipeOut = -1;
    int childPid = 0;

    for (unsigned i = 0; i < pipeInfo_List.size();i++)
    {
        childPid = fork();

        if (childPid == -1)
        {
            std::cerr << "Error: Forking failed." << std::endl;
            return;
        }
        else if (childPid == 0)
        {
            TokenList cmdArgs;

            for (int j = pipe_Start;j <= pipe_End;j++)
            {
                cmdArgs.push_back(tokenList[j]);
            }

            //close unnecessary pipe end
            if (i > 0)
            {
                close(pipeInfo_List[i-1].descriptor[PipeInfo::OUT_DESCRIPTOR]);
                //int dup2(int oldfd, int newfd)
                //dup2 is use to duplicate
                //STDIN_FILENO - just a file descriptor(almost certainly 0)
                dup2(prev_PipeOut,STDIN_FILENO);
            }

             if (i < pipeInfo_List.size() - 1)
            {
                close(pipeInfo_List[i].descriptor[PipeInfo::IN_DESCRIPTOR]);
                dup2(pipeInfo_List[i].descriptor[PipeInfo::OUT_DESCRIPTOR], STDOUT_FILENO); // Redirect output to the next pipe
            }

            //Execute command
            execute(cmdArgs);

            //Close pipe
            close(pipeInfo_List[i].descriptor[PipeInfo::IN_DESCRIPTOR]);
            close(pipeInfo_List[i].descriptor[PipeInfo::OUT_DESCRIPTOR]);
            exit(EXIT_FAILURE);
        }
        else // parent
        {
            //close pipe ends in parent
            if (i > 0)
            {
                close(pipeInfo_List[i-1].descriptor[PipeInfo::OUT_DESCRIPTOR]);
            }

            //Add child PID to list
            ProcessInfo pipe_Process(childPid,true);
            m_bgProcessList.push_back(pipe_Process);

            prev_PipeOut = pipeInfo_List[i].descriptor[PipeInfo::OUT_DESCRIPTOR];
        }
    }

    //parent process waits for all child processes to be completed
    for (unsigned i = 0; i < pipeInfo_List.size(); i++)
    {
        int status;
        waitpid(-1, &status, 0);

        // Print the status of the child process
        std::cout << "Process " << m_bgProcessList[i].PID << " exited with exit status " << status << "." << std::endl;

        // Mark the process as inactive
        m_bgProcessList[i].bActive = false;
    }
}
uShell3::uShell3(bool bFlag) : uShell2(bFlag)
{
    internalCmdList3["finish"] = (fInternalCmd3)&uShell3::finish;

    m_exit = false;
    m_verbose = bFlag;
}
int uShell3::run()
{
    while (m_exit == false)
    {

        std::string user_Input;

        std::cout << m_prompt << ">";

        if (!getInput(user_Input))
        {
            m_exit = true;
        }

        if (user_Input.empty())
        {
            continue;
        }

        TokenList buffer;
        tokenize(user_Input, buffer);

        // Same check as before
        if (m_verbose)
        {
            printVerbose(user_Input);
        }

        if (!replaceVars(buffer))
        {
            continue;
        }
        if (buffer.empty())
        {
            continue;
        }

        // Check all the internal command int the 2 list
        if (m_internalCmdList.find(buffer.front()) != m_internalCmdList.end())
        {
            (this->*m_internalCmdList[buffer.front()])(buffer);
        }
        else if (m_internalCmdList2.find(buffer.front()) != m_internalCmdList2.end())
        {
            (this->*m_internalCmdList2[buffer.front()])(buffer);
        }
        else if (m_internalCmdList3.find(buffer.front()) != m_internalCmdList3.end())
        {
            (this->*m_internalCmdList3[buffer.front()])(buffer);
        }
        // if all fail means that trying to get file
        else
        {
            doExternalCmd(buffer);
        }
    }
    return m_exitCode;
}
