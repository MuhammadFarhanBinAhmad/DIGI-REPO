#include "SmartPointer.h"
#include <vector>
#include <iostream>
#include <memory>

int main()
{
	std::cout << "/////////////////////////////////\n";
	std::cout << "int move\n";
	std::cout << "/////////////////////////////////\n";
	smrt_pointer<int> int_Cont01(56);
	smrt_pointer<int> int_Cont02(int_Cont01);
	int_Cont01.print();
	smrt_pointer<int> int_move(std::move(int_Cont01));
	int_move.print();
	smrt_pointer<int> ptr1(42);
	smrt_pointer<int> ptr2(12);
	std::cout << "/////////////////////////////////\n";
	std::cout << "Assignment\n";
	std::cout << "/////////////////////////////////\n";
	ptr2 = ptr1; // This calls the copy assignment operator
	std::cout << "ptr1\n";
	ptr1.print();
	std::cout << "ptr2\n";
	ptr2.print();
	std::cout << "/////////////////////////////////\n";
	std::cout << "= assignment with rvalue\n";
	std::cout << "/////////////////////////////////\n";
	smrt_pointer<int> ptr3;
	ptr3 = std::move(ptr2);
	std::cout << "ptr3\n";
	ptr3.print();
	std::cout << "ptr2\n";
	ptr2.print();
	std::cout << "/////////////////////////////////\n";
	std::cout << "*assignment\n";
	std::cout << "/////////////////////////////////\n";
	std::cout << *ptr3 << '\n';
	std::cout << *int_Cont02<< '\n';

	std::cout << "/////////////////////////////////\n";
	std::cout << "Shared Pointer\n";
	std::cout << "/////////////////////////////////\n";

	std::vector<std::shared_ptr<std::vector<smrt_pointer<int>>>> records;
	std::shared_ptr<std::vector<smrt_pointer<int>>> int_records01 = std::make_shared<std::vector<smrt_pointer<int>>>();
	records.push_back(int_records01);
	smrt_pointer<int> int_share_01(56);
	smrt_pointer<int> int_share_02(45);
	int_records01->push_back(int_share_01);
	int_records01->push_back(int_share_02);

	std::shared_ptr<std::vector<smrt_pointer<int>>> int_records02 = std::make_shared<std::vector<smrt_pointer<int>>>();
	records.push_back(int_records02);
	smrt_pointer<int> int_share_03(22);
	smrt_pointer<int> int_share_04(12);
	int_records02->push_back(int_share_03);
	int_records02->push_back(int_share_04);
	
	std::shared_ptr<std::vector<smrt_pointer<int>>> int_records03 = std::make_shared<std::vector<smrt_pointer<int>>>();
	records.push_back(int_records03);
	smrt_pointer<int> int_share_05(1244);
	smrt_pointer<int> int_share_06(4556);
	int_records03->push_back(int_share_05);
	int_records03->push_back(int_share_06);

	// The smrt_pointer objects will remain in scope during the loop.
	int list = 1;
	for (std::shared_ptr<std::vector<smrt_pointer<int>>> rec : records) {
		std::cout << "List: " << list << '\n';
		int total_num = 0;
		for (smrt_pointer<int> val : *rec) {
			val.print();
			total_num++;
		}
		list++;
		std::cout << '\n';
	}

	std::shared_ptr<std::vector<smrt_pointer<int>>> int_records04 = std::make_shared<std::vector<smrt_pointer<int>>>();
	smrt_pointer<int> int_share_07(1244);
	smrt_pointer<int> int_share_08(4556);
	int_records04->push_back(int_share_07);
	int_records04->push_back(int_share_08);

	std::cout << "Reference Count:" << int_records04.use_count() << '\n';

	for (std::shared_ptr<std::vector<smrt_pointer<int>>> vec : records)
	{
		std::cout << "use_count: " << vec.use_count() << std::endl;
	}

}
