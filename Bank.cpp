#include "Bank.h"

// Functions Prototype
int getAccountInAccountList(const Account &account, Account** accountsList, int numbeOfAccounts);

// CTOR
Bank::Bank()
:   m_name(nullptr), 
    m_account(nullptr), 
    m_bankCode(0),
    m_numbeOfAccounts(0), 
    m_totalBalance(0){}
// CTOR
Bank::Bank( const char* name, int code )
    :   m_bankCode(code), 
        m_account(nullptr),
        m_numbeOfAccounts(0), 
        m_totalBalance(0),
        m_name(nullptr)
{
    SetBankName(name);
}
// DTOR
Bank::~Bank(){
    if (m_name)
        delete[]m_name;
    for( int i = 0; i < m_numbeOfAccounts; i++ )
		delete m_account[i];

	delete[] m_account;
}

// Methods
// Gets Sets
void Bank::SetBankName( const char* name ){
    if (m_name)
        delete m_name;
    m_name = strdup(name);
}
void Bank::SetAccount( Account** account, int numbeOfAccounts )
{
    for( int i = 0; i < m_numbeOfAccounts; i++ )
		delete m_account[i];

	delete[] m_account;

	m_totalBalance = 0;
    m_numbeOfAccounts = numbeOfAccounts;
    m_account = account;

    for (int i = 0; i < m_numbeOfAccounts; i++ ) {
        m_totalBalance += m_account[i]->GetBalance();
    }
}
void Bank::SetTotal( double total ){
    m_totalBalance = total;
}
void Bank::SetCode( int code ){
    m_bankCode = code;
}
const char* Bank::GetBankName() const{
    return m_name;
}
Account** Bank::GetAccounts() const{
    return m_account;    
}
int Bank::GetNumberOfAccounts() const{
    return m_numbeOfAccounts;    
}
double Bank::GetTotal() const{
    return m_totalBalance;    
}
int Bank::GetCode() const{
    return m_bankCode;    
}

// More methods
void Bank::AddAccount( const Account& account ){
    
    if (getAccountInAccountList(account, m_account, m_numbeOfAccounts) != -1){
        cout << "INFO: Bank::AddAccount " << account.GetAccountNumber() <<  " Returned immediatelly  " << endl;
        return;
    }
    if (m_numbeOfAccounts == 0)
    {
        cout << "INFO: Bank::AddAccount " << account.GetAccountNumber() << " m_numbeOfAccounts == 0" << endl;
        m_account = new Account*[1];
        m_account[0] = new Account(account);
    }
    else
    {
        cout << "INFO: Bank::AddAccount " << account.GetAccountNumber() << " Copy existing accounts" << endl;
        Account** newAccountList = new Account*[m_numbeOfAccounts+1];
        // Copy existing accounts
        for (int i = 0; i < m_numbeOfAccounts; ++i) {
            newAccountList[i] = m_account[i];
        }
        // Add the new account
        newAccountList[m_numbeOfAccounts] = new Account(account);
        // Delete old accounts list and update
        delete[] m_account;
        m_account = newAccountList;
        
    }
    m_numbeOfAccounts++;
    m_totalBalance += account.GetBalance();
}
void Bank::AddAccount( const Person& per, double amount ){
    // Create account for person
    Account account(per, amount);
    // Add account to bank
    AddAccount(account);
}
void Bank::AddPerson( const Person& newPerson, const Account& account, double amount ){
    // Sets bools for conditions
    int isAccountInBank = getAccountInAccountList(account, m_account, m_numbeOfAccounts);
    bool isPersonInAccount = false;

    Person** personsList = account.GetPersons();
    for (int i = 0; i < account.GetTotalPersons(), i++;){
        if (personsList[i]->GetId() == newPerson.GetId())
            isPersonInAccount = true;
    }

    if (isAccountInBank && isPersonInAccount)
        return;
    if (!(isAccountInBank)){
        // Create new account and add to bank
        AddAccount(newPerson, amount);
        return;
    }
    // Account in bank without person
    // Find acccount in bank
    m_account[isAccountInBank]->AddPerson(newPerson,amount);
    m_totalBalance += amount;
}
void Bank::DeleteAccount( const Account& account ){
    int indexAccountInBank = getAccountInAccountList(account, m_account, m_numbeOfAccounts);
    // Account not in bank
    if (!(indexAccountInBank))
    {
        return;
    }

    m_totalBalance -= m_account[indexAccountInBank]->GetBalance();

    // If account the only one in bank
    if (indexAccountInBank && m_numbeOfAccounts == 1)
    {
        delete m_account[0];
        delete[] m_account;
        m_account = nullptr;
        return;
    }
    // Account in the list and not alone
    Account** newAccountsList = new Account*[m_numbeOfAccounts-1];
    // Copy existing accounts without old person
    int newIndex = 0;
    for( int i = 0; i < m_numbeOfAccounts; ++i )
	{
        if( i != indexAccountInBank )
        {
            newAccountsList[newIndex] = m_account[i];
            newIndex++;
        }
	}
    // Delete old accounts list and update
    delete m_account[indexAccountInBank];
    delete[] m_account;
    m_account = newAccountsList;
    m_numbeOfAccounts--;   
}
void Bank::DeletePerson( const Person& p ){

    int i = 0; 
    // For every account delete person
    while (i < m_numbeOfAccounts)
    {
        m_account[i]->DeletePerson(p);
        // Last person in account
        if (m_account[i]->GetPersons() == 0){
            DeleteAccount(*m_account[i]);
        }
        else 
        {
            i++;
        }
    }
    
}


int getAccountInAccountList(const Account &account, Account** accountsList, int numbeOfAccounts){
    for (int i = 0; i < numbeOfAccounts, i++;){
        if (accountsList[i]->GetAccountNumber() == account.GetAccountNumber())
            return i;
    }
    return -1;
}
