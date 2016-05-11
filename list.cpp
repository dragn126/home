#include <iostream>
using namespace std;
ostream& operator<<(ostream& o, string& s)
{
	o << s.c_str();
	return o;
}
istream& operator>>(istream& i, string& s)
{
	char buf[256];
	i >> buf;
	string tmp(buf);
	s = tmp;
	return i;
}
template<typename T>
class AbstractList
{
protected:
	T _default;
public:
	virtual void sort(bool(*f) (T* first, T* second)) = 0;
	virtual T get(int index) = 0;
	virtual void set(int index, T data) = 0;
	virtual void insert(int index, T data) = 0;
	virtual T remove(int index) = 0;
	virtual int len() = 0;
	void push(T data)
	{
		insert(0, data);
	}
	virtual T pop()
	{
		if (empty())
			return _default;
		else
			return remove(0);
	}
	virtual bool empty()
	{
		return len() == 0;
	}
	virtual ostream& print(ostream& o)
	{
		for (int i = 0; i < len(); i++)
		{
			o << get(i) << endl;
		}
		return o;
	}
	virtual istream& read(istream& in)
	{
		int count;
		in >> count;
		for (int i = 0; i < count; i++)
		{
			T tmp;
			in >> tmp;
			insert(len(), tmp);
		}
		return in;
	}

};
template<typename T>
class Linkedlist : public AbstractList<T>
{
	T _data;
	Linkedlist* next;
protected:
	T _default;
public:
	Linkedlist()
	{
		this->next = NULL;
	}
	Linkedlist(Linkedlist* next)
	{
		this->next = next;
	}
	Linkedlist(T _default)
	{
		this->next = NULL;
		this->_default = _default;
	}
	Linkedlist(T _data, T _default)
	{
		this->_data = _data;
		this->_default = _default;
		this->next = NULL;
	}
	Linkedlist(T _data, T _default, Linkedlist* next)
	{
		this->_default = _default;
		this->_data = _data;
		this->next = next;
	}
	Linkedlist(const Linkedlist& tmp)
	{
		this->next = tmp.next;
		this->_data = tmp._data;
		this->_default = tmp._default;
	}
	virtual ~Linkedlist()
	{
		next = NULL;
	}
	virtual int len()
	{
		Linkedlist* tmp = this;
		int i = 0;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			i++;
		}
		return i;
	}
	virtual T get(int index)
	{
		Linkedlist* tmp = this;
		if ((index >= len()) || (index < 0))
		{
			return this->_default;
		}
		else
		{
			int i = 0;
			while (index != i)
			{
				tmp = tmp->next;
				i++;
			}
			return tmp->_data;
		}
	}
	virtual void set(int index, T _data)
	{
		Linkedlist* tmp = this;
		if ((index >= len()) || (index < 0))
		{
			return;
		}
		else
		{
			int i = 0;
			while (index != i)
			{
				tmp = tmp->next;
				i++;
			}
			tmp->_data = _data;
			return;
		}
	}
	virtual void insert(int index, T _data)
	{
		Linkedlist* tmp = this;
		Linkedlist* tmp2 = new Linkedlist(_data, this->_default);
		int i = 0;
		while (i != index)
		{
			tmp = tmp->next;
			i++;
		}
		tmp2->next = tmp->next;
		tmp->next = tmp2;
		return;
	}
	virtual T remove(int index)
	{
		Linkedlist* tmp = this;
		int i = 0;
		while (i != index)
		{
			tmp = tmp->next;
			i++;
		if (i == index)
		{
			Linkedlist* tmp2 = tmp->next;
			tmp->next = tmp2->next;
			T inf = tmp2->_data;
			delete tmp2;
			return inf;
		}
		else
		{
		return this->_default;
		}
		}
	}
	virtual void sort(bool(*f) (T* first, T* second))
	{
		Linkedlist* tmp = this;
		Linkedlist* tmp2 = this;
		Linkedlist* other = this;
		Linkedlist* last = this;
		for (int i = 0; i<len(); i++)
			for (int k = 0;k<len() - 1; k++)
			{
				if (f(&(tmp->_data), &(tmp->next->_data)))
				{
					tmp2 = tmp->next;
					other = tmp2->next;
					last->next = tmp2;
					tmp2->next = tmp;
					tmp->next = other;
				}
				last = tmp;
				tmp = tmp->next;
			}
	}
    friend AbstractList<string>* get_init();
};

AbstractList<string>* get_init()
{
	string e("EMPTY!");
	string d("Hello world!");
	Linkedlist<string>* s = new Linkedlist<string>(e, d);
	return s;
}
