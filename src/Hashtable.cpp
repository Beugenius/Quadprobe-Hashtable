#include "Hashtable.h"

int Hashtable::hash(int v) const {
   return v % capacity();
}
/**
 * @brief - Default Constructor, initializes size_ to 0, capacity_ to 17, threshold to .65
 */
Hashtable::Hashtable() {
    size_ = 0;
    capacity_ = 17;
    threshold_ = .65;
    hashTable = new int[17];
    statusTable = new int[17];
    // initializing all values to null and 0
    for(int i = 0; i < capacity_; ++i) {
        statusTable[i] = status::emptySinceStart;
        hashTable[i] = 0;
    }
}

/**
 * @brief - Overloaded constructor that dynamically sizes the capacity
 * @param capacity
 */

Hashtable::Hashtable(int capacity) {
    size_ = 0;
    capacity_ = capacity;
    threshold_ = .65;
    hashTable = new int[capacity_];
    statusTable = new int[capacity_];
    // initializes all values to empty
    for(int i = 0; i < capacity_; ++i) {
        statusTable[i] = status::emptySinceStart;
        hashTable[i] = 0;
    }
}

/**
 * @brief -Overloaded constructor that dynamically sizes the capacity and sets threshold to custom value
 */

Hashtable::Hashtable(int capacity, double threshold) {
    size_ = 0;
    capacity_ = capacity;
    threshold_ = threshold;
    hashTable = new int[capacity_];
    statusTable = new int[capacity_];
    // initializes all values to empty
    for(int i = 0; i < capacity_; ++i) {
        statusTable[i] = status::emptySinceStart;
        hashTable[i] = 0;
    }
}

/**
 * @brief - Copy constructor that creates a new hashtable from an existing one
 */

Hashtable::Hashtable(const Hashtable& other) {
    // setting private attributes of this to the others
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    this->threshold_ = other.threshold_;
    // dynamically allocating new memory for each array
    this->hashTable = new int[other.capacity_];
    this->statusTable = new int[other.capacity_];
    // initialize all values to empty
    for(int i = 0; i < capacity_; ++i) {
        this->statusTable[i] = other.statusTable[i];
        this->hashTable[i] = other.hashTable[i];

    }
}

/**
 * @brief - overloaded = operator that copies a hashtable to another hashtable
 */

Hashtable& Hashtable::operator=(const Hashtable& other) {
    // handles self assignment protection
    if (this == &other) {
        return *this;
    }
    this->capacity_ = other.capacity_;
    this->threshold_ = other.threshold_;
    // after setting capacity and threshold, clear restores list to current capacity
    this->clear();
    this->size_ = other.size_;
    for(int i = 0; i < capacity_; ++i) {
        this->statusTable[i] = other.statusTable[i];
        this->hashTable[i] = other.hashTable[i];
    }
    return *this;
}

/**
 * @brief - destructor that deletes all dynamically allocated memory
 */

Hashtable::~Hashtable() {
    delete [] hashTable;
    delete [] statusTable;
    hashTable = nullptr;
    statusTable = nullptr;
}

/**
 * @brief - simply returns the size or how many items in the array
 */

int Hashtable::size() const {
    return size_;
}

/**
 * @brief - simply returns the height of the array (max size possible)
 */

int Hashtable::capacity() const {
    return capacity_;
}

/**
 * @brief - simply returns the threshold
 */

double Hashtable::getLoadFactorThreshold() const {
   return threshold_;
}

/**
 * @brief - boolean value indicating whether or not the hashtable is empty
 */

bool Hashtable::empty() const {
    return size_ == 0;
}

/**
 * @brief - function that inserts an item into the hashtable at the appropriate location using quadratic probing
 */

void Hashtable::insert(int value) {

    int bucketsProbed = 0;
    int key = hash(value + bucketsProbed*bucketsProbed);
    while (bucketsProbed < capacity_) {
        // this if statement just means if the location is not occupied, then we can occupy it
        if(statusTable[key] != status::occupied) {
            hashTable[key] = value;
            statusTable[key] = status::occupied;
            ++size_;
            // this statement determines the load factor and if it is more than the threshold, then resize
            if(static_cast<double>(size_)/static_cast<double>(capacity_) > threshold_) {
                resize();
            }
            return;
        }
        // updates the amount of buckets probed, which, updates the key value
        ++bucketsProbed;
        key = hash(value + bucketsProbed*bucketsProbed);
    }
}

