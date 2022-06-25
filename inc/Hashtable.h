#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H
#include <iostream>
#include <vector>

class Hashtable
{
private:
  int hash(int v) const;
  double threshold_;
  int capacity_;
  int size_;
  int* hashTable;
  int* statusTable;
  enum status{emptySinceStart = 0, emptyAfterRemoval, occupied};
public:
	Hashtable();
	Hashtable(int capacity);
	Hashtable(int capacity, double threshold);
	Hashtable(const Hashtable& other);
	Hashtable& operator=(const Hashtable& other);
	~Hashtable();
    int size() const;
    int capacity() const;
    double getLoadFactorThreshold() const;
    bool empty() const;
    void insert(const int value);
    void remove(int value);
    bool contains(int value) const;
    int indexOf(int value) const;
    void clear();
    static bool isPrime(int n);
    static int nextPrime(int n);
    void resize();
};
#endif
