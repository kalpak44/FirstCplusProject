#include <iostream>
#include "AccountsManager.h"
#include <string>
#include <stdlib.h>


void userInterface(AccountsManager *manager);
void installDemoUsers(AccountsManager *manager);
void printHelp();
void print_all_clients(AccountsManager *manager);
void add_client(AccountsManager *manager);
void remove_client(AccountsManager *manager);
void edit_client(AccountsManager *manager);

int main(int argc, char** argv) {
	/*
	TransactionManager *opert = new TransactionManager(0);
	opert->addInputTransaction(12.45);
	opert->addOutputTransaction(2.45);
	opert->print_operation();
	*/
	
	AccountsManager *manager = new AccountsManager();
	installDemoUsers(manager);
    userInterface(manager);
	return 0;
	
}


















void userInterface(AccountsManager *manager){
	string command = "";
	while(true){
		cout << endl <<"Please enter your command." << endl;
		getline(cin, command);
		if(command == "exit") {
			break;
		}
		else if(command == "help"){
			printHelp();
		}
		else if(command == "clear"){
			system("cls");
		}
		else if(command == "install_demo"){
			installDemoUsers(manager);
		}
		else if(command == "print_all_clients"){
			print_all_clients(manager);
		}
		else if(command == "add_client"){
			add_client(manager);
		}
		else if(command == "remove_client"){
			remove_client(manager);
		}
		else if(command == "get_client"){
			edit_client(manager);
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
		Account user = manager->getAccount(id);

		cout  << endl << "Fullname: " + user.getName() << endl;
		cout << "Balance: ";
		cout << user.getBalance() << endl << endl;
		user.printOperations();
		cout << "Do you want edit this user? (y/n) ";
		return;
	}else{
		cout << "Not found this ID. Try again..." << endl;
		edit_client(manager);
	}

}

void printHelp(){
	cout << "'exit' - Exit." << endl;
	cout << "'clear' - Clear console." << endl;
	cout << "'install_demo' - Intall demo users from the bank." << endl;
	cout << "'print_all_clients' - Printing all clients on the bank." << endl;
	cout << "'remove_client' - remove client by ID" << endl;
}

void installDemoUsers(AccountsManager *manager){
	manager->addClient("Petr Petrov",45.55);
	manager->addClient("Ivan Petrov",88.55);
	manager->addClient("Ivailo Ivanov",125.12);
}

void print_all_clients(AccountsManager *manager){
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
	}else{
		cout << "Input value error." << endl;
	}
}


