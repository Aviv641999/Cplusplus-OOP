#include "Account.h"

// Functions Prototype
bool isPersonInAccount(const Person &person, Person** persons, int personsNum);

// Default CTOR
Account::Account()
    :   m_transactionList(nullptr), 
        m_numberOfTransaction(0), 
        m_persons(nullptr),
        m_totalPersons(0), 
        m_accountNumber(0), 
        m_balance(0.0) {}
// CTOR
Account::Account( Person** persons, int count, double balance )
    :   m_transactionList(nullptr), 
        m_numberOfTransaction(0), 
        m_persons(nullptr),
        m_totalPersons(count), 
        m_accountNumber(0), 
        m_balance(balance) 
{
    SetPersons(persons, count);
    for (int i = 0; i < m_totalPersons; i++ ) {
        m_accountNumber += persons[i]->GetId();
    }
}
// CTOR
Account::Account( const Person& person, double balance )
    :   m_persons(nullptr), 
        m_totalPersons(1), 
        m_balance(balance),
        m_transactionList(nullptr), 
        m_numberOfTransaction(0),
        m_accountNumber(person.GetId())
{
    m_persons = new Person*[1];
	m_persons[0] = new Person( person );
}
// CCTOR
Account::Account( const Account& other ) 
    :   m_numberOfTransaction(other.m_numberOfTransaction), 
        m_accountNumber(other.m_accountNumber),
        m_balance(other.m_balance), 
        m_totalPersons(other.m_totalPersons),
        m_persons(nullptr), 
        m_transactionList(nullptr)
{
    SetPersons(other.m_persons, other.m_totalPersons);
    SetTransactions(other.m_transactionList,other.m_numberOfTransaction);
}
// DTOR
Account::~Account() 
{
    clearTransactions();
    clearPersons();
}

// Methods
// Gets Sets
void Account::SetPersons( Person** persons, int count )
{
    clearPersons();

    m_totalPersons = count;
    m_persons = new Person*[m_totalPersons];

    for (int i = 0; i < count; i++ ) {
        m_persons[i] = new Person(*persons[i]);
    }
}
void Account::SetAccountNumber( int number ){
    m_accountNumber = number;
}
void Account::SetBalance( double balance ){
    m_balance = balance;
}
void Account::SetTransactions( Transaction** newTransaction, int count ) 
{
    
    clearTransactions();

    m_numberOfTransaction = count;

    if (m_numberOfTransaction > 0) {
        m_transactionList = new Transaction*[count];
        for (int i = 0; i < m_numberOfTransaction; ++i) {
            m_transactionList[i] = new Transaction(*newTransaction[i]);
        }
    }
}
Transaction** Account::GetTransactions(){
    return m_transactionList;
}
int	Account::GetNumOfTransactions(){
    return m_numberOfTransaction;
}
Person** Account::GetPersons() const{
    return m_persons;
}
int	Account::GetTotalPersons()const{
    return m_totalPersons;
}
int Account::GetAccountNumber() const {
    return m_accountNumber;
}
double Account::GetBalance() const{
    return m_balance;
}

