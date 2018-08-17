/*Database program in C++ by Dipan Bhusal */

#include<iostream> //header to perform input output operations contains objects like cout, cin and cerr
#include<conio.h> // Windows only header which provides C function for console IO manipulations
#include<fstream> //header to perform Input Output operations in file
#include<stdio.h> //header to perform Input/Output operations
#include<windows.h> //Windows.h is the main header file for WinAPI which is Anything that involves window creation/management or communication with the OS or filesystem.
using namespace std;

class employee
{

	int idNum;
	long int salary;
	int choicee;
	int numWorker;
	int search_id;
	int limit;
	char name[100];
	public:
	void choice(); // takes user's choice 
	void viewInfo(); // search  the particular record from database
	void inputInfo(); //input the record in database file	 
	void input();  //takes user's input	
	void displayData(); // display record  to user	
	void displayAll();  // display record form database file	
	void modifyData();  // modify  particular  record form database	
	void deleteData(); // delete particular record from database
	void backup(); //to view delected data
	
}imp;



	void employee::choice() // takes user's choice
		{
			for(;;){
				system ("CLS");
 cout   << "\n\t\t|--------------------------------------------------|" << endl

        << "\t\t|                  .::MAIN MENU::.                 |" << endl

        << "\t\t|--------------------------------------------------|" << endl

        << "\t\t| 1.   Add Employee's Record                       |" << endl

        << "\t\t| 2.   Look Up Existing Employee                   |" << endl

        << "\t\t| 3.   Delete Employee's Information               |" << endl

        << "\t\t| 4.   View All Employee's Record      	           |" << endl
        << "\t\t| 5.   Recycle Bin                                 |" << endl
        << "\t\t| 6.   Modify The Record                           |" << endl
        << "\t\t| 7.   Exit                                        |" << endl
        << "\t\t|--------------------------------------------------|" << endl

         << "\t\t Selection: ";

			cin >> choicee;
			switch(choicee){
				case 1:
					inputInfo();
					break;
				case 2:
					viewInfo();
					break;
				case 3:
					deleteData();
					break; 
				case 4:
					displayAll();
					break;
				case 5:
					backup();
				case 6:
					modifyData();
				case 7:
					exit(0);
				default:
					cout << "Enter the valid option....\n";
		}
		cout << "Press any key to return to main menu. ";
	
		getch(); }
	}
	
	
	
	 void employee::input() //input information of employee
	 {
	 	cout << "\nEnter Id no::" ;
			cin >> idNum;
			cin.ignore();
			cout << "Enter name::";
			cin.getline(name, 200);
			cout <<"Enter Salary:";
			cin>> salary;
			cin.ignore();
	 }
	
	
	
	void	employee::inputInfo()
		{
			fstream dipan;
				
				 dipan.open("employe_data.dat", ios::out| ios::app |ios::binary);
				 do{
				input();
				dipan.write((char*)&imp, sizeof(employee));
				cout << "\nWant to add more? y/n>>>";
		} 		while(getchar() == 'y');
					cout << "Data added sucessfully......\n";
				 dipan.close();
				
		 }
		 
		 
		 
		 	void employee::displayData()
	{
			cout << "Id number::" <<  idNum << endl;
			cout << "Name::"<< name << endl;
			cout << "Salary::$" << salary << endl;
			cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	}
	
	
	
	
	void employee::displayAll()
	{
		ifstream disp("employe_data.dat", ios::in | ios::binary);
		cout << "The record of whole employees:-\n";
		while(disp.read((char*)&imp, sizeof(imp)))
		{
			imp.displayData();
		}
		disp.close();
}



	void employee::viewInfo() //for Searching The employee's database
		{
			int idno;
				int count = 0;
			ifstream viewIn("employe_data.dat", ios::in |ios::binary);
				cout <<"\nEnter the Id number you want to search::" ;
			cin >> idno;


				while(viewIn.read((char*)&imp,sizeof(employee))) //we can also do while(viewIn.read((char*)&imp,sizeof(employee)))
				{ 
					if(idno == idNum) //checks if input value matches with idNum or not
					{
						cout << "Search Sucessful....\n"; 
					displayData();
						count++;	
						
					}
				
				}
					 if(count == 0)
						cout << "Sorry!!!The Id number "<< idno <<" is not in the database..\n"<< endl;
				
		 viewIn.close();
}	



void employee::modifyData()
{
	int id_mod;
	int count = 0;
	fstream modify("employe_data.dat", ios::in | ios::out|ios::ate | ios::binary );
	cout <<"Enter the Id number of employee you want to modify::";
	cin >> id_mod;
	modify.seekg(0);
	while(modify.read((char*)&imp,sizeof(employee)))
	{
		if(id_mod == idNum){
			
			cout <<"\nId found sucessfully...\nEnter the new modified information::\n";
			input();
			modify.seekp(modify.tellp() - sizeof(employee));
			modify.write((char*)&imp,sizeof(employee));
			count++;
		}
	
	}
	if(count == 0)
		cout<< "The id number " << id_mod << "  is not in database.\n";
	modify.close();
}



void employee::deleteData() //for delecting data
{
	int found = 0;
	int search_id;
ifstream empData("employe_data.dat", ios::in |ios::binary); 
ofstream backup("backup.dat",ios::out | ios::app|ios::binary); //opening new trash file 
ofstream tempData("temp.dat",ios::out|ios::binary); //opening new temp file
cout<<"\nEnter the Roll No. whose record is to be deleted: ";
cin >> search_id;
empData.read((char*)&imp, sizeof(employee)); //employe_data.txt file in read mode
while(!empData.eof() ) //loop continues until it finds end-of-file in fio file
{
if(search_id == idNum)
{
	cout << "Delecting the following data form database:--------"<<endl;
	displayData();
	backup.write((char*)&imp, sizeof(employee)); //writes the matched data in  trash.txt file
	found++; //if search id matched to id number then found increased by 1 
} else {
	tempData.write((char*)&imp, sizeof(employee));  //writes remaining (not matched) data in temp
}
	empData.read((char*)&imp, sizeof(employee)); //employe_data.txt file in read mode
	
} if(found == 0){
	cout << "The provided Id number is not in the database."<<endl;
}
empData.close();
tempData.close();
std::remove("employe_data.dat"); //deleted or remove employe_data.txt file
std::rename("temp.dat","employe_data.dat"); //renames temp.txt file to   employe_data.txt file
}	



	void employee::backup()
	{
		cout<< "The delected data are:-"<<endl;
		ifstream back("backup.dat", ios::binary);
		while(back.read((char*)&imp, sizeof(employee)))
		{
			displayData();
		}
		cout << "\nPress any key to return to main menu.";
		getch();
		choice();
	}
	
	
	
int main()
{
	SetConsoleTitle("Database Program By Dipan Bhusal");
	
	system("COLOR 70");
imp.choice();
return 0;
} 
