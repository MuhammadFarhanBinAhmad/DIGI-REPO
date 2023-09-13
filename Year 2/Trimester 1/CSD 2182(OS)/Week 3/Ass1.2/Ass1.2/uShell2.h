#pragma once

#include <string>   // std::string
#include <vector>   // std::vector
#include <map>      // std::map
#include "uShell.h" // base

/************************************************************************/
/*!
\brief
uShell2 class. Acts as a command prompt that takes input and performs commands based on the input.
*/
/************************************************************************/
class uShell2 : public uShell
{
protected:
    typedef void (uShell2::*fInternalCmd2)(TokenList const &);

    /*! Store the list of strings to function pointers of internal commands in uShell2, i.e., for changeprompt and exit */
    std::map<std::string, fInternalCmd2> m_internalCmdList2;

    /************************************************************************/
    /*!
    \brief
    Reads the exit code from the token list
    If there is no other argument, it just returns 0. Otherwise, it parses the input into int and
    returns.
    \param tokenList
    Stores the exit code that will be extracted
    */
    /************************************************************************/
    void exit(TokenList const &tokenList);

    /************************************************************************/
    /*!
    \brief
    Changes the prompt that starts at every line
    If changeprompt command is called but there is no input, the function just returns null
    value. Otherwise, update prompt.



    \param tokenList
    The list of tokens where shell can retrieve the string value
    */
    /************************************************************************/
    void changePrompt(TokenList const &tokenList);

    /************************************************************************/
    /*!
    \brief
    Sets up the argument lists required for calling the execvp function, and creates the child process
    This function firstly checks whether the token3
    list is an empty argument list. It simply
    returns if the list is empty. Otherwise it gets the merged command line arguments and
    creates the argument array to put all the command line arguments. It then finds the
    executable file name and checks if this is an absolute path either started with ‘/’ or ‘./’. If
    so, it calls execvp() with the file name and the arguments. Else, it creates the environment
    variables list (e.g. type of std :: vector < std :: string >). Please note that the function can
    not be const because of the operator subscript of the map variable. It then loops through
    the environment variables list, and tries to invoke the input file name if it exists. At the
    end it deletes the created argument array. If no command has been found, it prints the
    error message.
    \param tokenList
    The list of tokens to get the data value from
    \param startParam
    The starting token to parse data from the list
    \param endParam
    Pass the last token to parse data from the list
    */
    /************************************************************************/
    void execute(TokenList const &tokenList, unsigned startParam, unsigned endParam);

    /************************************************************************/
    /*!
    \brief
    Calls an external command using the passed parameters.
    The function flushes the buffer and then uses fork() to spawn child process. Child process
    will set the arguments to the input in the token list given to the process and call execute().
    Then the child exits.The parent process should wait for the child to be done.


    \param tokenList
    The list of tokens to get the data value from
    */
    /************************************************************************/
    void doExternalCmd(TokenList const &tokenList);

public:
    /************************************************************************/
    /*!
    \brief
    Creates the class object of uShell2
    It sets function pointers for changeprompt and exit in m internalCmdList2.

    \param bFlag
    Boolean value to decide whether to echo input
    */
    /************************************************************************/
    uShell2(bool bFlag);

    /************************************************************************/
    /*!
    \brief
    Public function for external call. Execute in loops and waits for input.
    This function is enhanced based on the assignment A1.1. It has a loop and firstly check
    whether exit command is called. If so, it stops. Otherwise it prints out the prompt, with
    the right arrow. Then it gets user input. If there are no more lines from the input, it exits
    from the program (assume it gets re-directed input from the files). Otherwise, it clears the
    input buffer for next input. Obviously, it needs to skip if there is no input (e.g. empty line).
    It starts to tokenize the input otherwise. After this, it prints the input if verbose mode is
    set. It replaces all variables if possible. If the function call for replacement replaceV ars()
    returns false, an error has occurred, it continues to next line of input. Please note that
    replacement also clears comments, so we have to check if the result is empty. Next, it
    3
    finds if it is an internal command in the first list m internalCmdList. If so, it activates
    the internal command. Otherwise, it finds in the second list m internalCmdList2
    and activates the internal command if there is a match. If the search for the
    internal command fails, it regards the command as external command and does
    the external command accordingly.4 Please note that if the next char is EOF, we
    should end the loop to exit. Outside the loop, it returns exit code m exitCode.
    “Tokens” are smaller chunks of the string that are separated by a specified character, called the delimiting
    character.
    
    \return
    Exit code of the exit command
    */
    /************************************************************************/
    int run();
};
