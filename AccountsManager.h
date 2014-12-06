#include "Account.h"


class AccountsManager
{
private:
    Account *_pHead;
    Account *_pTail;
	char idLetter = 'a';
	int idNum = 100000;
	/* id generator */
    string idGenerator();
    
public:
    /* Constructors */
    AccountsManager(string id, string fullName, double money);
    AccountsManager();
    /* Destructor */
    ~AccountsManager(void);
    
    /* Function to append */
    void addClient(string fullName, double money);
    
    /* Remove a clients with a specific value if it exists */
    void remove(string id);
    
    
    
    /* see all */
    void print_accounts();
};