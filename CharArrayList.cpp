/*
 *  CharArrayList.cpp
 *  Naveed Naeem
 *  UTLN: nnaeem01
 *  DATE CREATED: 06/03/2023
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Purpose: Function Definitions for the CharArrayList Class
 */

#include <iostream>
#include "CharArrayList.h"

using namespace std;

/*
 * name:      CharArrayList default constructor
 * purpose:   initialize an empty CharArrayList
 * arguments: none
 * returns:   none
 * effects:   numChars to 0 (also updates capacity and data array)
 */
CharArrayList::CharArrayList()
{
    numChars = 0;
    capacity = 0;
    charArrayPtr = nullptr;
}

/*
 * name:      CharArrayList second constructor
 * purpose:   Initializes a CharArrayList with 1
 * arguments: A character to start the array
 * returns:   none
 * effects:   numChars = 1, capacity = 1
 */
CharArrayList::CharArrayList(char c)
{
    numChars = 1;
    capacity = 1;
    charArrayPtr = new char[capacity];
    charArrayPtr[0] = c;
}

/*
 * name:      CharArrayList third constructor
 * purpose:   Initializes a CharArray list with an array of characters
 * arguments: A char array and the size of the array
 * returns:   none
 * effects:   numChars = size, capacity = size, CharArrayList = arr
 */
CharArrayList::CharArrayList(char arr[], int size)
{
    numChars = size;
    capacity = size;
    charArrayPtr = new char[capacity];
    for (int i = 0; i < size; i++)
    {
        charArrayPtr[i] = arr[i];
    }
}

/*
 * name:      CharArrayList copy constructor
 * purpose:   Initializes a new CharArrayList with all values of the input
 *            CharArrayList
 * arguments: A char array and the size of the array
 * returns:   none
 * effects:   numChars = size, capacity = size, CharArrayList = arr
 */
CharArrayList::CharArrayList(const CharArrayList &other)
{
    numChars = other.numChars;
    capacity = other.capacity;
    charArrayPtr = new char[capacity];
    for (int i = 0; i < numChars; i++)
    {
        charArrayPtr[i] = other.charArrayPtr[i];
    }
}

/*
 * name:      CharArrayList destructor
 * purpose:   Frees the CharArrayList memory
 * arguments: none
 * returns:   none
 * effects:   Frees the memory for this CharArraylist
 */
CharArrayList::~CharArrayList()
{
    delete [] charArrayPtr;
    numChars = 0;
    charArrayPtr = nullptr;
}

/*
 * name:      isEmpty()
 * purpose:   Returns true if numChars = 0, false otherwise
 * arguments: none
 * returns:   none
 * effects:   none
 */
bool CharArrayList::isEmpty() const
{
    return (numChars == 0) ? true : false;
}

/*
 * name:      clear()
 * purpose:   Sets the numChars = 0
 * arguments: none
 * returns:   none
 * effects:   Sets numChars = 0
 */
void CharArrayList::clear()
{
    numChars = 0;
}

/*
 * name:      size()
 * purpose:   Returns and int containing the number of chars in the list
 * arguments: none
 * returns:   none
 * effects:   none
 */
int CharArrayList::size() const
{
    return numChars;
}

/*
 * name:      first()
 * purpose:   Returns the first char in the list if it's not empty
 * arguments: none
 * returns:   none
 * effects:   none
 */
char CharArrayList::first() const
{
    if(!isEmpty())
    {
        return charArrayPtr[0];
    }
    else
    {
        throw_runtime_error(RUNTIME_ERROR_FIRST);
        return (char)-1;
    }
}

/*
 * name:      last()
 * purpose:   Returns the last char in the list if it's not empty
 * arguments: none
 * returns:   none
 * effects:   none
 */
char CharArrayList::last() const
{
    if(!isEmpty())
    {
        return charArrayPtr[(numChars - 1)];
    }
    else
    {
        throw_runtime_error(RUNTIME_ERROR_LAST);
        return (char)-1;
    }
}

