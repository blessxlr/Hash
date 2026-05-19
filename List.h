#pragma once

#include <iostream>

class DFlist {
	private:
		struct Node {
			double val;
			Node* nval;
			Node* pval;
		};
		Node* head = nullptr;
		Node* tail = nullptr;
	public:
		DFlist();
		DFlist(const DFlist& other);
		DFlist& operator=(const DFlist& other);
		DFlist(DFlist&& other);
		DFlist& operator=(DFlist&& other);
		~DFlist();
		void push_front(double v);
		void pop_front();
		Node& front() const;
		size_t size() const;
		bool empty() const;
		void erase(double v);
		void clear();
		void push_back(double v);
		void pop_back();
		void insert(int index,double value);
		Node& back() const;
		double operator[](int index) const;
		DFlist operator+(const DFlist& other);
		friend std::ostream& operator<<(std::ostream &out,const DFlist &ob);
};

std::ostream& operator<<(std::ostream &out,const DFlist &ob);
