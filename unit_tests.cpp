/*
 * unit_tests.cpp
 *
 * CS 15 homework 1
 * by Tyler Calabrese, January 2021
 *
 * edited by: Milod Kazerounian, January 2022
 *
 * Example unit tests framework to test the CharArrayList class.
 *
 */

#include "CharArrayList.h"
#include <iostream>
#include <string>
#include <cassert>

/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/

/* To give an example of thorough testing, we are providing
 * the unit tests below which test the insertAt function. Notice: we have
 * tried to consider all of the different cases insertAt may be
 * called in, and we test insertAt in conjunction with other functions!
 *
 * You should emulate this approach for all functions you define.
 */

char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";

// Tests correct insertion into an empty AL.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct()
{
    CharArrayList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');
}

// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect()
{
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
    // insertAt for out-of-range index
    test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list()
{
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');

}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list()
{
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements()
{

    CharArrayList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
}

// Tests insertion into front of a larger list
void insertAt_front_large_list()
{

    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    test_list.insertAt('y', 0);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(0) == 'y');
    assert(test_list.toString() ==
    "[CharArrayList of size 9 <<yabcdefgh>>]");

}

// Tests insertion into the back of a larger list
void insertAt_back_large_list()
{
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    test_list.insertAt('x', 8);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(8) == 'x');
    assert(test_list.toString() ==
    "[CharArrayList of size 9 <<abcdefghx>>]");

}

// Tests insertion into the middle of a larger list
void insertAt_middle_large_list()
{
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    test_list.insertAt('z', 3);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(3) == 'z');
    assert(test_list.toString() ==
    "[CharArrayList of size 9 <<abczdefgh>>]");

}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect()
{

    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
}

// Test Copy Constructor
void CharArrayList_copy_constructor()
{
    char test_arr1[] = "Enterprise";
    CharArrayList test_list1(test_arr1, 10);

    assert(test_list1.toString() == 
    "[CharArrayList of size 10 <<Enterprise>>]");

    CharArrayList test_list2(test_list1);

    assert(test_list2.toString() == 
    "[CharArrayList of size 10 <<Enterprise>>]");
}

// Test Copy Constructor Operator Overload()
void CharArrayList_copy_constructor_overload()
{

    CharArrayList test_list1(ALPHABET, 26);

    assert(test_list1.toString() == 
    "[CharArrayList of size 26 <<abcdefghijklmnopqrstuvwxyz>>]");
    assert(test_list1.size() == 26);
    assert(test_list1.first() == 'a');
    assert(test_list1.last() == 'z');

    CharArrayList test_list2 = test_list1;

    assert(test_list2.toString() == 
    "[CharArrayList of size 26 <<abcdefghijklmnopqrstuvwxyz>>]");
    assert(test_list2.size() == 26);
    assert(test_list2.first() == 'a');
    assert(test_list2.last() == 'z');

}

// Check if isEmpty is working
void isEmpty_test()
{
    CharArrayList emptyList;
    assert(emptyList.isEmpty() == true);

    CharArrayList test_list('N');
    assert(test_list.isEmpty() == false);
}

// Test if clear is working
void clear_test()
{
    CharArrayList test_list(ALPHABET, 26);

    assert(test_list.toString() == 
    "[CharArrayList of size 26 <<abcdefghijklmnopqrstuvwxyz>>]");

    test_list.clear();
    assert(test_list.isEmpty() == true);
    assert(test_list.size() == 0);
    assert(test_list.toString() == 
    "[CharArrayList of size 0 <<>>]");
}

// Test if public method size() is working as expected
// Try three different array list sizes
void size_test()
{
    CharArrayList listSize_0;
    CharArrayList listSize_256;
    CharArrayList listSize_1024;

    for (int i = 0; i < 256; i++)
    {
        listSize_256.pushAtBack('z');
    }

        for (int i = 0; i < 1024; i++)
    {
        listSize_1024.pushAtBack('z');
    }

    assert(listSize_0.isEmpty() == true);
    assert(listSize_0.size() == 0);

    assert(listSize_256.isEmpty() == false);
    assert(listSize_256.size() == 256);

    assert(listSize_1024.isEmpty() == false);
    assert(listSize_1024.size() == 1024);
}

// Test if public methods first() and last() are working on the alphabet
void first_last_test_alphabet()
{
    CharArrayList alphabet_list(ALPHABET, 26);
    assert(alphabet_list.first() == 'a');
    assert(alphabet_list.last() == 'z');
}

