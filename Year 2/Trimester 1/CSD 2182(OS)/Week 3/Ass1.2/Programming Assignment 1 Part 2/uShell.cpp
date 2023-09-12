#include "uShell2.h"

void uShell2::exit(TokenList const &tokenList)
{
    if (tokenList.empty())
    {
        return;
    }
    
    int argu=0;

    for (size_t i = 0 ;i < tokenList.size();i++)
    {
        argu++;
    }
}

void uShell2::changePrompt(TokenList const &tokenList)
{
    if (tokenList.empty())
    {
        return;
    }


}
void uShell2::execute(TokenList const &tokenList, unsigned startParam, unsigned endParam)
{

}
void uShell2::doExternalCmd(TokenList const &tokenList)
{

}
uShell2::uShell2(bool bFlag)
{

}

int uShell2::run()
{

}
