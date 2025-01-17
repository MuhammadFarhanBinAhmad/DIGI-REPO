/*!************************************************************************
\file   uShell.cpp
\author Muhammad Farhan Bin Ahmad(2200544)
\par    email: b.muhammadfarhan@digipen.edu
\par    Course: CSD 2182
\par    OS Part 1.3
\date   06-10-2023

\brief 	Create a basic shell program called uShell. A shell program behaves typically in a similar fashion to a command prompt.
        This is a continuation from part 2. Now we continue on finish, exist and externalcmd(Explanation down in comment cause i lazy summarise here)
**************************************************************************/

#include "uShell3.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
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
/*!
    * \brief
    *  This function does finish command. It checks for finish command without parameters
    and indicates the error. If the finish command is with the correct parameters, it convert
    the argument to process id to wait for that process. It checks if the waited process ID is valid
    in the m bgProcessList and also checks if the process to be waited for has already done
    by checking bActive for the process. If everything is OK, it waits and gets the returned
    status (using waitpid()). At the end it prints the status for the process and then set the
    process active flag to false.
*/
void uShell3::finish(TokenList const & tokenList)
{
    //No process index present
    if (tokenList.size() < 2)
    {
        std::cout << "Error: no such process index." << std::endl;
        return;
    }

    //Process index
    size_t index = static_cast<size_t>(std::stoi(tokenList[1]));

    // Check if index larger than the list size
    if (index >= m_bgProcessList.size())
    {
        std::cout << "Error: no such process index." << std::endl;
        return;
    }

    // Get process
    ProcessInfo& process = m_bgProcessList[index];

    if (process.bActive)
    {
        int stat = 0;
        // Wait for active process to exit.
        waitpid(process.PID, &stat, WUNTRACED);        
        process.bActive = false;

        std::cout << "process " << process.PID << " exited with exit status " << WEXITSTATUS(stat) << std::endl;
    } 
    else 
    {
        // Process had already exited.
        std::cout << "Process Index " << index << " process " << process.PID << " is no longer a child process." << std::endl;
    }
}
 /*!
     * \brief
     * This function determines whether the command exists or not. It gets the executable file
        name. If the file carries an absolute path, it checks whether the file exists. Otherwise, it sets
        up the environment variables list and loop through the list to find whether the file exists.
     */
bool uShell3::exist (TokenList const & tokenList, unsigned startParam, unsigned endParam)
{
    //Standard check
    if (tokenList.empty()) 
    {
        return false;
    }
    
    //Find if '/' can be found
    if (tokenList[startParam].find('/') != std::string::npos)
    {
        return access(tokenList[startParam].c_str(), F_OK) != -1;
    }
    

    // Get path.
    const char* path = std::getenv("PATH");

    if (path == nullptr) 
    {
        // The PATH enviroment is not set up
        return false;
    }
    
    // Create path copy
    char* path_Copy = strdup(path);
    // Separate path by :
    char* path_Token = strtok(path_Copy, ":");
    
    //Use to check if path exist
    bool exists = false;

    while (path_Token != nullptr) 
    {
        std::string path_Entry = path_Token;
        std::string full_Path = path_Entry + "/" + tokenList[startParam];

        // Check if path exist not
        if (access(full_Path.c_str(), X_OK) != -1) 
        {
             // Found command. No need continue searching
            exists = true;
            break;
        }

        path_Token = strtok(nullptr, ":");
    }

    free(path_Copy);
    
    // Not even using end param.Bruv
    endParam = endParam;
    
    return exists;
}

/*!
    * \brief
    *  Calls an external command using the passed parameters.
    *  The function checks for rare case where first token is a pipe, where nothing will be done.
    It flushes the buffer and then count the number of pipes in the token list. It adds pipe
    information to a list typed of std :: vector < P ipeInfo > and creates the pipe (using
    pipe(). You may save the position of the pipe in the token list so that it can be used to
    separate the arguments. Once it has obtained the number of processes required, it loops
    over for further checking. It identifies where the beginning and ending position of the
    parameters in the token list. Otherwise if there is only a single process, it checks whether
    there is a background process token. It reports the syntax error if there is an empty string
    between the pipes. The function checks whether the command in the given token list with
    the specified starting and ending position of the parameters exists by calling exist() and
    reports the error accordingly. It returns if there is an error.
    Otherwise, it starts to create the child processes using fork(). For each fork(), if
    background process is specified, the parent does not wait and adds the child to the list by
    pushing into m bgProcessList. Please note you need to print out the status for the child
    process. Otherwise if no background process is required, the parent just adds the child
    PID to the list of the processes with piping. For the child process, it sets the arguments
    to the input in the token list given to the process and call execute(). If the process is
    not the first one to be created, it closes stdin and replaces with pipe in. If the process is
    not the last one, it closes stdout and replaces with pipe out. It closes all pipes that are
    not needed anymore when calling execute() given in uShell2.h. Then the child exits by
    calling exit(EXIT FAILURE). The parent process should close all pipes before waiting for
    all the child processes to be done.

    * \param tokenList
    * The list of tokens to get the data value from
    */
