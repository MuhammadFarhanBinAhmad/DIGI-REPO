

#include <string> 
#include <vector> 
#include <map>
/*! list of strings */
using TokenList = std::vector<std::string>;

/************************************************************************/
/*!
\brief
uShell class. Acts as a command prompt that takes in input and performs 
commands based on the input
*/
/************************************************************************/

class uShell
{

protected:

    /*! shell function pointers */
    typedef void (uShell::* fInternalCmd) (TokenList const &);

    /*! Store the list of strings to function pointers of internal command */ 
    std::map<std::string, fInternalCmd> m_internalCmdList;

    /*! Map of variables to string values */ 
    std::map<std::string, std::string> m_vars;

    /*! String prompt that is displayed at the beginning */ 
    std::string m_prompt;

    /*! decide whether to echo user input */
    bool m_verbose;

    /*! determine whether to exit */
    bool m_exit;

    /*! exit code determined during runtime */ 
    int m_exitCode;

    /************************************************************************/
    /*!
    \brief 
    Get one line of input from std:: cin. Removes the trailing \r if any 
    This function obtains a line from input stream and check whether the last character, is a
    ‘\r’, and remove it. This caters to file formats that has ‘\r’ with ‘\n’.
    \param input
    The input string to take the user input by reference
    \return
    return false if encountering the EOF
    */
    /************************************************************************/
    bool getInput (std::string & input) const;

    /************************************************************************/
    /*!
    \brief
    Print the user input without printing the starting and the trailing spaces.
    It finds the first last non-space positions and prints everything in between. Remember to
    print the line end.
    \param input
    The input string
    */
    /************************************************************************/
    void printVerbose(std::string const & input);

    /************************************************************************/
    /*!
    \brief
    Tokenize the input string into a list of strings which are separated by 
    spaces.
    It gets the string stream from the input and obtains each token item by item by pushing
    the item to token list.
    \param input
    The input string given by the user
    \param tokenList
    Token list to fill up, passed by reference to add strings to it
    */
    /************************************************************************/
    void tokenize(std::string const & input, TokenList & tokenList) const;


    /************************************************************************/
    /*!
    \brief
    Search and replace from the map all variables in the token list with the value 
    In this function it loop through all tokens in the token list. In each iteration, it checks each
    token for comment. If there is comment sign, it removes all the following tokens (including
    7
    this) and terminates the loop. Otherwise, it detects if each token has a variable within.
    Furthermore it checks if this token has ‘{’ following the ‘$’ sign. If not, it tries to find the
    next ‘$’ sign. If there is a ‘{’, it then searches for the first instance of ‘}’ after ‘${’. If there
    is no ‘}’ in the token, it just skips. However, if the ‘}’ is in the token, it continues to do
    changing for the variable in the token string.
    It checks if the variable name is valid by determining whether every character in between
    is a proper character (using function isValidVarname()). If it is invalid, it abort the attempt
    to change. Otherwise, it gets the string between ‘${’ and ‘}’ and check whether the string
    is in the list of the variables. If not, it abort the attempt to change. Otherwise it creates a
    string object with the correct space, which is the variable string size, added to the token size
    without the variable. At the end, it replaces the variable with the correct string and updates
    the original token string. Please note that the assignment requires only one exchange per
    token, it then goes to find the next dollar sign.

    \param tokenList
    Token list to replace the variables with
    \return
    Boolean value to decide whether there is a invalid variable found in the string. 
    Returning true means all valid. Otherwise,
    Returning false means there is a invalid variable (abort the search).
    */
    /************************************************************************/
    bool replaceVars(TokenList & tokenList) const;

    /************************************************************************/
    /*!
    \brief
    Check whether each character is a number or digit from the given start and 
    end of a character array.
    It loops from start to end. In each iteration, it checks each digit if it’s a alphabert or
    number.
    \param start
    Pointer to the start of string to search from
    \param end
    Pointer to the end of string where search stops
    \return
    boolean value to represent if the string is valid
    Returning true means each character in the given string is valid. 
    Otherwise, it returns false.
    */
    /************************************************************************/
    bool isValidVarname(char const* start, char const* end) const;

    /************************************************************************/
    /*!
    \brief
    Merge all the tokens from a given token list, separated by a space, into one 
    single string. We expect return value optimization and move scemantics help.
    It loops from start to end. In each iteration, it checks each digit if it’s a alphabert or
    number.
    \param tokenList
    The token list to take from
    \param startPos
    The starting position/index to start merging from 
    \return
    The merged string
    */
    /************************************************************************/
    std::string mergeTokens(TokenList const & tokenList, unsigned startPos) const;

    /************************************************************************/
    /*!
    \brief
    Echo the user input
    This function prints all the tokens except the first, adding a space in between each pair of
    token.
    \param tokenList
    The list of data to read in
    */
    /************************************************************************/
    void echo (TokenList const & tokenList);
    
    /************************************************************************/
    /*! 
    \brief
    In this function, if there is no input, then setvar command just returns. Otherwise it has
    to check if the variable name is proper by ensuring that the first letter is an alphabet and
    also continue to loop through the rest of the characters of this variable to check whether
    the variable name is valid by using isValidVarname(). If there are more variables at the
    back, it merges them all together (using mergeTokens()) and sets it to the mapped variable.
    Otherwise, it just initializes to an empty string.
    \param tokenList
    The list of tokens to get the data value from
    */
    /************************************************************************/
    void setVar(TokenList const & tokenList);

public:

    /************************************************************************/
    /*!
    \brief
    Creates the class object of uShell
    \param bFlag
    boolean value to decide whether to echo input
    */
    /************************************************************************/
    uShell (bool bFlag);
    /************************************************************************/
    /*!
    \brief
    Public function for external call. Execute in loops and waits for input. 
    It sets function pointers for echo and setvar in m internalCmdList. It sets PATH into the map in m vars.
    \return
    Exit code, of the exit command
    */
    /************************************************************************/
    int run();
};