// More methods
void Account::Withdraw( double amount, const char* date )
{
    AddTransaction(Transaction(this,this, -amount, date));
}
void Account::Deposit( double amount, const char* date )
{
    AddTransaction(Transaction(this,this, amount, date));
}
void Account::AddPerson( const Person& newPerson, double amount ){
    
    // If person not in account
    if (isPersonInAccount(newPerson, m_persons, m_totalPersons)){
        return;
    }
    if (m_totalPersons == 0 && m_persons == nullptr)
    {
        m_persons = new Person*[1];
		m_persons[0] = new Person( newPerson );
    }
    else
    {
        // Update list with new person
        Person** newPersonsList = new Person*[m_totalPersons+1];
        // Copy existing persons
        for (int i = 0; i < m_totalPersons; ++i) {
            newPersonsList[i] = m_persons[i];
        }
        // Add the new person
        newPersonsList[m_totalPersons] = new Person(newPerson);
        // Delete old persons list and update
        delete[] m_persons;
        m_persons = newPersonsList;
    }
    m_totalPersons++;
    m_balance += amount;
    
}
void Account::DeletePerson( const Person& oldPerson ){

    bool isPersonInList = isPersonInAccount(oldPerson, m_persons, m_totalPersons);
    if (!(isPersonInList)){
        return;
    }
    // If person the only one in account
    if (m_totalPersons == 1){
        delete m_persons[0];
        delete[] m_persons;
        m_totalPersons--;
        m_persons = nullptr;
        return;
    }
    // Person in the list and not alone
    Person** newPersonsList = new Person*[m_totalPersons-1];

    int index; // Index for person to delete
	for( int i = 0; i < m_totalPersons; ++i )
	{
		if( m_persons[i]->GetId() == oldPerson.GetId() )
		{
			index = i;
			break;
		}
	}
    int k = 0; // New index for new persons list
    // Copy existing persons without old person
    for (int i = 0; i < m_totalPersons; ++i) {
        if ( i != index)
        {
            newPersonsList[k] = m_persons[i];
            k++;
        }
    }
    // Delete old persons list and update
    delete m_persons[index];
    delete[] m_persons;
    m_persons = newPersonsList;
    m_totalPersons--;
            
    
}
void Account::AddTransaction( const Transaction& newTransaction )
{
    Account* src = newTransaction.GetSource();
	Account* dst = newTransaction.GetDes();

    if (src != nullptr)
    {  
        if (src->m_transactionList == nullptr)
        {
            src->m_transactionList = new Transaction*[1];
            src->m_transactionList[0] = new Transaction(newTransaction);
            src->m_numberOfTransaction++;
        }
        else
        {
            Transaction** newTransactionList = new Transaction*[src->m_numberOfTransaction+1];
            for (int i = 0; i < src->m_numberOfTransaction; i++)
            {
                newTransactionList[i] = src->m_transactionList[i];
            }
            newTransactionList[src->m_numberOfTransaction] = new Transaction(newTransaction);
            delete[] src->m_transactionList;

			src->m_transactionList = newTransactionList;
			++src->m_numberOfTransaction;
            
        }
        if (src == dst)
        {
            src->m_balance += newTransaction.GetAmount();
            return;
        }
        else 
        {
            src->m_balance -= newTransaction.GetAmount();
        }
    }

    if (dst != nullptr)
    {
        if (dst->m_transactionList == nullptr)
        {
            dst->m_transactionList = new Transaction*[1];
            dst->m_transactionList[0] = new Transaction(newTransaction);
            dst->m_numberOfTransaction++;
        }
        else
        {
            Transaction** newTransactionList = new Transaction*[dst->m_numberOfTransaction+1];
            for (int i = 0; i < dst->m_numberOfTransaction; i++)
            {
                newTransactionList[i] = dst->m_transactionList[i];
            }
            newTransactionList[dst->m_numberOfTransaction] = new Transaction(newTransaction);
            delete[] dst->m_transactionList;

			dst->m_transactionList = newTransactionList;
			++dst->m_numberOfTransaction;
            
        }
        dst->m_balance += newTransaction.GetAmount();
    }
    
}

void Account::clearTransactions()
{
    if (m_transactionList){
        for (int i = 0; i < m_numberOfTransaction; ++i) {
            delete m_transactionList[i];
        }
        delete[] m_transactionList;
        m_transactionList = nullptr;
    }
}
void Account::clearPersons(){
    if (m_persons){
        for (int i = 0; i < m_totalPersons; ++i) {
            delete m_persons[i];
        }
        delete[] m_persons;
        m_persons = nullptr;
    }
}

// Check if person is in the list
bool isPersonInAccount(const Person &person, Person** persons, int personsNum){
    for (int i = 0; i < personsNum, i++;){
        if (persons[i]->GetId() == person.GetId())
            return true;
    }
    return false;
}