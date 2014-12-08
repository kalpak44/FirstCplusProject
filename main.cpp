#include <iostream>
#include "AccountsManager.h"
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <iomanip>

void userInterface(AccountsManager *manager);
void installDemoUsers(AccountsManager *manager);
void printHelp();
void print_clients(AccountsManager *manager);
void add_client(AccountsManager *manager);
void remove_client(AccountsManager *manager);
void edit_client(AccountsManager *manager);
void edit_client_menu(Account *user);
void more_two(AccountsManager *manager);
void count(AccountsManager *manager);
void get_destination(AccountsManager *manager);
void get_equals(AccountsManager *manager);
void save(AccountsManager *manager);


int main(int argc, char** argv) {
	/*
	TransactionManager *opert = new TransactionManager(0);
	opert->addInputTransaction(12.45);
	opert->addOutputTransaction(2.45);
	opert->print_operation();
	*/
	
	AccountsManager *manager = new AccountsManager();
	
	//My Tests ))
	/*
	installDemoUsers(manager);
	Account *user = manager->getAccount("a99999");
    TransactionManager *tmanager = user->getTmanager();
	tmanager->addInputTransaction(200);
	double balance = user->getBalance();
	double result = balance + 200;
	user->setMoney(result);
	tmanager->addOutputTransaction(20);
	balance = user->getBalance();
	result = balance - 20;
	user->setMoney(result);
	save(manager);
    */
    
	userInterface(manager);
    //more_two(manager);
	return 0;
	
}

void userInterface(AccountsManager *manager){
	cout << "Enter 'help' to view documentation." << endl;
	string command = "";
	while(true){
		fflush(stdin);
		cout << endl <<"It is main menu." << endl << "command > ";
		getline(cin, command);
		if(command == "exit") {
			break;
		}
		else if(command == "help"){
			printHelp();
		}
		else if(command == "clear"){
			system("cls");
			userInterface(manager);
		}
		else if(command == "install_demo"){
			installDemoUsers(manager);
		}
		else if(command == "print_clients"){
			print_clients(manager);
		}
		else if(command == "add_client"){
			add_client(manager);
		}
		else if(command == "remove_client"){
			remove_client(manager);
		}
		else if(command == "edit_client"){
			edit_client(manager);
		}
		else if(command == "see_more_acc"){
			more_two(manager);
		}
		else if(command == "count_clients"){
			count(manager);
		}
		else if(command == "get_destination"){
			get_destination(manager);
		}
		else if(command == "get_equals"){
			get_equals(manager);
		}
		else if(command == "save"){
			save(manager);
		}
		
		else{
			cout << "Invalid command." << endl << endl;
		}
	}
}


void get_destination(AccountsManager *manager){
	count(manager);
		
	cout << "Destination: ";
	cout << manager->get_destination() << endl;
}

void count(AccountsManager *manager){
	cout << "Found clients: ";
	cout << manager->count() << endl;
}

void get_equals(AccountsManager *manager){
	vector<string> users = manager->find_equals();
	if (users.empty()){
		cout << "Empty" << endl;
		return;
	}
	
	for(int i = 0; i < users.size(); i++){
		cout << users[i] << endl;
	}
	cout << endl <<"Do you want to save this info in file? ('y' - to save) ";
	string ch = "";
	getline(cin, ch);
	if(ch == "y"){
		ofstream f;
		f.open("accounts.txt", ios::out);
		for(int i = 0; i < users.size(); i++){
			f << users[i] << endl;
		}
		cout << "Success.";
	}
}

void more_two(AccountsManager *manager){
	vector<string> names = manager->find_accounts();
	if (names.empty()){
		cout << "Empty" << endl;
		return;
	}
	sort( names.begin(), names.end());
	for(int i = 0; i < names.size(); i++){
		cout << names[i] << endl;
	}
}


