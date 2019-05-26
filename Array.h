#pragma once
#ifndef _ARRAY_H
#define _ARRAY_H

typedef signed long int Long;
template<typename T>
class Array {
public:
   // 생성자,소멸자
   Array(Long capacity=256);
   ~Array();
   Array(const Array& source);
   //멤버함수
   Long Store(Long index, T object);
   Long Insert(Long index, T object);
   Long AppendFromFront(T object);
   Long AppendFromRear(T object);
   Long Delete(Long index);
   Long DeleteFromFront();
   Long DeleteFromRear();
   void Clear();
   Long Modify(Long index, T object);
   Long LinearSearchUnique(void *key, int(*compare)(void*, void*));
   void LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*));
   Long BinarySearchUnique(void *key, int(*compare)(void*, void*));
   void BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*));
   void BubbleSort(int(*compare)(void*, void*));
   void InsertionSort(int(*compare)(void*, void*));
   void SelectionSort(int(*compare)(void*, void*));
   T& GetAt(Long index);
   Long GetLength() const;
   Long GetCapacity() const;
   void Merge(const Array& one, const Array& other, int(*compare)(void*, void*));
   //연산자함수
   Array& operator=(const Array& source);
   T& operator[](Long index);
   T* operator+(Long index);
private:
   T(*front);
   Long capacity;
   Long length;
};
template<typename T>
inline Long Array<T>::GetCapacity() const {
   return this->capacity;
}
template<typename T>
inline Long Array<T>::GetLength() const {
   return this->length;
}

// 탬플릿클래스는 헤더에 함수정의를 포함한다.

// 생성자정의
template<typename T>
Array<T>::Array(Long capacity) {
   this->front = new T[capacity];
   this->capacity = capacity;
   this->length = 0;
}
template<typename T>
Array<T>::~Array() {
}
template<typename T>
Array<T>::Array(const Array& source) {
   Long i = 0;

   this->front = new T[source.capacity];
   this->capacity = source.capacity;
   while (i < source.length) {
      this->front[i] = source.front[i];
      i++;
   }
   this->length = source.length;
}
template<typename T>
Long Array<T>::Store(Long index, T object) {
   this->front[index] = object;
   this->length++;
   return index;
}
template<typename T>
Long Array<T>::Insert(Long index, T object) {
   Long i = 0;
   Long j = 0;
   T(*front) = 0; // 초기화 습관화

   front = new T[this->capacity + 1];
   while (i < index) {
      front[j] = this->front[i];
      j++;
      i++;
   }
   j = index + 1;
   while (i < this->length) {
      front[j] = this->front[i];
      j++;
      i++;
   }
   if (this->front != 0) {
      delete[]this->front;
   }
   this->front = front;
   this->capacity++;
   this->front[index] = object;
   this->length++;
   return index;
}
template<typename T>
Long Array<T>::AppendFromFront(T object) {
   Long index = 0;
   Long i = 0;
   T(*front)=0;

   front = new T[this->capacity + 1];
   while (i < this->length) {
      front[i + 1] = this->front[i];
      i++;
   }
   if (this->front != 0) {
      delete[]this->front;
   }
   this->front = front;
   this->capacity++;
   this->front[index] = object;
   this->length++;
   return index;
}
template<typename T>
Long Array<T>::AppendFromRear(T object) {

   Long i = 0;
   Long index;
   T (*front) = 0;

   front = new T[this->capacity + 1];
   while (i < this->length) {
      front[i] = this->front[i];
      i++;
   }
   if (this->front != 0) {
      delete[] this->front;
      this->front = 0;
   }
   this->front = front;
   this->capacity++;
   index = this->capacity - 1;
   this->front[index] = object;
   this->length++;
   
   return index;
}
template<typename T>
Long Array<T> ::Delete(Long index) {
   Long i = 0;
   Long j = 0;
   T(*front) = 0;
   if (this->capacity > 1) {
      front = new T[this->capacity - 1];
   }
   while (i < index) {
      front[j] = this->front[i];
      j++;
      i++;
   }
   i = index + 1;
   while (i < this->length) {
      front[j] = this->front[i];
      j++;
      i++;
   }
   if (this->front != 0) {
      delete[]this->front;
      this->front = 0;
   }
   if (this->capacity > 1) {
      this->front = front;
   }
   this->capacity--;
   this->length--;
   index = -1;
   return index;
}
template<typename T>
Long Array<T> ::DeleteFromFront() {
   T(*front) = 0;
   Long i = 0;
   Long j = 0;
   Long index;

   if (this->capacity > 1) {
      front = new T[capacity-1];
   }
   while (i < this->length) {
      front[j] = this->front[i];
      j++;
      i++;
   }
   if (this->front != 0) {
      delete[]this->front;
      this->front = 0;
   }
   if (this->capacity > 1) {
      this->front = front;
   }
   this->capacity--;
   this->length--;
   index = -1;
   return index;
}
template<typename T>
Long Array<T>::DeleteFromRear() {
   T(*front) = 0;
   Long i = 0;
   Long index;

   if (this->capacity > 1) {
      front = new T[capacity - 1];
   }
   while (i < this->length - 1) {
      front[i] = this->front[i];
      i++;
   }
   if (this->front != 0) {
      delete[]this->front;
      this->front = 0;
   }
   if (this->capacity > 1) {
      this->front = front;
   }
   this->capacity--;
   this->length--;
   index = -1;
   return index;
}
template<typename T>
void Array<T>::Clear() {
   if (this->front != 0) {
      delete[]this->front;
      this->front = 0;
   }
   this->capacity = 0;
   this->length = 0;
}
template<typename T>
Long Array<T>::Modify(Long index, T object) {
   this->front[index] = object;
   return index;
}

