#include <iostream>
#include "List.h"

DFlist::DFlist(const DFlist& other) {
	if (other.head==nullptr)
	{
		head = nullptr;
		tail = nullptr;
		return;
	}
	Node* first = other.head;
	while (first != nullptr)
	{
		this->push_back(first->val);
		first = first->nval;
	}
}

DFlist& DFlist::operator=(const DFlist& other) {
	if (this!=&other)
	{
		while (head!=nullptr)
		{
			pop_front();
		}
		Node* first = other.head;
		while (first!=nullptr)
		{
			this->push_back(first->val);
			first = first->nval;
		}
	}
	return *this;
}

DFlist::~DFlist() {
	while (head!=nullptr)
	{
		pop_front();
	}
}

DFlist::DFlist(DFlist&& other) {
	head = other.head;
	tail = other.tail;
	other.head = nullptr;
	other.tail = nullptr;
}

DFlist& DFlist::operator=(DFlist&& other) {
	if (this!=&other)
	{
		while (head!=nullptr)
		{
			pop_front();
		}
		head = other.head;
          	tail = other.tail;
          	other.head = nullptr;
          	other.tail = nullptr;
	}
	return *this;
}

void DFlist::push_front(double v) {
	Node* first = new Node{v,head,nullptr};
	if (head!=nullptr)
	{
		head->pval = first;
		head = first;
	}
	else
	{
		head = first;
		tail = first;
	}
}

void DFlist::pop_front() {
	if (head!=nullptr)
	{
		if (head->nval != nullptr)
		{
			Node* tmp = head->nval;
			tmp->pval = nullptr;
			delete head;
			head = tmp;
		}
		else
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
	}
}

DFlist::Node& DFlist::front() const {
	if (head==nullptr)
		throw std::runtime_error("List is empty");
	return *head;
}

size_t DFlist::size() const {
	size_t cnt = 0;
	Node* tmp = head;
	while (tmp!=nullptr)
	{
		cnt++;
		tmp = tmp->nval;
	}
	return cnt;
}

bool DFlist::empty() const {
	if (head==nullptr)
		return true;
	return false;
}

void DFlist::erase(double v) {
	if (head==nullptr)
		return;
	Node* tmp = head;
	tmp = tmp->nval;
	while (tmp!=nullptr)
	{
		if (tmp->val == v)
		{
			if (tmp->nval != nullptr)
			{
				Node* tmp2 = tmp->nval;
				tmp->pval->nval = tmp2;
				tmp2->pval = tmp->pval;
				delete tmp;
				tmp = tmp2;
				continue;
			}
			else
			{
				pop_back();
				tmp = nullptr;
				continue;
			}
		}
		tmp = tmp->nval;
	}
	if (head!=nullptr && head->val == v)
		pop_front();
}

void DFlist::clear() {
	while (head!=nullptr)
	{
		pop_front();
	}
}

void DFlist::push_back(double v) {
	Node *tmp = new Node{v,nullptr,tail};
	if (tail!=nullptr)
	{
		tail->nval = tmp;
		tail = tmp;
	}
	else
	{
		head = tmp;
		tail = tmp;
	}
}

void DFlist::pop_back() {
	if (tail!=nullptr)
        {
                  if (tail->pval != nullptr)
                  {
                          Node* tmp = tail->pval;
                          tmp->nval = nullptr;
                          delete tail;
                          tail = tmp;
                  }
                  else
                  {
                          delete head;
                          head = nullptr;
                          tail = nullptr;
                  }
        }
}

void DFlist::insert(int index,double value) {
	if (index > 0 && index < size())
	{
		int cnt = 0;
		Node* tmp = head;
		while (cnt!=index)
		{
			tmp = tmp->nval;
			cnt++;
		}
		Node* ins = new Node{value,tmp,tmp->pval};
		tmp->pval->nval = ins;
		tmp->pval = ins;
	}
	else if (index==0)
		push_front(value);
	else if (index==size())
		push_back(value);
}

DFlist::Node& DFlist::back() const {
	if (tail!=nullptr)
		return *tail;
	throw std::runtime_error("List is empty");
}

double DFlist::operator[](int index) const {
	if (index < 0 || index>=size())
		throw std::runtime_error("Incorrect index");
	Node* tmp = head;
	int cnt = 0;
	while (tmp!=nullptr)
	{
		if (cnt==index)
		{
			return tmp->val;
		}
		tmp = tmp->nval;
		cnt++;
	}
	throw std::runtime_error("Error in operator []");
}

DFlist::DFlist() {
	head = nullptr;
	tail = nullptr;
}

DFlist DFlist::operator+(const DFlist& other) {
	if (head==nullptr)
		return other;
	if (other.head == nullptr)
		return *this;
	DFlist result;
	Node* tmp = head;
	while (tmp!=nullptr)
	{
		result.push_back(tmp->val);
		tmp = tmp->nval;
	}
	tmp = other.head;
	while (tmp!=nullptr)
	{
		result.push_back(tmp->val);
		tmp = tmp->nval;
	}
	return result;
}

std::ostream& operator<<(std::ostream &out, const DFlist& ob) {
	DFlist::Node* tmp = ob.head;
	while (tmp!=nullptr)
	{
		out << tmp->val << " ";
		tmp = tmp->nval;
	}
	out << "\n";
	return out;
}

