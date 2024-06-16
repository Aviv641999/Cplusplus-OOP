#include "Transaction.h"

// CTOR
Transaction::Transaction( Account* s, Account* d, double amount, const char* date )
    : m_date(nullptr) {
    SetSource(s);
    SetDes(d);
    SetAmount(amount);
    SetDate(date);
}
// CCTOR
Transaction::Transaction( const Transaction &other )
    : m_date(nullptr) {
    SetSource( other.m_source );
	SetDes( other.m_destination );
	SetAmount( other.m_amount );
	SetDate( other.m_date );
}

// Methods
void Transaction::SetSource( Account* src ){
    m_source = src;
}
void Transaction::SetDes( Account* dst ){
    m_destination = dst;
}
void Transaction::SetAmount( double amount ){
    m_amount = amount;
}
void Transaction::SetDate( const char* date ){
    if (m_date)
        delete m_date;
    if (date)
        m_date = strdup(date);
}
Account* Transaction::GetSource() const{
    return m_source;
}
Account* Transaction::GetDes() const{
    return m_destination;
}
double Transaction::GetAmount() const{
    return m_amount;
}
char* Transaction::GetDate() const{
    return m_date;
}