template<typename T>
Long Array<T>::LinearSearchUnique(void*key, int(*compare)(void*, void*)) {
   Long i = 0;
   Long index = -1;
   while (i < this->length &&compare(this->front + i, key) != 0) {
      i++;
   }
   if (i < this->length) {
      index = i;
   }
   return index;
}
template<typename T>
void Array<T> ::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {
   Long i = 0;
   Long j = 0;
   *count = 0;

   *indexes = new Long [this->length];
   while (i < this->length) {
      if (compare(this->front + i, key) == 0) {
         (*indexes)[j] = i;
         j++;
         (*count)++;
      }
      i++;
   }
}
template<typename T>
Long Array<T>::BinarySearchUnique(void*key, int(*compare)(void*, void*)) {
   
   Long low = 0;
   Long middle;
   Long high;
   Long index=-1;

   high = this->length - 1;
   middle = (low + high) / 2;
   while (low <= high && compare(this->front + middle, key) != 0) {
      if (compare(this->front + middle, key) > 0) {
         high = middle - 1;
      }
      else {
         low = middle + 1;
      }
      middle = (low + high) / 2;
   }
   if (low <= high) {
      index = middle;
   }
   return index;
}
template<typename T>
void Array<T> ::BinarySearchDuplicate(void*key, Long*(*indexes), Long *count, int(*compare)(void*, void*)) {
   Long low = 0;
   Long high;
   Long middle;
   Long i = 0;
   Long j = 0;
   *count = 0;

   (*indexes) = new Long[this->length];
   high = this->length - 1;
   middle=(low + high) / 2;
   while (low <= high && compare(this->front + middle, key) != 0) {
      if (compare(this->front + middle, key) > 0) {
         high = middle - 1;
      }
      else {
         low = middle + 1;
      }
      middle = (low + high) / 2;
   }
   i = middle - 1;
   while (i >= 0 && compare(this->front + i, key) == 0) {
      i--;
   }
   i = 0;
   while (i < this->length&&compare(this->front + i, key) == 0) {
      (*indexes)[j] = i;
      j++;
      (*count)++;
      i++;
      }
}

template<typename T>
T& Array<T>::GetAt(Long index) {
   return this->front[index];
}

template<typename T>
void Array<T> ::Merge(const Array& one, const Array& other, int(*compare)(void*, void*)) {
   Long i = 0;
   Long j = 0;
   Long k = 0;
   if (this->front != 0) {
      delete[]this->front;
      this->front = 0;
   }
   this->front = new T[one.length + other.length];
   this->capacity = one.length + other.length;

   while (i < one.length && j < other.length) {
      if (compare(one.front + i, other.front + j) < 0) {
         this->front[k] = one.front[i];
         k++;
         i++;
      }
      else {
         this->front[k] = other.front[j];
         k++;
         j++;
      }
   }
   while (i < one.length) {
      this->front[k] = one.front[i];
      k++;
      i++;
   }
   while (j < other.length) {
      this->front[k] = other.front[j];
      k++;
      j++;
   }
   this->length = one.length + other.length;
}

template<typename T>
Array<T>& Array<T> ::operator=(const Array& source) {
   Long i = 0;
   if (this->front != 0) {
      delete[]this->front;
   }
   this->front = new T[source.capacity];
   this->capacity = source.capacity;
   while (i < source.length) {
      this->front[i] = source.front[i];
      i++;
   }
   this->length = source.length;
   return *this;
}
template<typename T>
T& Array<T>::operator[](Long index) {
   return this->front[index];
}
template<typename T>
T* Array<T>::operator+(Long index) {
   return this->front + index;
}
template<typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)) {
   T temp;
   Long i = 0;
   Long j;
   while (i < this->length - 1) {
      j = i - 1;
      while (j < this->length) {
         if (compare(this->front + i, this->front + j) > 0) {
            temp = this->front[i];
            this->front[i] = this->front[j];
            this->front[j] = temp;
         }
         j++;
      }
      i++;
   }
}
template<typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)) {
   T key;
   Long i = 1;
   Long j;
   while (i < this->length) {
      key = this->front[i];
      j = i - 1;
      while (j >= 0 && compare(this->front + i, &key) > 0) {
         this->front[j + 1] = this->front[i];
         j--;
      }
      this->front[j + 1] = key;
      i++;
   }
}

template<typename T>
void Array<T>::BubbleSort(int(*compare)(void*, void*)) {
   Long i = 0;
   Long j;
   Long k;
   Long count;
   T temp;

   count = this->length;
   while (i < this->length - 1) {
      count--;
      j = 0;
      k = j + 1;
      while (j < count) {
         if (compare(this->front + j, this->front + k) > 0) {
            temp = this->front[j];
            this->front[j] = this->front[k];
            this->front[k] = temp;
         }
         k++;
         j++;
      }
      i++;
   }
}
#endif // _ARRAY_H