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
#include <filesystem>

namespace fs = std::filesystem;

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
    // Check if the tokenList contains the required number of arguments
    if (tokenList.size() != 2)
    {
        std::cerr << "Error: Invalid usage of finish. Usage: finish <process index>" << std::endl;
        return;
    }

    // Get the process index from the tokenList
    int processIndex;
    try
    {
        processIndex = std::stoi(tokenList[1]);
    }
    catch (const std::exception &)
    {
        std::cerr << "Error: Invalid process index specified." << std::endl;
        return;
    }

    // Check if the process index is valid
    if (processIndex < 0 || static_cast<size_t>(processIndex) >= m_bgProcessList.size())
    {
        std::cerr << "Error: Invalid process index specified." << std::endl;
        return;
    }

    // Check if the process with the specified index is still active
    if (m_bgProcessList[processIndex].bActive)
    {
        int status;
        pid_t pid = waitpid(m_bgProcessList[processIndex].PID, &status, 0);

        if (pid != -1)
        {
            std::cout << "Process Index " << processIndex << " process " << pid << " exited with exit status " << WEXITSTATUS(status) << "." << std::endl;
            m_bgProcessList[processIndex].bActive = false;
        }
        else
        {
            std::cerr << "Error: Failed to wait for process with index " << processIndex << "." << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Process Index " << processIndex << " process " << m_bgProcessList[processIndex].PID << " is no longer a child process." << std::endl;
    }
}
bool uShell3::exist (TokenList const & tokenList, unsigned startParam, unsigned endParam)
{
    // Ensure that the endParam is within the bounds of the tokenList
    if (endParam >= tokenList.size())
    {
        std::cerr << "Error: Invalid endParam value." << std::endl;
        return false;
    }

    // Get the executable file name
    std::string command = tokenList[startParam];

    // Check if the file carries an absolute path
    fs::path filePath = fs::path(command);
    if (!filePath.is_absolute()) 
    {
        // Search for the command in the PATH environment variable
        char *pathEnv = std::getenv("PATH");
        if (pathEnv == nullptr) 
        {
            std::cerr << "Error: PATH environment variable not set." << std::endl;
            return false;
        }

        // Split the PATH variable into directories
        std::vector<std::string> pathDirs;
        std::string pathEnvStr(pathEnv);
        size_t start = 0, end;

        while ((end = pathEnvStr.find(':', start)) != std::string::npos) 
        {
            pathDirs.push_back(pathEnvStr.substr(start, end - start));
            start = end + 1;
        }
        pathDirs.push_back(pathEnvStr.substr(start));

        // Check if the command exists in any of the directories
        bool found = false;
        for (const std::string &pathDir : pathDirs) 
        {
            fs::path fullPath = fs::path(pathDir) / command;
            if (fs::exists(fullPath)) 
            {
                found = true;
                break;
            }
        }

        if (!found) 
        {
            std::cerr << "Error: Command '" << command << "' not found." << std::endl;
            return false;
        }
    } 
    else 
    {
        // Check if the file with absolute path exists
        if (!fs::exists(filePath)) 
        {
            std::cerr << "Error: Command '" << command << "' not found." << std::endl;
            return false;
        }
    }

    return true;
}
void uShell3::doExternalCmd(TokenList const & tokenList)
{
    // Check if tokenList is empty
    if (tokenList.empty()) 
    {
        return;
    }

    fs::path currentPath = fs::current_path();

    // Check if the first token is a pipe
    if (tokenList[0] == "|") 
    {
        std::cerr << "Syntax error: Missing command before the pipe." << std::endl;
        return;
    }

    // Count how many pipes are in the token list
    int total_Pipe = 0;
    bool hasPipe = false;
    for (size_t i = 0; i < tokenList.size(); i++) 
    {
        if (tokenList[i] == "|") 
        {
            total_Pipe++;
            hasPipe = true;
        }
    }

    if (!hasPipe)
    {
        // Execute the single command directly
        if (!exist(tokenList, 0, tokenList.size() - 1))
        {
            std::cerr << "Error: Command not found." << std::endl;
            return;
        }
        std::cout << "ls\n";
        execute(tokenList, 0, tokenList.size());
    }

    std::vector<PipeInfo> pipes(total_Pipe);
    int pipe_Index = 0;
    unsigned paramStart = 0;

    // Set up positions of pipes
    for (size_t i = 0; i < tokenList.size(); i++) 
    {
        if (tokenList[i] == "|") 
        {
            if (pipe_Index >= total_Pipe) 
            {
                std::cerr << "Syntax error: Too many pipes." << std::endl;
                return;
            }

            pipes[pipe_Index].posInToken = i;
            
            pipe_Index++;

            // Identify the command boundaries
            unsigned paramEnd = i - 1;

            // Check for empty string between pipes
            if (paramStart > paramEnd) 
            {
                std::cerr << "Syntax error: Missing command between pipes." << std::endl;
                return;
            }

            // Check if the command exists
            if (!exist(tokenList, paramStart, paramEnd)) 
            {
                std::cerr << "Error: Command not found." << std::endl;
                return;
            }

            paramStart = i + 1;
        }
    }

    // Check if there's a command after the last pipe
    if (paramStart < tokenList.size()) 
    {
        unsigned paramEnd = tokenList.size() - 1;

        // Check if the command exists
        if (!exist(tokenList, paramStart, paramEnd)) 
        {
            std::cerr << "Error: Command not found." << std::endl;
            return;
        }
    }
    //single command
    {

        int numPipes = pipes.size();
        int pipefds[2];

        pid_t child_pid;

        // Initialize pipes
        for (int i = 0; i < numPipes; i++) 
        {
            if (pipe(pipefds) == -1) 
            {
                perror("pipe");
                _exit(EXIT_FAILURE);
            }
            pipes[i].descriptor[PipeInfo::IN_DESCRIPTOR] = pipefds[PipeInfo::IN_DESCRIPTOR];
            pipes[i].descriptor[PipeInfo::OUT_DESCRIPTOR] = pipefds[PipeInfo::OUT_DESCRIPTOR];
        }

        // Iterate through each command and execute it in a child process
        int start = 0;
        for (int i = 0; i <= numPipes; i++) 
        {
            bool isLastCommand = (i == numPipes);

            int end = isLastCommand ? tokenList.size() - 1 : pipes[i].posInToken - 1;

            // Create a child process
            if ((child_pid = fork()) == -1) 
            {
                perror("fork");
                _exit(EXIT_FAILURE);
            }

            if (child_pid == 0) // This is the child process
            {
                if (!isLastCommand) 
                {
                    // Redirect stdout to the write end of the pipe
                    if (dup2(pipes[i].descriptor[PipeInfo::OUT_DESCRIPTOR], STDOUT_FILENO) == -1) 
                    {
                        perror("dup2");
                        _exit(EXIT_FAILURE);
                    }
                }

                if (i > 0) 
                {
                    // Redirect stdin to the read end of the previous pipe
                    if (dup2(pipes[i - 1].descriptor[PipeInfo::IN_DESCRIPTOR], STDIN_FILENO) == -1) 
                    {
                        perror("dup2");
                        _exit(EXIT_FAILURE);
                    }
                }

                // Close pipe descriptors in child
                for (int j = 0; j < numPipes; j++) 
                {
                    close(pipes[j].descriptor[PipeInfo::IN_DESCRIPTOR]);
                    close(pipes[j].descriptor[PipeInfo::OUT_DESCRIPTOR]);
                }

                // Build the argument list for execvp
                char **args = new char *[end - start + 2];
                for (int j = start; j <= end; j++) 
                {
                    args[j - start] = const_cast<char *>(tokenList[j].c_str());
                }
                args[end - start + 1] = nullptr;

                // Execute the command
                execvp(args[0], args);

                // If execvp fails, print an error and exit
                perror("execvp");
                _exit(EXIT_FAILURE);
            } 
            else // This is the parent process
            {
                if (!isLastCommand) 
                {
                    // Close the write end of the pipe in the parent process
                    close(pipes[i].descriptor[PipeInfo::OUT_DESCRIPTOR]);
                }

                if (i > 0) 
                {
                    // Close the read end of the previous pipe in the parent process
                    close(pipes[i - 1].descriptor[PipeInfo::IN_DESCRIPTOR]);
                }

                // Wait for the child process to complete
                int status;
                if (waitpid(child_pid, &status, 0) == -1) 
                {
                    perror("waitpid");
                    _exit(EXIT_FAILURE);
                }

                // Handle the exit status of the child process
                if (WIFEXITED(status)) 
                {
                    int exit_status = WEXITSTATUS(status);
                    std::cout << "Child process exited with status " << exit_status << std::endl;
                } 
                else 
                {
                    std::cerr << "Child process did not exit normally" << std::endl;
                }
            }

            start = pipes[i].posInToken + 1;
        }

        // Close any remaining open pipe descriptors
        for (int i = 0; i < numPipes; i++) 
        {
            close(pipes[i].descriptor[PipeInfo::IN_DESCRIPTOR]);
            close(pipes[i].descriptor[PipeInfo::OUT_DESCRIPTOR]);
        }
        
        // Print the result of the last command to the console
        if (numPipes == 0) 
        {
            // If there are no pipes, print the result directly to the console
            execute(tokenList,paramStart,tokenList.size()-1);
        }
    }
    std::cout << "End function\n";
}
uShell3::uShell3(bool bFlag) : uShell2(bFlag)
{
    m_internalCmdList3["finish"] = (fInternalCmd3)&uShell3::finish;

    // m_exit = false;
    // m_verbose = bFlag;
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