void edit_client_menu(Account *user){
	cout << "Is client editing menu.";
	string command = "";
	while(true){
		fflush(stdin);
		cout << endl <<"command > ";
		getline(cin, command);
		if(command == "main") {
			break;
			return;
		}
		else if(command == "help"){
			cout << "'main' - to back in main menu" <<endl;
			cout << "'clear' - Clear console." << endl;
			cout << "'name' - edit name" << endl;
			cout << "'info' - info about this user" << endl;
			cout << "'add_input' - add input transaction" << endl;
			cout << "'add_output' - add input transaction" << endl;
			cout << "'see_operations' - see all transactions" << endl;
			cout << "'get_destination' - destination summ" << endl;
			
		}
		else if(command == "clear"){
			system("cls");
			edit_client_menu(user);
		}
		else if(command == "name"){
			cout << "New fullname: ";
			string name = "";
			getline(cin, name);
			user->setName(name);
			cout << "Success" << endl;
		}
		else if(command == "info"){
			cout  << endl << "Fullname: " + user->getName() << endl;
			cout << "Balance: ";
			cout << user->getBalance() << endl;
			user->printOperations();
		}
		else if(command == "add_input"){
			TransactionManager *tmanager = user->getTmanager();
			cout << "Enter input sum: ";
			double m;
			cin >> m;
			fflush(stdin);
			tmanager->addInputTransaction((double)m);
			double balance = user->getBalance();
			double result = balance + (double)m;
			user->setMoney(result);
			tmanager->print_operation();
		}
		else if(command == "add_output"){
			TransactionManager *tmanager = user->getTmanager();
			cout << "Enter output sum: ";
			double m;
			cin >> m;
			fflush(stdin);
			double balance = user->getBalance();
			if ((double)balance > (double)m){
				tmanager->addOutputTransaction(m);
				double result = balance - m;
				user->setMoney(result);
			}else{
				cout << "enough money" << endl;
			}
			tmanager->print_operation();
		}
		else if(command == "see_operations"){
			TransactionManager *tmanager = user->getTmanager();
			tmanager->print_transactions();
		}
		else if(command == "get_destination"){
			TransactionManager *tmanager = user->getTmanager();
			cout << tmanager->getDistinction() << endl;
		}
		
		else{
			cout << "Invalid command." << endl << endl;
		}
	}
}


void edit_client(AccountsManager *manager){
	cout << "Enter user ID: ";
	string id = "";
	getline(cin, id);
	
	if (manager->isExist(id)){
		Account *user = manager->getAccount(id);

		cout  << endl << "Fullname: " + user->getName() << endl;
		cout << "Balance: ";
		cout << user->getBalance() << endl;
		user->printOperations();
		
		cout << "Do you want edit this user? ('y' to edit)" << endl;
		string ch = "";
		getline(cin, ch);
		if(ch == "y"){
			edit_client_menu(user);
		}else{
			return;
		}
	}else{
		cout << "Not found this ID. Try again..." << endl;
		edit_client(manager);
	}

}

void printHelp(){
	cout << "'exit' - Exit." << endl;
	cout << "'clear' - Clear console." << endl;
	cout << "'install_demo' - Intall demo users from the bank." << endl;
	cout << "'print_clients' - Printing all clients on the bank." << endl;
	cout << "'remove_client' - remove client by ID" << endl;
	cout << "'edit_client' - edit client by ID" << endl;
	cout << "'see_more_acc' - sorted names are more than two accounts" << endl;
	cout << "'count_clients' - print count client" << endl;
	cout << "'get_destination' - destination summ of all bank" << endl;
	cout << "'get_equals' - see accounts where input quals output summ" << endl;
	cout << "'save' - save all in XML" << endl;
	
	
}

void save(AccountsManager *manager){
	if(manager->count() == 0){
		cout << "not saved. none clients" << endl;
	}else{
		manager->save_to_XML();
		cout << "saved." << endl;
	}
}

void installDemoUsers(AccountsManager *manager){
	manager->addClient("Anton Ivanov",255.12);
	manager->addClient("Petr Petrov",45.55);
	manager->addClient("Ivan Petrov",88.55);
	manager->addClient("Ivailo Ivanov",125.12);
	manager->addClient("Ivailo Antonov",122.12);
	manager->addClient("Vasil Ivanov",25.12);
	manager->addClient("Nikola Ivanov",5.12);
	manager->addClient("Yaskov Ivailov",2.12);
	manager->addClient("Anton Ivanov",25.12);
	manager->addClient("Ivailo Ivanov",1205.12);
	manager->addClient("Yaskov Ivailov",2.12);
	cout << "Success."<<endl;

	
}

void print_clients(AccountsManager *manager){
	manager->print_accounts();
}

void add_client(AccountsManager *manager){
	string name = "";
	double money = 0.0;
	
	cout << "Please enter client fullname." << endl;
	getline(cin, name);
	if(name != ""){
		cout << "Please enter client money balance." << endl;
		cin >> money;
		manager->addClient(name,money);
		cout << "Success."<<endl;
	}else{
		cout << "Input value error." << endl;
	}
}


void remove_client(AccountsManager *manager){
	string id = "";
	
	cout << "Please enter client ID." << endl;
	getline(cin, id);
	if(id != ""){
		manager->remove(id);
		cout << "Was deleted" << endl;
	}else{
		cout << "Input value error." << endl;
	}
}


