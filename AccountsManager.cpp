#include "AccountsManager.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/* to string path*/
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

/* end path */



/* Constructors */
AccountsManager::AccountsManager(string id, string fullName, double money){
    _pHead = new Account(id, fullName, money);
    _pTail = _pHead;
}

AccountsManager::AccountsManager(){
    _pHead = NULL;
    _pTail = _pHead;
}

/* End constructors */


/* Destructor */
AccountsManager::~AccountsManager()
{
}

/* End destructor */


/* Add element */
void AccountsManager::addClient(string fullName, double money){
	string id = idGenerator();
    if (_pHead == NULL) {
        _pTail = _pHead = new Account(id, fullName, money);
    }
    else
    {
        _pTail->_pNext = new Account(id, fullName, money);
        _pTail = _pTail->_pNext;
    }
    cout << "id: " << id <<endl;
    cout << "Full Name: " << fullName << endl;
    cout << "Money Balance: " << money << endl;
    cout << "Was created..." << endl << endl;
    
}

/*  End function */


/* Remove element */
void AccountsManager::remove(string id){
	Account *pPre = NULL, *pDel = NULL;
    
    if (_pHead->_id == id) {
        pDel = _pHead;
        _pHead = pDel->_pNext;
        delete pDel;
        return;
    }
    
    pPre = _pHead;
    pDel = _pHead->_pNext;
    
    while (pDel != NULL) {
        if (pDel->_id == id) {
            pPre->_pNext = pDel->_pNext;
            if (pDel == _pTail) {
                _pTail = pPre;
            }
            cout << "Was deleted" << endl;
            delete pDel; 
            break; 
        }
        pPre = pDel;
        pDel = pDel->_pNext;
    }
}

/*  End function */


/* Print */
void AccountsManager::print_accounts(){
	Account *p = _pHead;
    
    if (_pHead == NULL) {
		cout << "The bank is empty!" << endl;
        return;
    }
    
    cout << "The bank clients: " << endl << endl;
    

    while (p != NULL) { 
    	cout << "id: " + p->_id << endl;
        cout << "Full Name: " + p->_fullName << endl;
        cout << "Money balance: ";
		cout << p->_money << endl;
		p->printOperations();
		cout  << endl << endl;
        p = p->_pNext;
    }
    
}

/*  End function */

/* get Account from id */
Account* AccountsManager::getAccount(string id){
	Account *pNext = NULL;
    pNext = _pHead;

    while (pNext != NULL) {
        if (pNext->_id == id) {
            return pNext;
            break; 
        }
        pNext = pNext->_pNext;
    }
}
/* End Funktion */


/* get Account from id */
bool AccountsManager::isExist(string id){
	Account *pNext = NULL;
    pNext = _pHead;

    while (pNext != NULL) {
        if (pNext->_id == id) {
            return true;
            break; 
        }
        pNext = pNext->_pNext;
    }
    return false;
}
/* End Funktion */

/* id generator fumction */
string AccountsManager::idGenerator(){
	if(idNum < 10000){
		idNum = 99999;
		idLetter = static_cast<char>(idLetter + 1);
	}else{
		idNum -= 1;
	}
	
	return patch::to_string(idLetter) + patch::to_string(idNum);
}
/* End function */
