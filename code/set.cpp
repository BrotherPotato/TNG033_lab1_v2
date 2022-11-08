#include "set.hpp"

// std::size_t is defined in the C++ standard library
// std::size_t is an unsigned integer type that can store the maximum size of any possible object
// sizes are non-negative integers -- i.e. unsigned integer type

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ******************************************************** */

// Default constructor
Set::Set()
    : head(new Node{ 0, nullptr }), counter(0) {
}

// Constructor for creating a set from an int
Set::Set(int v) {
    insert(v);
    counter++;
}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements
Set::Set(const std::vector<int>& V) { //Constructor creating a set S from a non-sorted vector V of non-unique integers
	for (int i = 0; i < std::ssize(V); i++) {
		insert(V[i]);
		counter++;
	}
}

// copy constructor 
Set::Set(const Set& source) : Set() { //deep copy
    Node* ptrSauce = source.head->next; //S source
	Node* ptrThis = head; //R set()

    while (ptrSauce) {
        insert(head, ptrSauce->value);
        ptrSauce = ptrSauce->next;
        ptrThis = ptrThis->next;
    }

    counter = source.counter;
}

// Assignment operator: copy-and-swap idiom
Set& Set::operator=(Set s) {
    std::swap(head, s.head);
    std::swap(counter, s.counter);

	return *this; //destructor is called before the function ends :)
}

// Destructor: deallocate all nodes
Set::~Set() {
	Node* ptr = head;
	while (ptr != nullptr) {
        head = ptr->next;
        remove(ptr);
		ptr = head;
	}
	head = nullptr; // not necessary
    counter = 0;
}


// Return number of elements in the set
std::size_t Set::cardinality() const {
    return counter;
}

// Test if set is empty
bool Set::empty() const {
	
	return (counter == 0);
}

// Test if x is an element of the set
bool Set::member(int x) const {
    Node* ptr = head;

    while (ptr != nullptr && ptr->value != x) {
        ptr = ptr->next;
    }

    if (ptr == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

bool Set::operator<=(const Set& b) const {
    Node* temp = head->next;

    while (temp != nullptr) {
        if (!b.member(temp->value)) {
            return false;
        }
        temp = temp->next;
    }

    return false;  // delete if needed
}

bool Set::operator==(const Set& b) const {
  
    //if (operator<=(b)) { // *this <= b
     //   if (b.operator<=(*this)) { 
	if (b <= *this && *this <= b) { //^^ the same code
            return true;
    }


    return false;  // delete if needed
}

bool Set::operator!=(const Set& b) const {
    if(!(*this == b)){ //if (!operator==(b)) {
        return true;
    }

    return false;  // delete if needed
}

bool Set::operator<(const Set& b) const {
    if(*this <= b){ //if (operator<=(b)) {
		if(counter < b.counter){
		    return true;
	    }
    }

    return false;  // delete if needed
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {
    Node* ptr1 = this->head->next;
    Node* ptr2 = b.head->next;
    std::vector<int> sum; 

    for(int i = 0; i < )


    return Set{};  // delete if needed
}

// Set intersection
Set Set::operator*(const Set& b) const {
    // ADD CODE

    return Set{};  // delete if needed
}

// Set difference
Set Set::operator-(const Set& b) const {
    // ADD CODE

    return Set{};  // delete if needed
}

// set difference with set {x}
Set Set::operator-(int x) const {
    // ADD CODE

    return Set{};  // delete if needed
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
    if (theSet.empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp != nullptr) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/


void Set::insert(Node* ptr, int value) const{
	Node* newNode = new Node(value, ptr->next);
    ptr->next = newNode;
}

void Set::insert(int value) const{
	Node* ptr = head;
	while (ptr->next != nullptr && ptr->next->value <= value) {
		ptr = ptr->next;
	}
	if (ptr->next == nullptr || ptr->next->value > value) {
		insert(ptr, value); //inserts the value after ptr
	}
}

void Set::remove(Node* ptr) {
    delete ptr;
	ptr->next = nullptr; //safety
}