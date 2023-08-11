/*
 *  CharArrayList.cpp
 *  Naveed Naeem
 *  UTLN: nnaeem01
 *  DATE CREATED: 06/03/2023
 * 
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Contains the Class declaration of CharArrayList
 *
 */
#ifndef CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H

#include <iostream>
#include <string>

const int RUNTIME_ERROR_FIRST = 0;
const int RUNTIME_ERROR_LAST = 1;
const int RUNTIME_ERROR_POP = 2;

using namespace std;

class CharArrayList
{
    public:

        /* Class Constructior */
        CharArrayList();

        /* CharArrayList Class Destructor */
        ~CharArrayList();

        /* Class Constructior with single char input */
        CharArrayList(char c);

        /* Class Constructor with char array and char array size as inputs */
        CharArrayList(char arr[], int size);
        
        /* Copy Constructor: Deep Copy */
        CharArrayList(const CharArrayList &other);
        
        /* Copy Constructor: Deep Copy with operator overloading */
        /* Defining here for cleaner syntax */
        CharArrayList &operator=(const CharArrayList &other)
        {
            if (this != &other)
            {
                /* Free memory incase the class instance already exists */
                delete [] charArrayPtr;
                /* Perform the copy */
                numChars = other.numChars;
                capacity = other.capacity;
                charArrayPtr = new char[capacity];
                for (int i = 0; i < numChars; i++)
                {
                    charArrayPtr[i] = other.charArrayPtr[i];
                }
            }

            return *this;
        }

        /* See CharArrayList.cpp for function contracts */
        bool isEmpty() const;
        void clear();
        int size() const;
        char first() const;
        char last() const;
        char elementAt(int index) const;
        std::string toString() const;
        std::string toReverseString() const;
        void pushAtBack(char c);
        void pushAtFront(char c);
        void insertAt(char c, int index);
        void insertInOrder(char c);

        void popFromFront();
        void popFromBack();
        void removeAt(int index);
        void replaceAt(char c, int index);
        void concatenate(CharArrayList *other);

    private:

        int numChars;
        int capacity;
        char *charArrayPtr;

        /* Expand the capacity by 2x */
        void expand()
        {
            int newCapacity = capacity * 2 + 2;
            char *tempPtr = new char[newCapacity];
            for (int i = 0; i < numChars; i++)
            {
                tempPtr[i] = charArrayPtr[i];
            }
            delete [] charArrayPtr;
            charArrayPtr = tempPtr;
            capacity = newCapacity;

        }

        void expand_specific(int newCapacity)
        {
            char *tempPtr = new char[newCapacity];
            for (int i = 0; i < numChars; i++)
            {
                tempPtr[i] = charArrayPtr[i];
            }
            delete [] charArrayPtr;
            charArrayPtr = tempPtr;
            capacity = newCapacity;

        }

        /* Throw a range error regarding a particular index.
        *  Use endChar to modify the message
        */
        void throw_range_error(int index, char endChar) const
        {
            throw range_error("index (" + 
                       to_string(index) +
                  ") not in range [0.." + 
                      to_string(size()) + endChar);
        }

        void throw_runtime_error(const int mode) const
        {
            switch(mode)
            {
                case RUNTIME_ERROR_FIRST:
                {
                    throw runtime_error("cannot get first of empty ArrayList");
                    break;
                }
                case RUNTIME_ERROR_LAST:
                {
                    throw runtime_error("cannot get last of empty ArrayList");
                    break;
                }
                case RUNTIME_ERROR_POP:
                {
                    throw runtime_error("cannot pop from empty ArrayList");
                    break;
                }
                default:
                {
                    throw runtime_error("generic runtime error");
                    break;
                }
            }

        }

        /* Insert the character and shift every other element down */
        void insert_shift_start_end(char c, int start_index)
        {
            /* Check is the index range is valid*/
            if (start_index < 0 || start_index > (numChars))
            {
                return throw_runtime_error(start_index);
            }

            /* Increase the numChars*/
            numChars++;

            if(numChars >= capacity)
            {
                expand();
            }
            
            /* Insert c at start_index and shift remaining elements */
            for(int i = start_index; i < numChars; i++)
            {
                char temp = charArrayPtr[i];
                charArrayPtr[i] = c;
                c = temp;
            }
        }

        /* Remove the char at the index and shift everything left by one*/
        void remove_and_shift_left(int start_index)
        {
            /* Check is the index range is valid*/
            if (start_index < 0 || start_index > (numChars))
            {
                return throw_range_error(start_index, ')');
            }
            /* Remove the element at start_index, 
               shift remaining elements left */
            for(int i = start_index + 1; i < numChars; i++)
            {
                char temp = charArrayPtr[i];
                charArrayPtr[i-1] = temp;
            }
            
            /* Decrement numChars */
            numChars--;
        }
};

#endif
