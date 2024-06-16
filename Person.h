#ifndef PERSON_H
#define PERSON_H

#include <string.h>
#include <iostream>
using namespace std;


class Person
{
public:
	Person();
	Person( const char* name, int id );
	Person( const Person& other );
	~Person();
	const Person &operator=(const Person &p);
    bool operator==(const Person &p) const;
    char &operator[](int index);

public:
	void	SetName( const char* newName );
	void	SetId( int newId );
	char*	GetName() const;
	int		GetId() const;

private:
	char*	m_name;
	int		m_id;
};



#endif // !PERSON_H
