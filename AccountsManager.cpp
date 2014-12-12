#include "AccountsManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include<set>
#include "Markup.h"

using namespace std;
string SAVE_FILE = "Sample.xml";


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
}

void AccountsManager::addClient(Account *account){

    if (_pHead == NULL) {
        _pTail = _pHead = account;
    }
    else
    {
        _pTail->_pNext = account;
        _pTail = _pTail->_pNext;
    }
}

/*  End functions */


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
            delete pDel; 
            break; 
        }
        pPre = pDel;
        pDel = pDel->_pNext;
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

/* Names who are more at two accounts */
vector<string> AccountsManager::find_accounts(){
	vector <string> names;

	Account *p = _pHead;
    Account *n = _pHead;
    
    if (_pHead == NULL) {
        return names;
    }
    
	set<string> setNames;
	
    while (p != NULL) { 
        string name =  p->_fullName;
        if(setNames.find(name) != setNames.end()){
    		names.push_back(name);
    	}else{
    		setNames.insert(name);
    	}
       	
        p = p->_pNext;
    }
    return names;

}

/* End Function */

/* Get count accounts*/
int AccountsManager::count(){
	Account *p = _pHead;
    
    if (_pHead == NULL) {
        return 0;
    }
    
	int i = 0;
    while (p != NULL) {
    	i++;
        p = p->_pNext;
    }
    return i;
}
/* End Function */

/* get all sum destination */
double AccountsManager::get_destination(){
	Account *p = _pHead;
    
    if (_pHead == NULL) {
        return 0;
    }
    
	double input_summ = 0;
	double output_summ = 0;
	
    while (p != NULL) {
    	input_summ += p->tmanager->getInput();
    	output_summ += p->tmanager->getOutput();
        p = p->_pNext;
    }
    
    
    return input_summ - output_summ;
}
/* End Function */


/*names and summ where inputs equals outputs sum*/
vector<string> AccountsManager::find_equals(){
	vector <string> eq_infos;
	Account *p = _pHead;
    
    if (_pHead == NULL) {
        return eq_infos;
    }
    
    while (p != NULL) {
    	double in = p->getTmanager()->getInput();
    	double out = p->getTmanager()->getOutput();
    	if (out == in){
    		string r_struct = p->getId() + " ";
			r_struct += p->getName() + " ";
    		r_struct += patch::to_string(p->getBalance());
    		eq_infos.push_back(r_struct);
    	}
        p = p->_pNext;
    }
    
    
    return eq_infos;
}
/* End Function */


/* Save at XML file*/
void AccountsManager::save_to_XML(){
	Account *p = _pHead;
    
    if (_pHead == NULL) {
        return;
    }
	
	CMarkup xml;
	xml.AddElem("ORDER");
	xml.IntoElem();
	
    while (p != NULL) {
    	xml.AddElem("CLIENT");
    	xml.IntoElem();
    	xml.AddElem("ID",p->getId());
    	xml.AddElem("NAMES",p->getName());
    	xml.AddElem("BALANCE",patch::to_string(p->getBalance()));
    	
		xml.AddElem("TRANSACTIONS");
		xml.IntoElem();
    	
    	
    	int transact_count = p->getTmanager()->inputNumTransactions();
    	transact_count += p->getTmanager()->outputNumTransactions();
    	if (transact_count < 0){
    		transact_count = 0;
    	}

    	for(int i = 0; i < transact_count; i++){
    		Transaction *tr = p->getTmanager()->getTransactions(i);
    		xml.AddElem( tr->getType(),patch::to_string(tr->getMoneyBalance()));
    	}
    	
    	xml.OutOfElem();
    	xml.OutOfElem();
        p = p->_pNext;
    }
	xml.Save(SAVE_FILE);
}

/* End Function */

/* Load from XML file*/
AccountsManager* AccountsManager::load_XML(){
	AccountsManager *acc_manager = new AccountsManager();
	CMarkup xml;
	xml.Load(SAVE_FILE);
	xml.FindElem();
	xml.IntoElem();
	while (xml.FindElem("CLIENT")){
		
		xml.IntoElem();
		xml.FindElem("ID");
	    MCD_STR id = xml.GetData();
	    
	    xml.FindElem("NAMES");
	    MCD_STR name = xml.GetData();
	    
	    Account *account = new Account(id, name, 0);
	    
	    xml.FindElem("BALANCE");
	    MCD_STR str_balance = xml.GetData();
	    double d_balance = atof(str_balance.c_str());
	    
	   xml.FindElem("TRANSACTIONS");
	   xml.IntoElem();
	   TransactionManager *tr_manager = new TransactionManager(0);
	    while(xml.FindElem("IN")){
	    	
			MCD_STR in = xml.GetData();
			double d_in = atof(in.c_str());
	    	tr_manager->addInputTransaction(d_in);
	    }
	    while(xml.FindElem("OUT")){
	    	
			MCD_STR out = xml.GetData();
			double d_out = atof(out.c_str());
	    	tr_manager->addOutputTransaction(d_out);
	    }
	    account->setTmanager(tr_manager);
	    account->setMoney(d_balance);
		acc_manager->addClient(account);
	    xml.OutOfElem();
	    xml.OutOfElem();
	    
	}
	return acc_manager;
}
/* End Function */

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
        cout << "Money balance: " + patch::to_string(p->getBalance()) << endl;
		p->printOperations();
        p = p->_pNext;
    }
    
}

/*  End function */
