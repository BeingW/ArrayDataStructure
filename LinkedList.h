//LinkedList.h
#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef signed long int Long;

template <typename T>
class LinkedList {
public: //Nested class
	class Node {
		friend class LinkedList;
	public:
		Node() {
			this->previous = this;
			this->next = this;
		}
		Node(T object) {
			this->previous = this;
			this->object = object;
			this->next = this;
		}
		Node(Node *previous, T object) {
			this->previous = previous;
			this->object = object;
			this->next = this;
		}
		Node(T object, Node *next) {
			this->previous = this;
			this->object = object;
			this->next = next;
		}
		Node(Node *previous, T object, Node *next) {
			this->previous = previous;
			this->object = object;
			this->next = next;
		}
		Node(const Node& source) {
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;
		}
		~Node() {
		}
		Node& operator =(const Node& source) {
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;

			return *this;
		}
		T& GetObject() const {
			return const_cast<T&>(this->object);
		}
	private:
		Node *previous;
		T object;
		Node *next;
	};

public:
	LinkedList();
	LinkedList(const LinkedList& source);
	~LinkedList();
	Node* InsertBefore(Node *index, T object);
	Node* InsertAfter(Node *index, T object);
	Node* AppendFromHead(T object);
	Node* AppendFromTail(T object);
	Node* Delete(Node *index);
	Node* DeleteFromHead();
	Node* DeleteFromTail();
	void DeleteAllItems();
	Node* LinearSeachUnique(void *key, int(*compare)(void*, void*));
	void LinearSeachDuplicate(void *key, Node **(*indexes), Long *count, int(*compare)(void*, void*));
	Node* First();
	Node* Previous();
	Node* Next();
	Node* Last();
	Node* Move(Node *index);

	LinkedList& operator =(const LinkedList& source);
	T& operator [](Long index);
	Long GetLength() const;
	Node* GetCurrent() const;
private:
	Node *head;
	Node *tail;
	Long length;
	Node *current;
};

template <typename T>
inline Long LinkedList<T>::GetLength() const {
	return this->length;
}
template<typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetCurrent() const {
	return const_cast<Node*>(this->current);
}
template <typename T>
LinkedList<T>::LinkedList() {
	this->head = 0;
	this->tail = 0;
	this->length = 0;
	this->current = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& source) {
	this->head = 0;
	this->tail = 0;
	this->length = 0;
	this->current = 0;
	Node *previous = 0;
	Node *it;
	Node *temp;

	it = source.head;
	while (it != previous) {
		if (this->tail != 0) {
			this->current = new Node(this->tail, it->object);
		}
		else {
			this->current = new Node(it->object);
		}
		if (this->tail != 0) {
			this->tail->next = this->current;
		}
		else {
			this->head = this->current;
		}
		if (it == source.current) {
			temp = this->current;
		}
		this->tail = this->current;
		this->length++;
		previous = it;
		it = it->next;
	}
	this->current = temp;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Node *previous = 0;

	this->current = this->head;
	while (this->current != previous) {
		previous = this->current;
		this->head = this->current->next;
		if (this->current != 0) {
			delete this->current;
		}
		this->current = this->head;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertBefore(Node *index, T object) {

	if (this->head != index) {
		this->current = new Node(index->previous, object, index);
	}
	else {
		this->current = new Node(object, index);
	}
	if (this->head != index) {
		index->previous->next = this->current;
	}
	else {
		this->head = this->current;
	}
	index->previous = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertAfter(Node *index, T object) {

	if (this->tail != index) {
		this->current = new Node(index, object, index->next);
	}
	else {
		this->current = new Node(index, object);
	}
	if (this->tail != index) {
		index->next->previous = this->current;
	}
	else {
		this->tail = this->current;
	}
	index->next = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromHead(T object) {

	if (this->head != 0) {
		this->current = new Node(object, this->head);
	}
	else {
		this->current = new Node(object);
	}
	if (this->head != 0) {
		this->head->previous = this->current;
	}
	else {
		this->tail = this->current;
	}
	this->head = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromTail(T object) {

	if (this->tail != 0) {
		this->current = new Node(this->tail, object);
	}
	else {
		this->current = new Node(object);
	}
	if (this->tail != 0) {
		this->tail->next = this->current;
	}
	else {
		this->head = this->current;
	}
	this->tail = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Delete(Node *index) {

	if (this->head != index && this->tail != index) {
		index->previous->next = index->next;
		index->next->previous = index->previous;
		this->current = index->next;
	}
	else if (this->tail != index) {
		index->next->previous = index->next;
		this->head = index->next;
		this->current = index->next;
	}
	else if (this->head != index) {
		index->previous->next = index->previous;
		this->tail = index->previous;
		this->current = index->previous;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromHead() {
	Node *index;

	index = this->head;
	if (this->tail != index) {
		this->head->next->previous = this->head->next;
		this->head = this->head->next;
		this->current = this->head;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromTail() {
	Node *index;

	index = this->tail;
	if (this->head != index) {
		this->current = index->previous;
		this->current->next = this->current;
		this->tail = this->current;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

template <typename T>
void LinkedList<T>::DeleteAllItems() {
	Node *previous = 0;

	this->current = this->head;
	while (this->current != previous) {
		previous = this->current;
		this->head = this->current->next;
		if (this->current = 0) {
			delete this->current;
		}
		this->length--;
		this->current = this->head;
	}
	this->head = 0;
	this->tail = 0;
	this->current = 0;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::LinearSeachUnique(void *key, int(*compare)(void*, void*)) {
	Node *index = 0;
	Node *previous = 0;
	Node *it;

	it = this->head;
	while (it != previous && compare(&(it->object), key) != 0) {
		previous = it;
		it = it->next;
	}
	if (it != previous) {
		index = it;
	}

	return index;
}

template <typename T>
void LinkedList<T>::LinearSeachDuplicate(void *key, Node **(*indexes), Long *count, int(*compare)(void*, void*)) {
	Node *previous = 0;
	Long i = 0;
	*count = 0;

	*indexes = new Node*[this->length];
	this->current = this->head;

	while (this->current != previous) {
		if (compare(&(this->current->object), key) == 0) {
			(*indexes)[i] = this->current;
			(*count)++;
			i++;
		}
		previous = this->current;
		this->current = this->current->next;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::First() {
	this->current = this->head;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Previous() {
	this->current = this->current->previous;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Next() {
	this->current = this->current->next;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Last() {
	this->current = this->tail;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Move(Node *index) {
	this->current = index;

	return this->current;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& source) {
	Node *previous = 0;
	Node *temp;
	Node *it;

	this->current = this->head;
	while (this->current != previous) {
		previous = this->current;
		this->head = this->current->next;
		if (this->current = 0) {
			delete this->current;
		}
		this->length--;
		this->current = this->head;
	}
	this->head = 0;
	this->tail = 0;
	this->current = 0;

	previous = 0;
	it = source.head;
	while (it != previous) {
		if (this->tail != 0) {
			this->current = new Node(this->tail, it->object);
		}
		else {
			this->current = new Node(it->object);
		}
		if (this->tail != 0) {
			this->tail->next = this->current;
		}
		else {
			this->head = this->current;
		}
		if (it == source.current) {
			temp = this->current;
		}
		this->tail = this->current;
		this->length++;
		previous = it;
		it = it->next;
	}
	this->current = temp;

	return *this;
}

template <typename T>
T& LinkedList<T>::operator[](Long index) {
	Long i = 0;

	this->current = this->head;
	while (i < index) {
		this->current = this->current->next;
		i++;
	}

	return this->current->object;
}
#endif //_LINKEDLIST_H