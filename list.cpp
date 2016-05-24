#include <iostream>
#include <string>
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
		next = NULL;
	}
	Linkedlist(Linkedlist* _next)
	{
		next = _next;
	}
	Linkedlist(T default_)
	{
		next = NULL;
		_default = default_;
	}
	Linkedlist(T data, T default_)
	{
		_data = data;
		_default = default_;
		next = NULL;
	}
	Linkedlist(T data, T default_, Linkedlist* _next)
	{
		_default = default_;
		_data = data;
		next = _next;
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
		if (index >= len())
		{
			return tmp->_default;
		}
		for (int i = 0; i < len(); i++)
		{
			tmp = tmp->next;
			if (index == i)
			{
				return tmp->_data;
			}
		}
		return tmp->_default;
	}
	virtual void set(int index, T data)
	{
		Linkedlist* tmp = this;
		if (index >= len())
		{
			return;
		}
		for (int i=0; i < len(); i++)
		{
			tmp = tmp->next;
			if (index == i)
			{
				tmp->_data = data;
				return;
			}
		}
		return;
	}
	virtual void insert(int index, T _data)
	{
		if (index < 0)
		{
			index = 0;
		}
		if (index > len())
		{
			index = len();
		}
		Linkedlist* now = next;
		Linkedlist* add = new Linkedlist(_data);
		Linkedlist* prev = this;
		for (int i = 0; i < index; i++)
		{
			prev = now;
			now = now->next;
		}
		prev->next = add;
		add->next = now;
	}
	virtual T remove(int index)
	{
		if (len() == 0 || index < 0)
		{
			return _data;
		}
		else
		{
			if (index > len() - 1)
			{
				index = len() - 1;
			}
			Linkedlist* now = next;
			Linkedlist* prev = this;
			for (int i = 0; i < index; i++)
			{
				prev = now;
				now = now->next;
			}
			T tmp = now->_data;
			prev->next = now->next;
			delete now;
			return tmp;
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
};


Linkedlist<string>* get_init()
{
	string e("EMPTY!");
	string d("Hello world!");
	Linkedlist<string>* s = new Linkedlist<string>(e, d);
	return s;
}
