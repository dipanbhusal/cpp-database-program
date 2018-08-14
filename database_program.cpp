/*Database program in C++ by Dipan Bhusal */

#include<iostream>
#include<string.h>
#include<conio.h>
#include<fstream>
#include<stdio.h>
#include<windows.h>
using namespace std;

class employee
{

	int idNum, salary;
	int choicee;
	int numWorker;
	int search_id;
	int limit;
	string name;
	public:
	void choice();
	int viewInfo();
	void getInfo();
	void inputInfo();
	void input();
	void searchId();
	void remove(string);
	void displayData();
	void displayAll();
	void deleteData();
	void backup(); //to view delected data
}imp;

	void employee::displayData()
	{
			cout << "Id number: " <<  idNum << endl;
			cout << "Name: "<< name << endl;
			cout << "Salary: " << salary << endl;
			cout <<"================================================================================"<<endl;
	}
	void employee::displayAll()
	{
		ifstream disp("employe_data.txt", ios::in);
		while(disp >> idNum >> name >> salary)
		{
			imp.displayData();
			
		}
		disp.close();
	}
	void employee::choice()
		{
			for(;;){
 cout   << "\n\t\t|--------------------------------------------------|" << endl

        << "\t\t|                  .::MAIN MENU::.                 |" << endl

        << "\t\t|--------------------------------------------------|" << endl

        << "\t\t| 1.   Add Employee's Record                       |" << endl

        << "\t\t| 2.   Look Up Existing Employee                   |" << endl

        << "\t\t| 3.   Delete Employee's Information               |" << endl

        << "\t\t| 4.   View All Employee's Informations List       |" << endl

        << "\t\t| 5.   Recycle Bin                                 |" << endl
        << "\t\t| 6.   Exit                                        |" << endl
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
					exit(1);
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
			getline(cin,name);
			cout <<"Enter Salary:";
			cin>> salary;
			cin.ignore();
	 }
	void	employee::inputInfo()
		{
			fstream dipan;
				do{
				 dipan.open("employe_data.txt", ios::out| ios::app);
				input();
				dipan << idNum <<'\t'<< name << '\t' << salary <<endl;
				cout << "\nWant to add more? y/n>>>";
		} 		while(getchar() == 'y');
				 dipan.close();
				choice();
		 }
		 
	employee::viewInfo() //for Searching The employee's database
		{
			int count = 0;
			ifstream viewIn("employe_data.txt", ios::out); 
			searchId();
			int i = 0;
				while(viewIn >> idNum >> name >> salary){ 
					if(search_id == idNum) //checks if input value matches with idNum or not
					{
						displayData();
						count++	;
					}
					}
					 if(count == 0){
						cout << "Sorry!!!The Id number "<< search_id <<" is not in the database..\n"<< endl;
					}
		 viewIn.close();		
	}  
		void employee::searchId()
		{
			
			cout <<"\nEnter the Id number you want to search::" ;
			cin >> search_id;			
		}	
void employee::deleteData() //for delecting data
{
	int found = 0;
	int search_id;
ifstream fio("employe_data.txt", ios::in); 
ofstream foout("backup.txt",ios::out | ios::app); //opening new trash file 
ofstream fout("temp.txt",ios::out); //opening new temp file
cout<<"\nEnter the Roll No. whose record is to be deleted: ";
cin >> search_id;
fio >> idNum >> name >> salary; //employe_data.txt file in read mode
while(!fio.eof() ) //loop continues until it finds end-of-file in fio file
{
if(search_id == idNum)
{
	cout << "Delecting the following data form database:--------"<<endl;
	displayData();
	foout<< idNum <<'\t'<< name << '\t' << salary <<endl; //writes the matched data in  trash.txt file
	found++; //if search id matched to id number then found increased by 1 
} else {
	fout<< idNum <<'\t'<< name << '\t' << salary <<endl;  //writes remaining (not matched) data in temp
}
	fio >> idNum >> name >> salary; //employe_data.txt file in read mode
	
} if(found == 0){
	cout << "The provided Id number is not in the database.";
}
fio.close();
fout.close();
std::remove("employe_data.txt"); //deleted or remove employe_data.txt file
std::rename("temp.txt","employe_data.txt"); //renames temp.txt file to   employe_data.txt file
}	
	void employee::backup()
	{
		cout<< "The delected data are:-"<<endl;
		ifstream back("backup.txt");
		while(back >> idNum >> name >> salary)
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
imp.choice();
return 0;
}
