#include <string>
#include <iostream>
#include "TransactionManager.h"

using namespace std;


class Account
{
    friend class AccountsManager;
private:
	string _id;
    string _fullName;
    double _money;
    TransactionManager *tmanager;
    Account *_pNext; 
    
public:
    /* Constructors with No Arguments */
    Account(void)
    : _pNext(NULL)
    {
		tmanager = new TransactionManager(0);
	}
    
    /* Constructors with a given value */
    Account(string id, string fullName, double money)
    : _id(id), _fullName(fullName), _money(money), _pNext(NULL)
    {
		tmanager = new TransactionManager(money);
	}
    
    /* Constructors with a given value and a link of the next node */
    Account(string id, string fullName, double money, Account* next)
    :  _id(id), _fullName(fullName), _money(money), _pNext(next)
    {
		tmanager = new TransactionManager(money);
	}
    
    /* Getters */
    Account* getNext(void)
    { return _pNext; }
    
    string getId(void)
    { 
		return _id;
	}
    
    string getName(void)
    { 
		return _fullName;
	}
	
	double getBalance(void)
    { 
		return _money;
	}
	
	TransactionManager* getTmanager(){
		return tmanager;
	}
    
    /* Seters */
    void setName(string name)
    { 
		_fullName = name;
	}
	
	void setMoney(double &money)
    { 
		_money = money;
	}
	
	void setTmanager(TransactionManager* tm){
		tmanager = tm;
	}
    
    /* Functions */
	void printOperations(void)
    { 
		tmanager->print_operation();
	}
    
};
