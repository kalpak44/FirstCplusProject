#include "TransactionManager.h"
#include <iostream>
#include <string>

const string outputTypeOperation = "OUT";
const string inputTypeOperation = "IN";

/* Constructor */
TransactionManager::TransactionManager(double money){
    _pHead = NULL;
    _pTail = _pHead;
    _money = money;
}

/* End constructors */


/* Destructor */
TransactionManager::~TransactionManager()
{
}

/* End Destructor */



/* Functions */
void TransactionManager::addInputTransaction(double money){
    if (_pHead == NULL) {
        _pTail = _pHead = new Transaction(inputTypeOperation, money);
    }
    else
    {
        _pTail->_pNext = new Transaction(inputTypeOperation, money);
        _pTail = _pTail->_pNext;
    }
}

void TransactionManager::addOutputTransaction(double money){
    if (_pHead == NULL) {
        _pTail = _pHead = new Transaction(outputTypeOperation, money);
    }
    else
    {
        _pTail->_pNext = new Transaction(outputTypeOperation, money);
        _pTail = _pTail->_pNext;
    }
}

double TransactionManager::getInput(void){
	Transaction *p = _pHead;
    
    if (_pHead == NULL) {
        return 0;
    }
    double summ = 0;
    while (p != NULL) {
    	if(p->_type == inputTypeOperation){
    		summ = summ + p->getMoneyBalance();
    	}
    	p = p->_pNext;
    }
    return summ;
}

double TransactionManager::getOutput(void){
	Transaction *p = _pHead;
    
    if (_pHead == NULL) {
        return 0;
    }
    double summ = 0;
    while (p != NULL) {
    	if(p->_type == outputTypeOperation){
    		summ = summ + p->getMoneyBalance();
    	}
    	p = p->_pNext;
    }
    return summ;
}

double TransactionManager::getDistinction(void){
	Transaction *p = _pHead;
    
    if (_pHead == NULL) {
        return 0;
    }
    double distinction = 0;
    while (p != NULL) {
    	if(p->_type == inputTypeOperation){
    		distinction = distinction + p->getMoneyBalance();
    	}
		if(p->_type == outputTypeOperation){
    		distinction = distinction - p->getMoneyBalance();
    	}
    	p = p->_pNext;
    }
    return distinction;
}

int TransactionManager::inputNumTransactions(void){
	Transaction *p = _pHead;
    
    if (_pHead == NULL) {
        return 0;
    }
    int inputNum = 0;
    
    while (p != NULL) {
		if(p->_type == inputTypeOperation){
    		inputNum += 1;
    	}
    	p = p->_pNext;
    }
    return inputNum;
}

int TransactionManager::outputNumTransactions(void){
	Transaction *p = _pHead;
    
    if (_pHead == NULL) {
        return 0;
    }
    int outputNum = 0;
    
    while (p != NULL) {
		if(p->_type == outputTypeOperation){
    		outputNum += 1;
    	}
    	p = p->_pNext;
    }
    return outputNum;
}

void TransactionManager::print_operation(void){
	cout << "Operations: " << endl;
    cout << inputTypeOperation + ": ";
    cout << +inputNumTransactions();
    cout << "   " + outputTypeOperation + ": ";
    cout << +outputNumTransactions() << endl << endl;
}

void TransactionManager::print_transactions(void){
	Transaction *p = _pHead;
    
    if (_pHead == NULL) {
		cout << "None operations!" << endl;
        return;
    }
    
    cout << "Primary balance: ";
    cout << _money << endl;
    cout << "Destination balance: ";
    cout << getDistinction() << endl << endl;
    
    cout << "Details: " << endl << endl;
    while (p != NULL) { 
        cout << "Type: " + p->_type << endl;
        cout << "Money transacted: ";
		cout << p->_money << endl <<endl;
        p = p->_pNext;
    }
}