/*
 * name:      elementAt()
 * purpose:   Returns the element at the index provided if it's a valid index
 * arguments: int index: Index to access in the array
 * returns:   The desired character
 * effects:   none
 */
char CharArrayList::elementAt(int index) const
{
    if ((index >= 0) && (index < numChars) && (charArrayPtr != nullptr))
    {
        return charArrayPtr[index];
    }
    else
    {
        throw_range_error(index, ')');
        return (char)-1;
    }
}

/*
 * name:      toString()
 * purpose:   Returns the chars as a string in a formatted message
 * arguments: none
 * returns:   A string in the following format:
 *            [CharArrayList of size numChars <<string>>]
 * effects:   none
 */
string CharArrayList::toString() const
{

    string outputStr = "[CharArrayList of size " +
                        to_string(numChars) +
                        " <<";

    string charArrayStr = "";
    for (int i = 0; i < numChars; i++)
    {
        charArrayStr += charArrayPtr[i];
    }
    outputStr += charArrayStr + ">>]";
    return outputStr;
}

/*
 * name:      toReverseString()
 * purpose:   Returns the chars in reverse as a string in a formatted message
 * arguments: none
 * returns:   A string in the following format:
 *            [CharArrayList of size numChars <<string>>]
 * effects:   none
 */
string CharArrayList::toReverseString() const
{
    string outputStr = "[CharArrayList of size " +
                        to_string(numChars) +
                        " <<";

    string charArrayStr = "";
    /* Loop from the back of the array */
    for (int i = (numChars - 1); i >= 0; i--)
    {
        charArrayStr += charArrayPtr[i];
    }
    outputStr += charArrayStr + ">>]";
    return outputStr;
}

/*
 * name:      pushAtBack()
 * purpose:   Insert the provided character at the end of the list
 * arguments: char c: The character that is being pushed
 * returns:   none
 * effects:   Inserts the input character at the end of the list
*/
void CharArrayList::pushAtBack(char c)
{
    if (charArrayPtr == nullptr)
    {
        charArrayPtr = new char[1];
        charArrayPtr[0] = c;
        numChars = 1;
        capacity = 1;
        return;
    }

    /* If capacity == numChars expand the memory*/
    if(numChars == capacity)
    {
        expand();
    }

    /* Insert the char into the last array index */
    charArrayPtr[numChars] = c;
    numChars++;
}

/*
 * name:      pushAtFront()
 * purpose:   Insert the provided character at the front of the list
 * arguments: char c: The character that is being pushed
 * returns:   none
 * effects:   Inserts the input character at the front of the list
 */
void CharArrayList::pushAtFront(char c)
{
    /* Functionality is identical to pushAtBack if charArrayPtr = nullptr*/
    if (charArrayPtr == nullptr)
    {
        pushAtBack(c);
        return;
    }

    /* If capacity == numChars expand the memory*/
    if(numChars == capacity)
    {
        expand();
    }

    /* Insert the new character */
    insert_shift_start_end(c, 0);
}

/*
 * name:      insertAt()
 * purpose:   Insert the provided character at the provided index
 * arguments: char c: Input Character
 *            int index: The desired index to place char c
 * returns:   none
 * effects:   Inserts the input character at the front of the list if
 *            the index is valid
 */
void CharArrayList::insertAt(char c, int index)
{
    if(index < 0 || index > numChars)
    {
        throw_range_error(index, ']');
        return;
    }

    /* If charArrayPtr is nullPtr just call pushAtBack and return*/
    if (charArrayPtr == nullptr)
    {
        return pushAtBack(c);
    }

    /* Check if the capacity needs to be updated */
    if (numChars == capacity)
    {
        expand();
    }

    /* If the index is after the last element*/
    if(numChars == index)
    {
        /* Push c to then end of the array list */
        pushAtBack(c);
        return;
    }

    /* Insert the new character at the desired index */
    insert_shift_start_end(c, index);
}

/*
 * name:      insertInOrder()
 * purpose:   Insert the provided character in ASCII order. 
 *            NOTE!!! Assumes list is already sorted
 * arguments: char c: Input Character
 * returns:   none
 * effects:   Inserts the input character in ASCII order
 */
