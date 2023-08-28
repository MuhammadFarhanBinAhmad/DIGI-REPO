#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct Person
{
	char age[25];
	char first[25];
	char last[25];
	char phone[25];
};

class BinaryData
{
private:
	char age[25];
	char first[25];
	char last[25];
	char phone[25];

public:
	BinaryData() {}
	~BinaryData() {}


	/*Convert to char and place it into array*/
	void SetData(int age, std::string strFirst, std::string strLast, std::string phone)
	{
		sprintf_s(this->age, "%d", age);
		sprintf_s(this->first, "%s", strFirst.c_str());
		sprintf_s(this->last, "%s", strLast.c_str());
		sprintf_s(this->phone, "%s", phone.c_str());
	}
	/*Write data into stream*/
	void Save(std::ofstream& of)
	{
		of.write((char*)&age, sizeof(age));
		of.write((char*)&first, sizeof(first));
		of.write((char*)&last, sizeof(last));
		of.write((char*)&phone, sizeof(phone));
	}

	void WriteBinaryFile(std::string strFile)
	{
		std::ofstream fs;
		fs.open(strFile, std::ios::out | std::ios::binary | std::ios::app);
		if (!fs.is_open())
		{
			std::cout << "Cannot open file " << strFile << std::endl;
		}
		else
		{
			this->Save(fs);
		}
		fs.close();
	}

	void ReadBinaryFile(std::string strFile)
	{
		Person p;
		std::ifstream binaryFile;
		int size = 0;

		binaryFile.open(strFile, std::ios::in | std::ios::binary);
		binaryFile.seekg(0, std::ios::end);
		size = (int)binaryFile.tellg();
		binaryFile.seekg(0, std::ios::beg);

		while (binaryFile.tellg() < size)
		{
			binaryFile.read((char*)p.age, sizeof(p.age));
			binaryFile.read((char*)p.first, sizeof(p.first));
			binaryFile.read((char*)p.last, sizeof(p.last));
			binaryFile.read((char*)p.phone, sizeof(p.phone));

			std::cout << p.age << '\t' << p.first << '\t' << p.last << '\t' << p.phone << '\n';

		}

		binaryFile.close();
	}
};

int main()
{
	std::string strFirst, strLast, strPhone;
	int age;

	std::unique_ptr<BinaryData> bd(new BinaryData());

	std::cout << "Enter age: ";
	std::cin >> age;
	std::cout << "Enter first name: ";
	std::cin >> strFirst;
	std::cout << "Enter last name: ";
	std::cin >> strLast;
	std::cout << "Enter phone number : ";
	std::cin >> strPhone;

	bd->SetData(age, strFirst, strLast, strPhone);
	bd->WriteBinaryFile("./record.dat");
	bd->ReadBinaryFile("./record.dat");
}