//This function was fun to make *sarcasm included
//COMMAND TO CHECK
//& - Informs the shell to put the command in the background
//EDIT - UNIX have that set for you
//ls - List out all file
//ls | grep ... - List out all file with same string in it
//ls | wc - Check amount of word in the text(do we need this???)
void uShell3::doExternalCmd(TokenList const & tokenList)
{
    if(tokenList[0] == "|" || tokenList.empty())
    {
        return;
    }

    unsigned start = 0;
    std::vector<PipeInfo> pipeList;
    std::cout.flush();//flush the buffer

    for(size_t i = 0; i < tokenList.size();i++)
    {
        if(tokenList[i] == "|")
        {
            PipeInfo pipe_Found;

            pipe_Found.posInToken = i;
            pipe(pipe_Found.descriptor);
            pipeList.push_back(pipe_Found);

            //Check for error
            if((i+1) == tokenList.size() || tokenList[i+1] == "|")
            {
                std::cout << "Error: syntax error\n";
                return;
            }

            if(!exist(tokenList,i+1,i+1))
            {
                std::cout << "Error: " << tokenList[i+1] << " cannot be found\n";
                return;
            }

        }
    }
    //Check if exist
    if(!exist(tokenList,0,0))
    {
        std::cout << "Error: " << tokenList[0] << " cannot be found\n";
        return;
    }
    //check if empty
    if(pipeList.empty())
    {
        pid_t status = fork();//fork the child

        if(status == 0)
        {
            if(tokenList[tokenList.size()-1] == "&")
            {
                execute(tokenList,0,tokenList.size()-1);
            }
            else
            {
                execute(tokenList,0,tokenList.size());
                _exit(EXIT_FAILURE);
            }
        }
        else
        {
            if(tokenList[tokenList.size()-1] == "&")
            {
                ProcessInfo process;
                process.PID = status;
                process.bActive = true;

                m_bgProcessList.push_back(process);
                std::cout << "[" << m_bgProcessList.size()-1 << "] process " << process.PID << '\n';
            }
            else
            {
                wait(NULL);//wait for child
            }
        }
    }
    else
    //NEED CHECK FOR STATUS. ALL OF THEM
    {
        //STATS 1
        pid_t status_1 = fork();

        if(status_1== 0)
        {
            close(1);
            close(pipeList[0].descriptor[PipeInfo::IN_DESCRIPTOR]);

            dup(pipeList[0].descriptor[PipeInfo::OUT_DESCRIPTOR]);
            
            for(int i = getdtablesize(); i > 3;) 
            {
                close(--i);
            }

            execute(tokenList,start,pipeList[0].posInToken);//execute order 66
            
            _exit(EXIT_FAILURE);
        }
        else
        {

            start = pipeList[0].posInToken + 1;

            //Check for &
            if(tokenList[tokenList.size()-1] == "&")
            {
                ProcessInfo process;
                process.PID = status_1;
                process.bActive = true;

                m_bgProcessList.push_back(process);
                std::cout << "[" << m_bgProcessList.size()-1 << "] process " << process.PID << '\n';
            }
            for(size_t i = 1; i < pipeList.size(); i++)
            {
                //STATS 2
                pid_t status_2 = fork();

                if(status_2== 0)
                {
                    close(0);
                    dup(pipeList[i-1].descriptor[PipeInfo::IN_DESCRIPTOR]);
                    close(1);
                    dup(pipeList[i].descriptor[PipeInfo::OUT_DESCRIPTOR]);
                    for(int j = getdtablesize(); j > 3;) close(--j);

                    execute(tokenList,start,pipeList[i].posInToken);
                    _exit(EXIT_FAILURE);
                }
                else
                {
                    if(tokenList[tokenList.size()-1] == "&")
                    {
                        ProcessInfo process;
                        process.PID = status_2;
                        process.bActive = true;

                        m_bgProcessList.push_back(process);
                        std::cout << "[" << m_bgProcessList.size()-1 << "] process " << process.PID << '\n';
                    }

                    start = pipeList[i].posInToken + 1;
                }
            }
            //STATS 3
            pid_t status_3 = fork();

            if(status_3 == 0)
            {
                close(0);
                close(pipeList[pipeList.size()-1].descriptor[PipeInfo::OUT_DESCRIPTOR]);
                dup(pipeList[pipeList.size()-1].descriptor[PipeInfo::IN_DESCRIPTOR]);
                
                for(int i = getdtablesize(); i > 3;)
                {
                    close(--i);
                } 
                if(tokenList[tokenList.size()-1] == "&")
                {
                    execute(tokenList,pipeList[pipeList.size()-1].posInToken + 1,tokenList.size() - 1);
                }
                else
                {
                    execute(tokenList,pipeList[pipeList.size()-1].posInToken + 1,tokenList.size());
                }

                _exit(EXIT_FAILURE);
            }
            else
            {
                if(tokenList[tokenList.size()-1] == "&")
                {
                    ProcessInfo process;
                    process.PID = status_3;
                    process.bActive = true;

                    m_bgProcessList.push_back(process);
                    std::cout << "[" << m_bgProcessList.size()-1 << "] process " << process.PID << '\n';
                }
            }
        }

        for(int i = getdtablesize(); i > 3;)
        {
            close(--i);
        }

        if(tokenList[tokenList.size()-1] != "&")
        {
            wait(NULL);

            for(unsigned i = 0; i < pipeList.size(); ++i)
            {
                wait(NULL);
            }

        }
    }
}
uShell3::uShell3(bool bFlag) : uShell2(bFlag)
{
    m_exit = false;
    m_verbose = bFlag;

    m_vars["PATH"] = getenv("PATH");
    m_internalCmdList3["finish"] = (fInternalCmd3)&uShell3::finish;
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

        // Check all the internal command int the 3 list
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