/**
 * @brief - remove function that quadratically probes for a value in the hashtable and if found removes it
 */

void Hashtable::remove(int value) {
    int bucketsProbed = 0;
    int key = hash(value + bucketsProbed*bucketsProbed);
    while (bucketsProbed < capacity_) {
        // if value found
        if(hashTable[key] == value) {
            hashTable[key] = 0;
            statusTable[key] = status::emptyAfterRemoval;
            --size_;
            return;
        }
        ++bucketsProbed;
        key = hash(value + bucketsProbed*bucketsProbed);
    }
}

/**
 * @brief - method that checks if a value is in the hashtable
 */

bool Hashtable::contains(int value) const {
    int bucketsProbed = 0;
    int key = hash(value + bucketsProbed*bucketsProbed);
    while (bucketsProbed < capacity_) {
        // if it hits a bucket that has been empty since the start, it is clearly not in hashtable
        if(statusTable[key] == status::emptySinceStart) {
            return false;
        }
        if(hashTable[key] == value) {
            return true;
        }
        ++bucketsProbed;
        key = hash(value + bucketsProbed*bucketsProbed);
    }
    return false;
}

/**
 * @brief - finds the index of a value to ensure quadratic probing
 */

int Hashtable::indexOf(int value) const {
    int bucketsProbed = 0;
    int key = hash(value+ bucketsProbed*bucketsProbed);
    while (bucketsProbed < capacity_) {
        if(hashTable[key] == value) {
            // the key is ultimately the bucket index of the value found
            return key;
        }
        ++bucketsProbed;
        key = hash(value + bucketsProbed*bucketsProbed);
    }
    return -1;
}

/**
 * @brief - this resets the hashtable and statusTable to a default state by the current capacity
 */

void Hashtable::clear() {
    delete [] hashTable;
    delete [] statusTable;
    hashTable = new int[capacity_];
    statusTable = new int[capacity_];
    // initialize all values
    for(int i = 0; i < capacity_; ++i) {
        statusTable[i] = status::emptySinceStart;
        hashTable[i] = 0;
    }
    size_ = 0;
}

/**
 * @brief - checks if a number is prime
 */

bool Hashtable::isPrime(int n) {
    if(n == 2 || n == 3) {
        return true;
    }
    for(int i = 3; i < n; ++i) {
        // if any number from i to n-1 can divide the number, then it is not prime
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}

/**
 * @brief - find the next primeNumber greate than the current number
 */

int Hashtable::nextPrime(int n) {
   n += 1;
   // repeatedly updates the number until a prime number is found
   while(!isPrime(n)) {
       ++n;
   }
   return n;
}

/**
 * @brief - resizes the array to the next prime number to limit load factor
 */

void Hashtable::resize() {
    // these temps just hold the values temporarily
    int tempHash[capacity_];
    int tempStatus[capacity_];
    int tempCapacity = capacity_;
    for(int i = 0; i < capacity_; ++i) {
        // copying only the values that are used
        if(statusTable[i] == status::occupied) {
            tempHash[i] = hashTable[i];
            tempStatus[i] = statusTable[i];
        }
    }
    // doubles the current capacity number
    int prime = capacity_*2;
    // now finds the next highest prime number after being doubled
    prime = nextPrime(prime);
    capacity_ = prime;
    // re-initialize arrays with new next highest prime number capacity
    clear();
    size_ = 0;
    // initialize values
    for(int i = 0; i < capacity_; ++i) {
        statusTable[i] = status::emptySinceStart;
        hashTable[i] = 0;
    }
    // insert back into the list in the correct location
    for(int i = 0; i < tempCapacity; ++i) {
        if(tempStatus[i] == status::occupied) {
            insert(tempHash[i]);
        }
    }
}
