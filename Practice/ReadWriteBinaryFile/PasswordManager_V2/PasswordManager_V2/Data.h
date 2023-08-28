/*****************************************************************//**
 * \file	Data.h
 * \brief	Contain function call that can do various task regarding data management
 *			and modification to a binary file
 *
 * \author	Farhan
 * \date	16-AUG-2023
***********************************************************************/
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class PasswordData
{
public:
	//Constr
	PasswordData() {};
	~PasswordData() {};
	/*!***********************************************************************
	* \brief SetData(std::string website, std::string password)
	* Use to set data of a new/editted password and website
	* \param website
	* Set a website name
	* \param password
	* Set a password name
	* \return
	* None
	*************************************************************************/
	void SetData(std::string website, std::string password);
	/*!***********************************************************************
	* \brief SaveData(std::ofstream& of);
	* Write and save new/editted value into the file
	* \param of
	* File to edit
	* \return
	* None
	**************************************************************************/
	void SaveData(std::ofstream& of);
	/*!***********************************************************************
	* \brief DecipherFile(std::string strFile)
	* Decipher the file so as to access and use the content of the file
	* \param strFile
	* Name of file to edit
	* \return
	* None
	**************************************************************************/
	void DecipherFile(std::string strFile);
	/*!***********************************************************************
	* \brief WriteFile(std::string strFile)
	* To save the content into file
	* \param strFile
	* Name of file to edit
	* \return
	* None
	**************************************************************************/
	void WriteFile(std::string strFile);
	/*!***********************************************************************
	* \brief EditPassword(std::string strFile,int index)
	* To edit an existing password
	* \param strFile
	* Name of file to edit
	* \param index
	* Which website password to modify
	* \return
	* None
	**************************************************************************/
	void EditPassword(std::string strFile,int index);
	/*!***********************************************************************
	* \brief DeletePassword(std::string strFile, int index)
	* To delete an existing password
	* \param strFile
	* Name of file to edit
	* \param index
	* Which website password to delete
	* \return
	* None
	**************************************************************************/
	void DeletePassword(std::string strFile, int index);
	/*!***********************************************************************
	* \brief PrintAllWebsite()
	* Print all existing website in the file
	* \return
	* None
	**************************************************************************/
	void PrintAllWebsite();
	/*!***********************************************************************
	* \brief PrintPassword(int index)
	* Print a selected website's password
	* \param index
	* Which website's password to view
	* \return
	* None
	**************************************************************************/
	void PrintPassword(int index);
	/*!***********************************************************************
	* \brief PrintAllContent()
	* Print all existing website and its password in the file
	* \return
	* None
	**************************************************************************/
	void PrintAllContent();


private:
	std::string Website, Password;

};