#include "Person.h"
#include <iostream>
using namespace std;

// Default CTOR
Person::Person(): m_name(nullptr), m_id(0) {}
// CTOR
Person::Person( const char* name, int id ): m_id(id), m_name(nullptr) {
    SetName(name);
}
// CCTOR
Person::Person( const Person& other ): m_id(other.m_id), m_name(nullptr) {
    SetName(other.m_name);
}
// DTOR
Person::~Person(){
    if (m_name)
        delete m_name;
}

// Methods
void Person::SetName( const char* newName ) {
    if (m_name)
        delete m_name;
    if (newName)
        m_name = strdup(newName);
}
void Person::SetId( int newId ) {
    m_id = newId;
}
char* Person::GetName() const {
    return m_name;
}
int Person::GetId() const {
    return m_id;
}

