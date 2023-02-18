#include <iostream>
#include <string>
#include <vector>
#include<iomanip>
#include <fstream>
using namespace std;

enum EnMinMenue {
	ShowClientList = 1, AddNewClient = 2,
	DeletClient = 3, UpdateClientData = 4,
	findClient = 5, Transactions = 6,
	ManageUsers=7,
	Logout = 8
};
enum EnTransactionsMenue
{
	deposit = 1,
	Withdrawal = 2,
	TotalBalance = 3,
	MinMenue = 4
};
enum enManageUsers {
	ListUsers = 1,
	AddNewUser = 2,
	DeleteUser = 3,
	UpdateUser = 4,
	FindUser = 5,
	MainMenue = 6
};
enum enPermissions {
Else=0,	Ell = -1, pShowClientList = 1, pAddNewClient = 2, pDeletClient = 4, pUpdateClientData = 8, pFindClient = 16,
	pTransactions = 32, pManageUsers = 64
};
struct SClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelat = false;

};
struct stUser {
	string Username;
	string Password;
	int Permissions;
	bool MarkForDelete = false;
};

stUser CurentUser;

const string ClientsFileName = "FileClientData.txt";
string UsersInfo = "Users.txt";

short ReadNumberMinMenue()
{
	short RMM = 0;;
	do {
		cout << "Please Enter Number From 1 To 8 : ";
		cin >> RMM;
	} while (RMM < 0 || RMM >8);

	return RMM;
}
short ReadTransactionsMenue()
{
	short NumberTransactionsMenue = 0;
	do
	{
		cout << "Please Enter Number From 1 To 4 : ";
		cin >> NumberTransactionsMenue;
	} while (NumberTransactionsMenue < 0 || NumberTransactionsMenue>4);

	return NumberTransactionsMenue;
}
short ReadNumberManageUsers()
{
	short NumberManageUsersCase = 0;
	do
	{
		cout << "Please Enter Number From 1 To 6 : ";
		cin >> NumberManageUsersCase;
	} while (NumberManageUsersCase < 0 || NumberManageUsersCase>6);
	
	return NumberManageUsersCase;
}

void BackToMenue();
void BackToTransactionsMenue();
void PerformingManageUsers(enManageUsers ManageUsers);
void Login();
bool CheckAccessPermissions(enPermissions Permission);
void ShowAccessDeniedMessage();
void ShowTransactionsMenue();
void PerformingTransactionsMenue(EnTransactionsMenue TransactionsMenue);
void ShowManageUsersMenue();

vector <string>  SplitString(string Line, string Delim)
{
	vector <string> Vstring;
	short Pos = 0;
	string TempString;

	while ((Pos = Line.find(Delim)) != string::npos)
	{
		TempString = Line.substr(0, Pos);

		if (TempString != "")
		{
			Vstring.push_back(TempString);
		}
		Line.erase(0, Pos + Delim.length());
	}
	if (Line != "")
	{
		Vstring.push_back(Line);
	}
	return Vstring;
}
SClient ConvertLineToRecord(string Line, string Delim = "#//#")

