/*****************************************************************//**
 * \file	FileFunction.h
 * \brief	Call function that user can call to instiate certain action to be done
 *			to the password file
 *
 * \author	Farhan
 * \date	16-AUG-2023
***********************************************************************/
#pragma once
/*!***********************************************************************
	* \brief
	* Add new password to file
	*************************************************************************/
void AddPassword();
/*!***********************************************************************
	* \brief
	* Select an existing password to edit
	**********************************/
void EditPassword();
/*!***********************************************************************
	* \brief
	* Select a password to delete
	*************************************************************************/
void DeletePassword();
/*!***********************************************************************
	* \brief
	* View a password from a selected website
	*************************************************************************/
void ViewPassword();
/*!***********************************************************************
	* \brief
	* View all website and password
	*************************************************************************/
void ViewAllPassword();
/*!***********************************************************************
	* \brief
	* Decipher the content inside the binary file. Is always call at the start
	*************************************************************************/
void DecipherPassword();