// Test if public methods first() and last() are working ont an empty list
void first_last_test_empty_list()
{
    CharArrayList empty_list;
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try
    {
        empty_list.first();
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot get first of empty ArrayList");

        try
    {
        empty_list.last();
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot get last of empty ArrayList");

}

// Test insertInOrder for and empty list
void insertInOrder_empty_tests()
{
    CharArrayList testList_empty;

    testList_empty.insertInOrder('j');
    assert(testList_empty.toString() == 
    "[CharArrayList of size 1 <<j>>]");
    testList_empty.insertInOrder('a');
    assert(testList_empty.toString() == 
    "[CharArrayList of size 2 <<aj>>]");
    testList_empty.insertInOrder('z');
    assert(testList_empty.toString() == 
    "[CharArrayList of size 3 <<ajz>>]");
    testList_empty.insertInOrder('a');
    assert(testList_empty.toString() == 
    "[CharArrayList of size 4 <<aajz>>]");
    testList_empty.insertInOrder('l');
    assert(testList_empty.toString() == 
    "[CharArrayList of size 5 <<aajlz>>]");
    testList_empty.insertInOrder('z');
    assert(testList_empty.toString() == 
    "[CharArrayList of size 6 <<aajlzz>>]");
}

// Test insertInOrder for a small array list
void insertInOrder_small_tests()
{
    char smallList[] = "ABFG";
    CharArrayList testList_small(smallList, 4);

    testList_small.insertInOrder('a');
    assert(testList_small.toString() == 
    "[CharArrayList of size 5 <<ABFGa>>]");

    testList_small.insertInOrder('z');
    assert(testList_small.toString() == 
    "[CharArrayList of size 6 <<ABFGaz>>]");

    testList_small.insertInOrder('Z');
    assert(testList_small.toString() == 
    "[CharArrayList of size 7 <<ABFGZaz>>]");

    testList_small.insertInOrder('l');
    assert(testList_small.toString() == 
    "[CharArrayList of size 8 <<ABFGZalz>>]");

    testList_small.insertInOrder('L');
    assert(testList_small.toString() == 
    "[CharArrayList of size 9 <<ABFGLZalz>>]");

}

//Test insertInOrder for a larger array list
void insertInOrder_large_tests()
{
    char largeList[] = "abcgjklmprstqy";
    CharArrayList testList_large(largeList, 14);

        assert(testList_large.toString() == 
    "[CharArrayList of size 14 <<abcgjklmprstqy>>]");

    testList_large.insertInOrder('a');
    assert(testList_large.toString() == 
    "[CharArrayList of size 15 <<aabcgjklmprstqy>>]");

    testList_large.insertInOrder('Z');
    assert(testList_large.toString() == 
    "[CharArrayList of size 16 <<Zaabcgjklmprstqy>>]");

    testList_large.insertInOrder('z');
    assert(testList_large.toString() == 
    "[CharArrayList of size 17 <<Zaabcgjklmprstqyz>>]");

    testList_large.insertInOrder('A');
    assert(testList_large.toString() == 
    "[CharArrayList of size 18 <<AZaabcgjklmprstqyz>>]");

    testList_large.insertInOrder('n');
    assert(testList_large.toString() == 
    "[CharArrayList of size 19 <<AZaabcgjklmnprstqyz>>]");

    testList_large.insertInOrder('J');
    assert(testList_large.toString() == 
    "[CharArrayList of size 20 <<AJZaabcgjklmnprstqyz>>]");

}

// Test if popFromBack and popFromFront are working
// Call popFromBack and popFromFront multiple times on the ALPHABET char array
void popFrom_alphabet()
{
    CharArrayList alphabet_list(ALPHABET, 26);

    alphabet_list.popFromBack();
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 25 <<abcdefghijklmnopqrstuvwxy>>]");
    alphabet_list.popFromFront();
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 24 <<bcdefghijklmnopqrstuvwxy>>]");

    alphabet_list.popFromBack();
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 23 <<bcdefghijklmnopqrstuvwx>>]");
    alphabet_list.popFromFront();
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 22 <<cdefghijklmnopqrstuvwx>>]");

    alphabet_list.popFromBack();
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 21 <<cdefghijklmnopqrstuvw>>]");
    alphabet_list.popFromFront();
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 20 <<defghijklmnopqrstuvw>>]");
}