{
	SClient InfoStSClient;

	vector <string> VSClient = SplitString(Line, Delim);
	InfoStSClient.AccountNumber = VSClient[0];
	InfoStSClient.PinCode = VSClient[1];
	InfoStSClient.Name = VSClient[2];
	InfoStSClient.Phone = VSClient[3];
	InfoStSClient.AccountBalance = stoi(VSClient[4]);

	return InfoStSClient;
}
vector <SClient> LoadClientFromFile(string FileName)
{
	vector <SClient> VClient;
	fstream FileSClient;
	string Line;
	SClient InfoSClient;

	FileSClient.open(FileName, ios::in);

	if (FileSClient.is_open())
	{
		while (getline(FileSClient, Line))
		{
			InfoSClient = ConvertLineToRecord(Line, "#//#");

			VClient.push_back(InfoSClient);
		}
	}
	return VClient;
}
void PrintClientData(SClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintAllClientData(vector <SClient> VClient)
{
	cout << "\n\t\t\t\t\t Client Liest (" << VClient.size() << ") Client(s)";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	for (SClient ClientData : VClient)
	{
		PrintClientData(ClientData);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;
}
void CaseShowClientList()
{
	system("cls");

	if (!CheckAccessPermissions(enPermissions::pShowClientList))
	{
		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	vector <SClient> Vclintes;
	Vclintes = LoadClientFromFile(ClientsFileName);
	PrintAllClientData(Vclintes);
}

void ScrenAddNewClientS()
{
	cout << "\n======================================================\n";
	cout << "               Add New ClientS Scren                      ";
	cout << "\n======================================================\n";

}
SClient ReadSClient()
{
	SClient Client;
	cout << "Please Enter Account Number" << endl;
	getline(cin >> ws, Client.AccountNumber);

	cout << "Please Enter Pin Code" << endl;
	getline(cin, Client.PinCode);

	cout << "Please Enter Name" << endl;
	getline(cin, Client.Name);

	cout << "Please Enter Phone" << endl;
	getline(cin, Client.Phone);

	cout << "Please Enter Account Balance" << endl;
	cin >> Client.AccountBalance;

	return Client;
}
string ConvertRecordToLine(SClient Client, string Delim = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Delim;
	stClientRecord += Client.PinCode + Delim;
	stClientRecord += Client.Name + Delim;
	stClientRecord += Client.Phone + Delim;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
void SevDataToFile(string FileName, string StToLine)
{
	fstream FileSClient;
	FileSClient.open(FileName, ios::out | ios::app);

	if (FileSClient.is_open())
	{
		FileSClient << StToLine << endl;
		FileSClient.close();
	}
}
void ProcessOfAddClients()
{
	SClient Client;
	Client = ReadSClient();
	SevDataToFile(ClientsFileName, ConvertRecordToLine(Client));
}
void AddNewClientS()
{
	system("cls");

	if (!CheckAccessPermissions(enPermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	SClient Client;
	char MorClient = 'Y';
	do
	{
		system("cls");
		ScrenAddNewClientS();
		ProcessOfAddClients();
		cout << "Client added successfully Do you want to add another client ? ";
		cin >> MorClient;

	} while (MorClient == 'Y' || MorClient == 'y');
}

void ScrenDelatClientData()
{
	cout << "\n======================================================\n";
	cout << "               Delat Client Data Scren                      ";
	cout << "\n======================================================\n";

}
string ReadAccountNumber()
{
	string AccountNumber;
	cout << "Pleas Enter Account Number : ";
	cin >> AccountNumber;
	return AccountNumber;
}
bool SerchClientInVector(string AccountNumber, vector <SClient> Vclintes, SClient& Client)
{
	Vclintes = LoadClientFromFile(ClientsFileName);

	for (SClient& C : Vclintes)
	{
		if (AccountNumber == C.AccountNumber)
		{
			Client = C;
			return true;
		}
	}

	return false;
}
bool MarkClientForDelatByAccountNumber(string AccountNumber, vector <SClient>& Vclintes)
{
	for (SClient& C : Vclintes)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelat = true;
			return true;
		}
	}
	return false;
}
vector <SClient> SaveClientDataToFile(string FileName, vector <SClient> Vclintes)
{
	fstream FileSClient;

	FileSClient.open(FileName, ios::out);
	string Line;

	if (FileSClient.is_open())
	{
		for (SClient C : Vclintes)
		{
			if (C.MarkForDelat == false)
			{
				Line = ConvertRecordToLine(C);
				FileSClient << Line << endl;

			}
		}
		FileSClient.close();
	}
	return Vclintes;
}
void PrintTempClientData(SClient& Client)
{
	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

}
bool DelatClientByAccountNumber(string AccountNumber, vector <SClient>& Vclintes)
{
	SClient Client;
	char DelatRecord;
	if (SerchClientInVector(AccountNumber, Vclintes, Client))
	{
		PrintTempClientData(Client);
		cout << "Are you sure you delete the client " << AccountNumber << "? : ";
		cin >> DelatRecord;
		if (DelatRecord == 'Y' || DelatRecord == 'y')
		{
			MarkClientForDelatByAccountNumber(AccountNumber, Vclintes);
			SaveClientDataToFile(ClientsFileName, Vclintes);

			Vclintes = LoadClientFromFile(ClientsFileName);
			return true;
		}
	}
	else
	{
		cout << "Account not found " << AccountNumber;
		return false;
	}
}
void DelatClientData()
{
	system("cls");

	if (!CheckAccessPermissions(enPermissions::pDeletClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	system("cls");
	ScrenDelatClientData();
	SClient Client;
	vector <SClient> Vclintes;
	Vclintes = LoadClientFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	DelatClientByAccountNumber(AccountNumber, Vclintes);
}

void ScrenUpdateClientData()
{
	cout << "\n======================================================\n";
	cout << "               Update Client Data Scren                      ";
	cout << "\n======================================================\n";

}
SClient ReadNewVlue(string AccountNumber)
{
	SClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "Please Enter Pin Code" << endl;
	getline(cin >> ws, Client.PinCode);

	cout << "Please Enter Name" << endl;
	getline(cin, Client.Name);

	cout << "Please Enter Phone" << endl;
	getline(cin, Client.Phone);

	cout << "Please Enter Account Balance" << endl;
	cin >> Client.AccountBalance;
	return Client;
}
bool EditClientByAccountNumber(string AccountNumber, vector <SClient>& Vclintes)
{
	SClient Client;
	char EditRecord;
	if (SerchClientInVector(AccountNumber, Vclintes, Client))
	{
		PrintTempClientData(Client);
		cout << "Are you sure you Edit the client " << AccountNumber << "? : ";
		cin >> EditRecord;

		if (EditRecord == 'Y' || EditRecord == 'y')
		{

			for (SClient& C : Vclintes)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ReadNewVlue(AccountNumber);
					break;
				}
			}

			SaveClientDataToFile(ClientsFileName, Vclintes);

			cout << "\nClient Updated Successfully ";
			return true;
		}

	}
	else
	{
		cout << "Account not found " << AccountNumber;
		return false;
	}
}
void EditClientData()
{
	system("cls");

	if (!CheckAccessPermissions(enPermissions::pUpdateClientData))
	{
		ShowAccessDeniedMessage();
		return;
	}
	system("cls");
	ScrenUpdateClientData();
	SClient Client;
	vector <SClient> Vclintes;
	Vclintes = LoadClientFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	EditClientByAccountNumber(AccountNumber, Vclintes);
}

void ScrenfindClient()
{
	cout << "\n======================================================\n";
	cout << "               find Client Scren                      ";
	cout << "\n======================================================\n";

}
void findClientDataInVector(string AccountNumber, vector <SClient>& Vclintes)
{
	for (SClient& C : Vclintes)
	{
		if (C.AccountNumber == AccountNumber)
		{
			PrintTempClientData(C);
			break;
		}
	}
}
void findClientData()
{
	system("cls");

	if (!CheckAccessPermissions(enPermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	system("cls");
	ScrenfindClient();
	vector <SClient> Vclintes;
	Vclintes = LoadClientFromFile(ClientsFileName);

	string AccountNumber = ReadAccountNumber();
	findClientDataInVector(AccountNumber, Vclintes);
}

void ScrenExit()
{
	cout << "\n======================================================\n";
	cout << "               Exit Progrem -_-                      ";
	cout << "\n======================================================\n";

}
void ExitProgrem()
{
	system("cls");
	ScrenExit();
	system("pause>0");
}

short ReadDepositAmount()
{
	short DepositAmount = 0;
	cout << "Pleas Enter Deposit Amount : ";
	cin >> DepositAmount;
	return DepositAmount;
}
void ScrenDeposit()
{
	cout << "\n======================================================\n";
	cout << "               Deposit Scren                              ";
	cout << "\n======================================================\n";
}
bool DepositBalanceClientByAccountNumber(string AccountNumber, double DepositAmount, vector <SClient>& Vclintes)
{
	char ConfirmTransaction;
	cout << "Are you sure you can confirm this transaction ? Y/N ";
	cin >> ConfirmTransaction;

	if (ConfirmTransaction == 'Y' || ConfirmTransaction == 'y')
	{
		for (SClient& C : Vclintes)
		{
			if (AccountNumber == C.AccountNumber)
			{
				C.AccountBalance += DepositAmount;
				SaveClientDataToFile(ClientsFileName, Vclintes);
				cout << "Done Successfully New balance is:  " << C.AccountBalance << endl;
				return true;
			}
		}
	}
	return false;
}
void CaseMoneyeDposit()
{
	SClient Client;
	vector <SClient> Vclintes;

	system("cls");
	ScrenDeposit();
	Vclintes = LoadClientFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	while (!SerchClientInVector(AccountNumber, Vclintes, Client))
	{
		cout << "Account not found " << AccountNumber << endl;
		AccountNumber = ReadAccountNumber();
	}
	double DepositAmount = ReadDepositAmount();
	DepositBalanceClientByAccountNumber(AccountNumber, DepositAmount, Vclintes);
}

short ReadWithdrawaAmount()
{
	short WithdrawaAmount = 0;
	cout << "Pleas Enter Withdraw Amount : ";
	cin >> WithdrawaAmount;
	return WithdrawaAmount;
}
void ScrenWithdrawa()
{
	cout << "\n======================================================\n";
	cout << "               Withdrawa Scren                              ";
	cout << "\n======================================================\n";

}
void PerformingMoneyeWithdrawa()
{
	SClient Client;
	vector <SClient> Vclintes = LoadClientFromFile(ClientsFileName);
	system("cls");
	ScrenWithdrawa();

	short WithdrawaAmount = 0;
	string AccountNumber = ReadAccountNumber();

	while (!SerchClientInVector(AccountNumber, Vclintes, Client))
	{
		cout << "Account not found " << AccountNumber << endl;
		AccountNumber = ReadAccountNumber();
	}

	PrintTempClientData(Client);


	for (SClient& C : Vclintes)
	{
		if (C.AccountNumber == AccountNumber)
		{
			WithdrawaAmount = ReadWithdrawaAmount();

			while (WithdrawaAmount > C.AccountBalance)
			{
				cout << "Amount Exceeds the balance, you can withdraw up to : ";
				cout << Client.AccountBalance << endl;
				WithdrawaAmount = ReadWithdrawaAmount();
			}
		}
	}
	DepositBalanceClientByAccountNumber(AccountNumber, WithdrawaAmount * -1, Vclintes);
}
void PrintClientDataTotalBalance(SClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintAllClientDataTotalBalance(vector <SClient> VClient)
{
	cout << "\n\t\t\t\t\t Client Liest (" << VClient.size() << ") Client(s)";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Account Balance";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	for (SClient ClientData : VClient)
	{
		PrintClientDataTotalBalance(ClientData);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;
}
void PerformingTotalBalance()
{
	SClient Client;
	vector <SClient> Vclintes = LoadClientFromFile(ClientsFileName);
	system("cls");

	double TotalBlance = 0;
	for (SClient& C : Vclintes)
	{
		TotalBlance += C.AccountBalance;
	}
	PrintAllClientDataTotalBalance(Vclintes);
	cout << "                                  Total Blance " << TotalBlance << endl;
}

void ShowTransactionsMenue()
{
	system("cls");

	if (!CheckAccessPermissions(enPermissions::pTransactions))
	{
		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	cout << "\n======================================================\n";
	cout << "              Show Transactions Menue Screan\t\t";
	cout << "\n======================================================\n";

	cout << "\t[1] deposit \n";
	cout << "\t[2] Withdrawal\n";
	cout << "\t[3] TotalBalance\n";
	cout << "\t[4] MinMenue\n";
	cout << "\n======================================================\n";

	PerformingTransactionsMenue((EnTransactionsMenue)ReadTransactionsMenue());
}
void PerformingTransactionsMenue(EnTransactionsMenue TransactionsMenue)
{

	switch (TransactionsMenue)
	{
	case EnTransactionsMenue::deposit:
		CaseMoneyeDposit();
		BackToTransactionsMenue();
		break;
	case EnTransactionsMenue::Withdrawal:
		PerformingMoneyeWithdrawa();
		BackToTransactionsMenue();
		break;
	case EnTransactionsMenue::TotalBalance:
		PerformingTotalBalance();
		BackToTransactionsMenue();

	case EnTransactionsMenue::MinMenue:
		BackToMenue();
	}

}

void PerfromMainMenueOptio(EnMinMenue MinMenue)
{
	switch (MinMenue)
	{
	case EnMinMenue::ShowClientList:
		CaseShowClientList();
		BackToMenue();
		break;
	case EnMinMenue::AddNewClient:
		AddNewClientS();
		BackToMenue();
		break;
	case EnMinMenue::DeletClient:
		DelatClientData();
		BackToMenue();
		break;
	case EnMinMenue::UpdateClientData:
		EditClientData();
		BackToMenue();
		break;
	case EnMinMenue::findClient:
		findClientData();
		BackToMenue();
		break;

	case EnMinMenue::Transactions:
		ShowTransactionsMenue();
		BackToMenue();
		break;
	case EnMinMenue::ManageUsers:
		ShowManageUsersMenue();
		BackToMenue();
	break;
	case EnMinMenue::Logout:
		system("cls");
		Login();
	}
}
void ShowMinMenue()
{
	system("cls");
	cout << "\n======================================================\n";
	cout << "              Show Main Menue Screan\t\t";
	cout << "\n======================================================\n";

	cout << "\t[1] Show Client List\n";
	cout << "\t[2] Add New Client\n";
	cout << "\t[3] Delet Client\n";
	cout << "\t[4] Update Client Data\n";
	cout << "\t[5] find Client\n";
	cout << "\t[6] Transactions \n";
	cout << "\t[7] Manage Users \n";
	cout << "\t[8] Logout \n";
	cout << "\n======================================================\n";
	PerfromMainMenueOptio((EnMinMenue)ReadNumberMinMenue());
}
void BackToMenue()
{
	cout << "Press any key to Back To The Menu ";
	system("pause");
	ShowMinMenue();
}
void BackToTransactionsMenue()
{
	cout << "Press any key to Back To The Menu ";
	system("pause");
	ShowTransactionsMenue();
}

void LoginScren()
{
	cout << "\n======================================================\n";
	cout << "               Login Scren                              ";
	cout << "\n======================================================\n";

}
string ReadUsernameLogin(string Username)
{
	cout << "Please Enter Username ? ";
	getline(cin >> ws, Username);
	return Username;
}
string ReadPasswordLogin(string Password)
{
	cout << "Please Enter Password ? ";
	getline(cin >> ws, Password);
	return Password;
}
stUser ConvertLineToRecordUserInfo(string Line, string Delim = "#//#")
{
	stUser User;

	vector <string> vUser = SplitString(Line, Delim);

	User.Username = vUser[0];
	User.Password = vUser[1];
	User.Permissions = stoi(vUser[2]);

	return User;
}

bool CheckAccessPermissions(enPermissions Permissions)
{
	if (CurentUser.Permissions == enPermissions::Ell)
		return true;

	if ((Permissions & CurentUser.Permissions) == Permissions)
		return true;
	else
		return false;
}
void ShowAccessDeniedMessage() {
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin."; 
	cout << "\n------------------------------------\n";

}

void ManageUserMenuScran()
{
	cout << "\n======================================================\n";
	cout << "                  Manage User Menu Scran                  ";
	cout << "\n======================================================\n";

}
string ConvertRecordToLineUserInfo(stUser user, string Delim = "#//#")
{
	string userinfoRecord = "";

	userinfoRecord += user.Username + Delim;
	userinfoRecord += user.Password + Delim;
	userinfoRecord += to_string(user.Permissions);

	return userinfoRecord;
}
vector <stUser> LoadUserInfoFromFile(string FileName)
{
	vector <stUser> vUser;
	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stUser User;

		while (getline(MyFile, Line))
		{
			User = ConvertLineToRecordUserInfo(Line);

			vUser.push_back(User);
		}
	}
	return vUser;
}
bool FindUsernameInfoInVector(string Username, string Password, stUser& User)
{
	vector <stUser> Vuser;
	Vuser = LoadUserInfoFromFile(UsersInfo);

	for (stUser & U : Vuser)
	{
		if (U.Username == Username && U.Password == Password)
		{
			User = U;
			return true;
		}
	}
	return false;
}
bool FindUserByUsername(string Username,string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stUser User;

		while (getline(MyFile, Line))
		{
			User = ConvertLineToRecordUserInfo(Line);

			if (User.Username == Username)
			{
				MyFile.close();
				return true; 
			}

		}
		MyFile.close();
	}
	return false;
}
void Login()
{
	vector <stUser> Vuser;
	stUser User;
	LoginScren();
	string Username,Password;
    Username = ReadUsernameLogin(Username);
	Password = ReadPasswordLogin(Password);

	while (FindUsernameInfoInVector(Username, Password, CurentUser) == false)
	{
		system("cls");
		LoginScren();
		cout << "Invalid Username/Password \n";
		Username = ReadUsernameLogin(Username);
		Password = ReadPasswordLogin(Password);
	}

	ShowMinMenue();
}
void ShowManageUsersMenue()
{
	system("cls");
	if (!CheckAccessPermissions(enPermissions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		return;
	}
	system("cls");
	cout << "\n======================================================\n";
	cout << "              Show Manage Users Menue Screan\t\t";
	cout << "\n======================================================\n";

	cout << "\t[1] List Users \n";
	cout << "\t[2] Add New User\n";
	cout << "\t[3] Delete User\n";
	cout << "\t[4] Update User\n";
	cout << "\t[5] Find User\n";
	cout << "\t[6] Main Menue\n";

	cout << "\n======================================================\n";
	PerformingManageUsers((enManageUsers)ReadNumberManageUsers());
}
void BackToManageUsersMenue()
{
	cout << "Press any key to Back To The Menu ";
	system("pause");
	ShowManageUsersMenue();
}

void PrintClientData(stUser User)
{
	cout << "| " << setw(15) << left << User.Username;
	cout << "| " << setw(10) << left << User.Password;
	cout << "| " << setw(40) << left << User.Permissions;

}
void PrintListUsersInfo(vector <stUser> vUser)
{
	cout << "\n\t\t\t\t\t User Liest (" << vUser.size() << ") Client(s)";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permission";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	for (stUser& UserData : vUser)
	{
		PrintClientData(UserData);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

}
void CaseShowUserList()
{
	vector <stUser> vUser;
	vUser = LoadUserInfoFromFile(UsersInfo);
	system("cls");
	PrintListUsersInfo(vUser);
}

void ScrenAddUser()
{
	cout << "\n======================================================\n";
	cout << "               Add User Scren                              ";
	cout << "\n======================================================\n";
}
short PermissionsShowClientList(int Permissions)
{
	char Access;
	cout << "\nShow ClientList Y/n ";
	cin >> Access;
	if (Access == 'y' || Access == 'Y')
	{
		Permissions = enPermissions::pShowClientList;
		return Permissions;
	}
	else
		Permissions = enPermissions::Else;

	return Permissions;
}
short PermissionsAddNewClient(int Permissions)
{
	char Access;
	cout << "\nAdd NewClient  Y/n ";
	cin >> Access;
	if (Access == 'y' || Access == 'Y')
	{
		Permissions += enPermissions::pAddNewClient;
		return Permissions;
	}
	else
		Permissions += enPermissions::Else;
	return Permissions;

}
short PermissionsDeletClient(int Permissions)
{
	char Access;
	cout << "\nDelet Client   Y/n ";
	cin >> Access;
	if (Access == 'y' || Access == 'Y')
	{
		Permissions += enPermissions::pDeletClient;
		return Permissions;
	}
	else
		Permissions += enPermissions::Else;
	return Permissions;

}
short PermissionsUpdateClientData(int Permissions)
{
	char Access;
	cout << "\n Update Client Data  Y/n ";
	cin >> Access;
	if (Access == 'y' || Access == 'Y')
	{
		Permissions += enPermissions::pUpdateClientData;
		return Permissions;
	}
	else
		Permissions += enPermissions::Else;
	return Permissions;

}
short PermissionsfindClient(int Permissions)
{
	char Access;
	cout << "\n find Client Y/n ";
	cin >> Access;
	if (Access == 'y' || Access == 'Y')
	{
		Permissions += enPermissions::pFindClient;
		return Permissions;
	}
	else
		Permissions += enPermissions::Else;
	return Permissions;

}
short PermissionsTransactions(int Permissions)
{
	char Access;
	cout << "\n Transactions  Y/n ";
	cin >> Access;
	if (Access == 'y' || Access == 'Y')
	{
		Permissions += enPermissions::pTransactions;
		return Permissions;
	}
	else
		Permissions += enPermissions::Else;
	return Permissions;

}
short PermissionsManageUsers(int Permissions)
{

	char Access;
	cout << "\n Manage Users Y/n ";
	cin >> Access;
	if (Access == 'y' || Access == 'Y')
	{
		Permissions += enPermissions::pManageUsers;
		return Permissions;
	}
	else
		Permissions += enPermissions::Else;
	return Permissions;

}
int ReadPermissionsUser()
{
	char AccessPermissions = false;
	cout << "Do You Want Give Full Access Y/N ? ";
	cin >> AccessPermissions;
	int Permissions = 0;
	if (AccessPermissions == 'Y' || AccessPermissions == 'y')
	{
		 Permissions = -1;
		 return Permissions;
	}

	else
		cout << "Do You Want Give Access : \n";
	{
		Permissions = PermissionsShowClientList(Permissions);
		Permissions = PermissionsAddNewClient(Permissions);
		Permissions = PermissionsDeletClient(Permissions);
		Permissions = PermissionsUpdateClientData(Permissions);
		Permissions = PermissionsfindClient(Permissions);
		Permissions = PermissionsTransactions(Permissions);
		Permissions = PermissionsManageUsers(Permissions);
	}
	return Permissions;
}
stUser ReadUsernameAndPassword()
{
	stUser  User;
	vector <stUser> vUser;
	User.Username = ReadUsernameLogin(User.Username);
	if (FindUserByUsername(User.Username, UsersInfo))
	{
		while (FindUserByUsername(User.Username, UsersInfo) == true)
		{
			cout << "Usernam " << User.Username << " Already exists Entr Usernam Different \n";
			User.Username = ReadUsernameLogin(User.Username);
		}
	}
	User.Password = ReadPasswordLogin(User.Password);
	User.Permissions = ReadPermissionsUser();
	return User;
}
void AddNew_1_User(stUser  User)
{
	User = ReadUsernameAndPassword();
	SevDataToFile(UsersInfo, ConvertRecordToLineUserInfo(User));
}
void CaseAddUser()
{
	stUser User;
	char MorAddUser = false;
	do
	{
		system("cls");
		ScrenAddUser();
		AddNew_1_User(User);
		
		cout << "user added successfully Do You Want Add Mor User Y/N : ";
		cin >> MorAddUser;
	} while (MorAddUser == 'Y' || MorAddUser == 'y');
}

void ScrenDelatUserData()
{
	cout << "\n======================================================\n";
	cout << "               Delat User Data Scren                      ";
	cout << "\n======================================================\n";

}
bool MarkUserForDelatByUsername(string Username, vector <stUser>& vUser)
{
	for (stUser & U : vUser)
	{
		if (U.Username == Username)
		{
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
vector <stUser> SaveClientDataToFile(string FileName, vector <stUser>& vUser)
{
	fstream FileSClient;

	FileSClient.open(FileName, ios::out);
	string Line;

	if (FileSClient.is_open())
	{
		for (stUser U : vUser)
		{
			if (U.MarkForDelete == false)
			{
				Line = ConvertRecordToLineUserInfo(U);
				FileSClient << Line << endl;

			}
		}
		FileSClient.close();
	}
	return vUser;
}
void PrintCardUsertData(stUser  User)
{
	cout << "-----------------------------------";
	cout << "\nUser Name  : " << User.Username;
	cout << "\nPassword : " << User.Password;
	cout << "\nPermissions : " << User.Permissions;
	cout << "\n-----------------------------------\n";
}
void DelatUserByUsername(string Username, vector <stUser>& vUser)
{
	    char DelatRecord = 'n';
		stUser User;
		system("cls");

		ScrenDelatUserData();

		Username = ReadUsernameLogin(Username);

		vUser = LoadUserInfoFromFile(UsersInfo);

		if (!FindUserByUsername(User.Username, UsersInfo))
		{
			while (!FindUserByUsername(User.Username, UsersInfo))
			{
				cout << "Username " << Username << " Not Found Try Again \n";

				Username = ReadUsernameLogin(Username);

			}
		}
		PrintCardUsertData(User);
		cout << "Are you sure you delete the User  " << User.Username << " ? ";
		cin >> DelatRecord;
		if (DelatRecord == 'Y' || DelatRecord == 'y')
		{
			MarkUserForDelatByUsername(Username,vUser);
			SaveClientDataToFile(UsersInfo,vUser);
			vUser = LoadUserInfoFromFile(UsersInfo);

			cout << "\n\nDelated User *_* \n";
		}
		else
		{
			BackToManageUsersMenue();
		}
}
void CaseDelatUser()
{
	stUser User;
	vector <stUser> vUser;
	string Username;
	DelatUserByUsername(Username, vUser);
}

void ScrenUpdateUserData()
{
	cout << "\n======================================================\n";
	cout << "               Update User Data Scren                      ";
	cout << "\n======================================================\n";

}
bool UpdateUserDataByUsername(string Username, vector <stUser>& vUser)
{
	stUser User;
	char EditRecord;
	if (FindUserByUsername(User.Username, UsersInfo))
	{
		PrintCardUsertData(User);
		cout << "Are you sure you Edit the User " << Username << " ? : ";
		cin >> EditRecord;

		if (EditRecord == 'Y' || EditRecord == 'y')
		{

			for (stUser& C : vUser)
			{
				if (C.Username == Username)
				{
					C.Password = ReadPasswordLogin(C.Password);
					C.Permissions = ReadPermissionsUser();
					break;
				}
			}

			SaveClientDataToFile(UsersInfo, vUser);

			cout << "\nUser Updated Successfully ";
			return true;
		}

	}
	else
	{
		cout << "\nUsername not found " << Username;
		return false;
	}
}
void CaseUpdateUserData()
{
	system("cls");
	ScrenUpdateUserData();
	stUser User;
	vector <stUser> vUser;
	string Username;

	Username = ReadUsernameLogin(Username);
	vUser = LoadUserInfoFromFile(UsersInfo);
	UpdateUserDataByUsername(Username,vUser);
}

void ScrenfindUser()
{
	cout << "\n======================================================\n";
	cout << "               find User Scren                      ";
	cout << "\n======================================================\n";

}
void findUserDataInVector(string Username, vector <stUser>& vUser)
{
	for (stUser& C : vUser)
	{
		if (C.Username == Username)
		{
			PrintCardUsertData(C);
			break;
		}
	}
}
void findUserData()
{
	system("cls");
	ScrenfindUser();
	vector <stUser> vUser;
	stUser User;
	string Username;

	Username = ReadUsernameLogin(Username);

	if (!FindUserByUsername(User.Username, UsersInfo))
	{
		while (!FindUserByUsername(User.Username, UsersInfo))
		{
			cout << "Username " << Username << " Not Found Try Again \n";

			Username = ReadUsernameLogin(Username);

		}
	}
	vUser = LoadUserInfoFromFile(UsersInfo);
	findUserDataInVector(Username, vUser);
}

void PerformingManageUsers(enManageUsers ManageUsers)
{
	switch (ManageUsers)
	{
	case enManageUsers::ListUsers:
		CaseShowUserList();
		BackToManageUsersMenue();
	break;
	case enManageUsers::AddNewUser:
		CaseAddUser();
		BackToManageUsersMenue();
		break;
	case enManageUsers::DeleteUser:
		CaseDelatUser();
		BackToManageUsersMenue();
		break;
	case enManageUsers::UpdateUser:
		CaseUpdateUserData();
		BackToManageUsersMenue();
		break;
	case enManageUsers::FindUser:
		findUserData();
		BackToManageUsersMenue();
		break;
	case enManageUsers::MainMenue:
		BackToMenue();
		break;
	}
}

int main()
{
	Login();

	system("pause>0");
}