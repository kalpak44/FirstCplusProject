#include "Account.h"
#include <vector>

class AccountsManager
{
private:
    Account *_pHead;
    Account *_pTail;
	char idLetter = 'a';
	int idNum = 100000;
    void appendAccount(AccountsManager *manager, string id,string fullName, double money, TransactionManager *tmanager);
public:
    /* Constructors */
    AccountsManager(string id, string fullName, double money);
    AccountsManager();
    /* Destructor */
    ~AccountsManager(void);
    
    /* Function to append */
    void addClient(string fullName, double money);
    void addClient(Account *account);
    
    
    /* Remove a clients with a specific value if it exists */
    void remove(string id);
    
    /* get Account from id */
    Account* getAccount(string id);
    
    /* checking existiing in list */
    bool isExist(string id);
    
    /* see all */
    void print_accounts();
    
    /* count account */
    int count();
    
	/* get all destination transactions  */
	double get_destination();
    
    /*find names who names are more two accounts*/
    std::vector<string> find_accounts();
    
	/*names and summ where inputs equals outputs sum*/
    std::vector<string> find_equals();
    
    /* save to XML */
    void save_to_XML();
    
    /* load from XML */
    AccountsManager* load_XML();
    
};
