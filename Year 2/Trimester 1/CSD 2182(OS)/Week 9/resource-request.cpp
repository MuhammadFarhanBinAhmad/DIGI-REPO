// Banker's Algorithm
#include <iostream>
using namespace std;

bool check_safety(int *allocation, int *max, 
				int *avail, int *need, 
				int nProcess, int mResource)
{
	int i, j, k;
	int *finish = new int[nProcess];
	int *seq = new int[nProcess]; 
	int index = 0;
	for (k = 0; k < nProcess; k++) {
		finish[k] = 0;
	}
	
	for (i = 0; i < nProcess; i++) {
		for (j = 0; j < mResource; j++)
			need[i*mResource+j] = max[i*mResource+j] - allocation[i*mResource+j];
	}

	for (k = 0; k < nProcess; k++) {
		for (i = 0; i < nProcess; i++) {
			if (finish[i] == 0) { 
				int flag = 0;
				for (j = 0; j < mResource; j++) {
					if (need[i*mResource+j] > avail[j]){
						flag = 1;
						break;
					}
				}
	 
				if (flag == 0) {
					seq[index++] = i;
					for (int l = 0; l < mResource; l++)
						avail[l] += allocation[i*mResource+l];
					
					finish[i] = 1;
				}
			}
		}
	}
   
	int flag = 1;
   
	// To check if sequence is safe or not
	for(int i = 0; i<nProcess; i++)
	{
		if(finish[i]==0)
		{
			flag = 0;
			std::cout << "The given sequence is not safe";
			break;
		}
	}
 
	if(flag==1)
	{
		std::cout << "The Safe Sequence is" << std::endl;
		for (i = 0; i < nProcess - 1; i++)
			std::cout << " Process " << seq[i] << " =>";
		std::cout << " Process " << seq[nProcess - 1] << std::endl;
	}

	delete finish;
	delete seq;
	
	return flag;
}
	
int main()
{
	// P0, P1, P2, P3, P4 are the Processes 
	// there are 3 types of resources 
	
	int nProcess, mResource, i, j, k;
	nProcess = 5; // Number of processes
	mResource = 3; // Number of resources
	// Allocation Matrix
	int allocation[5*3] = {  0, 1, 0 , // P0 
						 2, 0, 0 , // P1
						 3, 0, 2 , // P2
						 2, 1, 1 , // P3
						 0, 0, 2  }; // P4
	// MAX Matrix 
	int max[5*3] = {  7, 5, 3 , // P0 
                    3, 2, 2 , // P1
                    9, 0, 2 , // P2
                    2, 2, 2 , // P3
                    4, 3, 3  }; // P4
	
	// Available Resources
	int avail[3] = { 3, 3, 2 };  
	int *need = new int[nProcess*mResource];
	//check_safety(allocation, max, avail, need, nProcess, mResource);
	for (i = 0; i < nProcess; i++) {
		for (j = 0; j < mResource; j++)
			need[i*mResource+j] = max[i*mResource+j] - allocation[i*mResource+j];
	}
 
	//resource request algo
	int A, B, C;
	int PID;
	int cont = 1;
	while(1)
	{
		std::cout << "\nContinue? 0-No " << std::endl;
		std::cin >> cont;	
		if (!cont)
			break;
		std::cout << "Process id " << std::endl;
		std::cin >> PID;
		std::cout << "request for A, B, C" << std::endl;
		std::cin >> A;
		std::cin >> B;
		std::cin >> C;		

		int req [3] = { A, B, C };  	
		/*
		Requesti = request vector for process Ti.  
		If Requesti [j] = k then process Ti wants k instances of resource type Rj
		If Requesti < Needi go to step 2.  Otherwise, raise error condition, 
		since process has exceeded its maximum claim
		If Requesti < Available, go to step 3.  Otherwise Ti  must wait, 
		since resources are not available
		Pretend to allocate requested resources to Ti by modifying the state as follows:
			Available = Available  – Requesti;
			Allocationi = Allocationi + Requesti;
			Needi = Needi – Requesti;
		If safe then the resources are allocated to Ti
		If unsafe then Ti must wait, and the old resource-allocation state is restored

		*/
		int flag = 1;
		std::cout << "Need ";
		for (j = 0; j < mResource; j++)
			std::cout << need[PID*mResource+j] << " ";
		std::cout << std::endl;

		for (j = 0; j < mResource; j++)
			if(req[j] > need[PID*mResource+j])
			{
				flag = 0;
				break;
			}	
			
		if (flag == 0)
		{
			std::cout << "process has exceeded its maximum claim\n";
			continue;
		}		
		
		std::cout << "Available ";
		for (j = 0; j < mResource; j++)
			std::cout << avail[j] << " ";
		std::cout << std::endl;

		for (j = 0; j < mResource; j++)
			if(req[j] > avail[j])
			{
				flag = 0;
				break;
			}
					
		if (flag == 1)
		{	
			for (j = 0; j < mResource; j++) {
				avail[j] = avail[j] - req[j];
				allocation[PID*mResource+j] = allocation[PID*mResource+j] + req[j];
				need[PID*mResource+j] = need[PID*mResource+j] - req[j];	
			}
			check_safety(allocation, max, req, need, nProcess, mResource);
		}
		else
		{
			std::cout << "request does not succeed due to insufficient resources" << std::endl;
		}	
	}
	
	delete need;
    return 0;
}