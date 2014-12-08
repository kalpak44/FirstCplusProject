#include <string>

using namespace std;


class Transaction
{
    friend class TransactionManager;
private:
    string _type;
    double _money;
    Transaction *_pNext; 
    
public:
    /* Constructors with No Arguments */
    Transaction(void)
    : _pNext(NULL)
    { }
    
    /* Constructors with a given value */
    Transaction(string _type, double money)
    :_type(_type), _money(money), _pNext(NULL)
    { }
    
    /* Constructors with a given value and a link of the next node */
    Transaction(string _type, double money, Transaction* next)
    : _type(_type), _money(money), _pNext(next)
    {}
    
    /* Getters */
    string getType(void)
    { return _type; }
    
    double getMoneyBalance(void)
    { return _money; }
    
    Transaction* getNext(void)
    { return _pNext; }
};
