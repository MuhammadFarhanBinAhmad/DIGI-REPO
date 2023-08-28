#include "Data.h"

std::string DecipheredFile;
std::vector<std::string> strWebsite;
std::vector<std::string> strPassword;


void PasswordData::SetData(std::string website, std::string password)
{
	//Set password and website
	Website = website;
	Password = password;
}
void PasswordData::WriteFile(std::string strFile)
{
	std::ofstream fs;
	fs.open(strFile, std::ios::out | std::ios::binary | std::ios::app);

	//File check
	if (!fs.is_open())
	{
		std::cout << "Fail to open " << strFile << '\n';
	}
	//Save data
	else
	{
		this->SaveData(fs);
	}

	fs.close();

}
//Writing binary data to file
void PasswordData::SaveData(std::ofstream& of)
{

	int webLen = Website.size();
	//Use reinterpret_cast to convert pointer of a data type to another data type
	//ofstream.write just copies a a block of data

	//convert content into a binary data
	of.write(reinterpret_cast<char*>(&webLen), sizeof(webLen));//write the binary representation of content to the file
	of.write(Website.c_str(), webLen);//store content as binary data

	int passwordLen = Password.size();
	of.write(reinterpret_cast<char*>(&passwordLen), sizeof(passwordLen));
	of.write(Password.c_str(), passwordLen);

}
void PasswordData::EditPassword(std::string strFile, int index)
{
	//Check if valid index
	if (index < 0 || index >= strWebsite.size()) 
	{
		std::cout << "Invalid index." << std::endl;
		return;
	}

	// Input new password
	std::string newPassword;
	std::cout << "Enter new password: ";
	std::cin >> newPassword;

	// Update vectors
	strPassword[index] = newPassword + '\n';
	std::cout << strWebsite.size();

	// Open and clear file content
	std::ofstream fs(strFile, std::ios::out | std::ios::binary | std::ofstream::trunc);
	
	//File check
	if (!fs.is_open())
	{
		std::cout << "Failed to open " << strFile << '\n';
		return;
	}

	//Write data into binary file
	for (int i = 0; i < strWebsite.size(); ++i)
	{
		//remove '\n' at end of string
		strWebsite[i].erase(remove(strWebsite[i].begin(), strWebsite[i].end(), '\n'), strWebsite[i].end());
		strPassword[i].erase(remove(strPassword[i].begin(), strPassword[i].end(), '\n'), strPassword[i].end());
		//Save data into binary file
		SetData(strWebsite[i], strPassword[i]);
		SaveData(fs);
	}

	fs.close();

	std::cout << "Password has been updated." << std::endl;
}
void PasswordData::DecipherFile(std::string strFile)
{

	std::ifstream binaryfile;
	int size = 0;

	//Open and set pointer to the start of the file. Also grab the total byte size of the file
	binaryfile.open(strFile, std::ios::in | std::ios::binary);
	binaryfile.seekg(0, std::ios::end);
	size = (int)binaryfile.tellg();
	binaryfile.seekg(0, std::ios::beg);

	//DECIPHER FILE
	while (binaryfile.tellg() < size)
	{
		//Decipher binary text to string
		int webLen = 0;
		binaryfile.read(reinterpret_cast<char*>(&webLen), sizeof(webLen));
		std::string web;
		web.resize(webLen);
		binaryfile.read(&web[0], webLen);

		int passwordLen = 0;
		binaryfile.read(reinterpret_cast<char*>(&passwordLen), sizeof(passwordLen));
		std::string pw;
		pw.resize(passwordLen);
		binaryfile.read(&pw[0], passwordLen);

		DecipheredFile += web;
		DecipheredFile += '\n';
		DecipheredFile += pw;
		DecipheredFile += '\n';
	}

	//Place decipher value into vector for ease of access and use in the future
	std::istringstream iss{ DecipheredFile };
	std::string line;
	short counter = 0;

	//NOTE: Due to wanting to split the content into 2 vector, need remember to remove the '\n' when rewriting into binary file
	//using the 2 vectors as failure to do so will result in 2 '\n' character present
	while (std::getline(iss, line))
	{
		line += '\n';
		if (counter % 2)
		{
			strPassword.push_back(line);
		}
		else
		{
			strWebsite.push_back(line);
		}
		counter++;
	}

	binaryfile.close();
}
void PasswordData::DeletePassword(std::string strFile,int index)
{
	if (index < 0 || index >= strWebsite.size()) {
		std::cout << "Invalid index." << std::endl;
		return;
	}

	//remove desired password from vector
	strWebsite.erase(strWebsite.begin() + index);
	strPassword.erase(strPassword.begin() + index);

	// Write modified data back to the file
	std::ofstream fs(strFile, std::ios::out | std::ios::binary | std::ofstream::trunc);
	if (!fs.is_open())
	{
		std::cout << "Failed to open " << strFile << '\n';
		return;
	}

	//Rewrite all modify content into binary file
	for (int i = 0; i < strWebsite.size(); ++i)
	{
		strWebsite[i].erase(remove(strWebsite[i].begin(), strWebsite[i].end(), '\n'), strWebsite[i].end());
		strPassword[i].erase(remove(strPassword[i].begin(), strPassword[i].end(), '\n'), strPassword[i].end());
		SetData(strWebsite[i], strPassword[i]);
		SaveData(fs);
	}

	fs.close();

	std::cout << "Password has deleted." << std::endl;
}
void PasswordData::PrintAllWebsite()
{
	//Print all website
	for (short i = 0; i < strWebsite.size();i++)
	{
		std::cout << i << ": " << strWebsite[i];
	}
}
void PasswordData::PrintPassword(int index)
{
	//Print selected website and password
	std::cout << "Website: " << strWebsite[index];
	std::cout << "Password: " << strPassword[index];
}
void PasswordData::PrintAllContent()
{
	//Print all website and password
	for (short i = 0; i < strPassword.size();i++)
	{
		std::cout << i << ":\n";
		std::cout << "Website: " << strWebsite[i];
		std::cout << "Password: " << strPassword[i];
	}
}

