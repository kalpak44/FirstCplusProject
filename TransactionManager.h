#include "Transaction.h"


class TransactionManager
{
private:
    Transaction *_pHead;
    Transaction *_pTail;
    double _money;
    
public:
    /* Constructor */
    TransactionManager(double money);
    /* Destructor */
    ~TransactionManager(void);
    
    /* Functions*/
    void addInputTransaction(double money);
    int inputNumTransactions();
    void addOutputTransaction(double money);
    int outputNumTransactions();
	double getDistinction(void);
    
    /* see all */
    void print_transactions(void);
    void print_operation(void);
    
};