// Call popFromBack and popFromFront and an empty list
void popFrom_empty_list()
{
    CharArrayList empty_list;
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try
    {
        empty_list.popFromBack();
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");

        try
    {
        empty_list.popFromFront();
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "cannot pop from empty ArrayList");
}

//Call elementAt on a CharArrayList that is empty
//Call elementAt on indices <0 and > numChars
void elementAt_invalid_indices()
{
     // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList empty_list;

    try
    {
        assert(empty_list.elementAt(256));
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (256) not in range [0..0)");

    CharArrayList alphabet_list(ALPHABET, 26);
    
    error_message = "";
    try
    {
        assert(alphabet_list.elementAt(26));
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (26) not in range [0..26)");

    error_message = "";
    try
    {
        assert(alphabet_list.elementAt(-1));
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (-1) not in range [0..26)");
    
}

//Call elementAt on valid indices of a CharArrayList
void elementAt_valid_indices()
{
    CharArrayList alphabet_list(ALPHABET, 26);

    assert(alphabet_list.elementAt(0) == 'a');
    assert(alphabet_list.elementAt(1) == 'b');

    assert(alphabet_list.elementAt(13) == 'n');
    assert(alphabet_list.elementAt(14) == 'o');

    assert(alphabet_list.elementAt(24) == 'y');
    assert(alphabet_list.elementAt(25) == 'z');    
}

//Call remove element on invalid indices of a CharArrayList
void removeAt_invalid_indeces()
{
    CharArrayList empty_list;

     // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try
    {
        empty_list.removeAt(0);
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");

    try
    {
        empty_list.removeAt(-1);
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (-1) not in range [0..0)");

    try
    {
        empty_list.removeAt(1);
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (1) not in range [0..0)");

}

//Call removeAt() in valid indices of a CharArrayList
void removeAt_valid_indeces()
{
    CharArrayList alphabet_list(ALPHABET,26);

    alphabet_list.removeAt(25);
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 25 <<abcdefghijklmnopqrstuvwxy>>]");

    alphabet_list.removeAt(0);
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 24 <<bcdefghijklmnopqrstuvwxy>>]");

    alphabet_list.removeAt(12);
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 23 <<bcdefghijklmopqrstuvwxy>>]");

}

//Call replaceAt() on invalid indices of CharArrayList
void replaceAt_invalid_indeces()
{
    CharArrayList empty_list;
    CharArrayList alphabet_list(ALPHABET, 26);

     // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // empty_list tests
    try
    {
        empty_list.replaceAt('T',0);
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");

    try
    {
        empty_list.replaceAt('T',1);
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (1) not in range [0..0)");

    try
    {
        empty_list.replaceAt('T',-1);
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (-1) not in range [0..0)");
    
    //alphabet_list tests
    try
    {
        alphabet_list.replaceAt('T',-1);
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (-1) not in range [0..26)");

    try
    {
        alphabet_list.replaceAt('T',26);
    }
    catch(const std::exception& e)
    {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (26) not in range [0..26)");

}

// Call replaceAt() on valid indices
void replaceAt_valid_indeces()
{
    CharArrayList alphabet_list(ALPHABET, 26);

    alphabet_list.replaceAt('A',0);
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 26 <<Abcdefghijklmnopqrstuvwxyz>>]");

    alphabet_list.replaceAt('J', 9);
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 26 <<AbcdefghiJklmnopqrstuvwxyz>>]");

    alphabet_list.replaceAt('Z', 25);
    assert(alphabet_list.toString() == 
    "[CharArrayList of size 26 <<AbcdefghiJklmnopqrstuvwxyZ>>]");

}

// Test the different conditions for concatenate two list's together
void concatenate_tests()
{
    CharArrayList empty_list;
    
    char array1[] = "PARANOID";
    char array2[] = "android";

    CharArrayList paranoid_list(array1, 8);
    CharArrayList android_list(array2, 7);

    paranoid_list.concatenate(&empty_list);
    assert(paranoid_list.toString() == 
    "[CharArrayList of size 8 <<PARANOID>>]");

    empty_list.concatenate(&android_list);
    assert(empty_list.toString() == 
    "[CharArrayList of size 7 <<android>>]");

    paranoid_list.concatenate(&android_list);
    assert(paranoid_list.toString() == 
    "[CharArrayList of size 15 <<PARANOIDandroid>>]");

}

// Test the toReverseString is working as expected
void toReverseString_test()
{
    char array1[] = "Starship";
    char array2[] = "Enterprise";

    CharArrayList starship_list(array1, 8);
    CharArrayList enterprise_list(array2, 10);
    assert(starship_list.toReverseString() ==
    "[CharArrayList of size 8 <<pihsratS>>]");
    assert(enterprise_list.toReverseString() ==
    "[CharArrayList of size 10 <<esirpretnE>>]");

}
int main()
{
    //Provided tests
    insertAt_empty_correct();
    insertAt_empty_incorrect();
    insertAt_front_singleton_list();
    insertAt_back_singleton_list();
    insertAt_many_elements();
    insertAt_front_large_list();
    insertAt_back_large_list();
    insertAt_middle_large_list();
    insertAt_nonempty_incorrect();

    // My Tests
    CharArrayList_copy_constructor();
    CharArrayList_copy_constructor_overload();
    isEmpty_test();
    clear_test();
    size_test();
    first_last_test_alphabet();
    first_last_test_empty_list();
    insertInOrder_empty_tests();
    insertInOrder_small_tests();
    insertInOrder_large_tests();
    popFrom_alphabet();
    popFrom_empty_list();
    elementAt_invalid_indices();
    elementAt_valid_indices();
    removeAt_invalid_indeces();
    removeAt_valid_indeces();
    replaceAt_invalid_indeces();
    replaceAt_valid_indeces();
    concatenate_tests();
    toReverseString_test();
    return 0;
}