void CharArrayList::insertInOrder(char c)
{
    /* If numChars == 0, call pushAtFront */
    if (numChars == 0)
    {
        return pushAtFront(c);
    }
    /* Insert the character */
    else
    {
        /* Keep track of the index to insert char c at */
        int insertIdx = 0;
        /* Loop through the characters until we find a character */
        while((insertIdx < numChars) && (c > charArrayPtr[insertIdx]))
        {
            /* Increment insertIdx*/
            insertIdx++;
        }

        /* If insertIdx == numChars, call pushAtBack */
        if(insertIdx == (numChars))
        {
            return pushAtBack(c);
        }
        if(insertIdx == 0)
        {
            return pushAtFront(c);
        }
        return insert_shift_start_end(c, insertIdx);
    }
}

/*
 * name:      popFromFront()
 * purpose:   Remove the front element of the list and shift
 *            shift everything to the left
 * arguments: none
 * returns:   none
 * effects:   Removes the first element of the list
 */
void CharArrayList::popFromFront()
{
    if (numChars == 0)
    {
        throw_runtime_error(RUNTIME_ERROR_POP);
    }
    if (numChars == 1)
    {
        popFromBack();
    }
    /* Remove the first element, shift everything left by one*/
    remove_and_shift_left(0);
}

/*
 * name:      popFromBack()
 * purpose:   Remove the last element in the list by decrementing numChars
 * arguments: none
 * returns:   none
 * effects:   Decrements numChars effectively removing the 
 *            last element in the list
 */
void CharArrayList::popFromBack()
{
    if (numChars == 0)
    {
        throw_runtime_error(RUNTIME_ERROR_POP);
    }
    /* Decrement numChars */
    numChars--;
}

/*
 * name:      removeAt()
 * purpose:   Remove the desired element in the list,
 *            shift elements to the right to the left by one
 * arguments: int index: The index to remove the value from
 * returns:   none
 * effects:   Decrements numChars effectively removing the 
 *            last element in the list
 */
void CharArrayList::removeAt(int index)
{
    if (charArrayPtr == nullptr)
    {
        return throw_range_error(index, ')');
    }
    remove_and_shift_left(index);
}

/*
 * name:      replaceAt()
 * purpose:   Replace the value at the index with the desired character
 * arguments: int index: The index to place the desired character
 *            char c: The character value to insert at the index
 * returns:   none
 * effects:   Replaces the character at the input index with the 
 *            desired character 
 */
void CharArrayList::replaceAt(char c, int index)
{
    if (index < 0 || index >= (numChars) || numChars == 0)
    {
        return throw_range_error(index, ')');
    }

    charArrayPtr[index] = c;
}

/*
 * name:      concatenate()
 * purpose:   Adds a copy of the array list provided as the input to the end
 *            of the current array list
 * arguments: CharArrayList *other: Pointer to the CharArrayList to be
 *            concatenated.
 * returns:   none
 * effects:   Appends the input CharArrayList to current CharArrayList 
 */
void CharArrayList::concatenate(CharArrayList *other)
{
    /* If the other CharArrayList is nullptr return, do nothing */
    if (other == nullptr)
    {
        return;
    }

    /* If this CharArrayList is nullptr return, 
    *  copy other into this CharArrayList
    */
    if(charArrayPtr == nullptr)
    {
        this->numChars = other->size();
        this->capacity = other->size();

        charArrayPtr = new char[capacity];
        for (int i = 0; i < numChars; i++)
        {
            charArrayPtr[i] = other->charArrayPtr[i];
        }
        return;
    }

    int newCapacity = capacity + other->size();
    if (capacity < newCapacity)
    {
        /* Expand capacity to the min capacity needed */
        expand_specific(newCapacity);
    }

    /* Add the other CharArrayList to the end of this one */
    for (int i = this->numChars; i < capacity; i++)
    {
        charArrayPtr[i] = other->charArrayPtr[i - numChars];
    }
    numChars = capacity;
    return;
}
