#include <iostream>
#include <vector>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//ptr template is for the lambda function that gives the boolean to choose how to sort it
template <typename type, class ptr>
void quickSort(typename std::vector<type>& arr, int low, int high, ptr condition)
{
    //while the length of the part > 1
    if (low < high)
    {
        //end = end of the lhs
        int end = (low - 1);
        //goes through each each value in the array
        for (int i = low; i < low + (high - low); i++)
        {
            //if its lower than the pivot
            if (condition(arr[i], arr[high]))
            {
                //lhs increases in size
                end++;
                //swaps the current value with the last value that should be on the rhs
                std::swap(arr[i], arr[end]);
            }
        }

        //swaps pivot with 1 after the lhs
        std::swap(arr[end + 1], arr[high]);
        //sorts lhs
        quickSort(arr, low, end, condition);
        //sorts rhs
        quickSort(arr, end + 2, high, condition);
    }
}

//function overload for default sort (low to high)
template <typename type>
void quickSort(typename std::vector<type>& arr, int low, int high) {
    quickSort(arr, low, high, [](type a, type b) { return (a <= b); });
}

//function overload for no low and high vars
template <typename type>
void quickSort(typename std::vector<type>& arr) {
    quickSort(arr, 0, arr.size()-1, [](type a, type b) { return (a <= b); });
}

template <typename type, class ptr>
void quickSort(typename std::vector<type>& arr, ptr command) {
    quickSort(arr, 0, arr.size() - 1, command);
}

//fills a vector with random numbers
void createRandVect(std::vector<int>& target, int length, int range)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i <= length; i++)
    {
        target.push_back(rand() % (range + 1));
    }
}

//overload for doubles
void createRandVect(std::vector<double>& target, int length, int range)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i <= length; i++)
    {
        target.push_back((double)(rand() % ((range * 100) + 1)) / 100.0);
    }
}

//struct to test the ability to sort by certain attributes
struct person
{
    std::string name;
    int age;
    person(int age, std::string name)
    {
        this->age = age;
        this->name = name;
    }
};

int main() {
    std::vector<int> a;
    int length = 10000;
    int range = 10000;
    createRandVect(a, length, range);

    auto start = std::chrono::high_resolution_clock::now();

    quickSort(a);

    auto finish = std::chrono::high_resolution_clock::now();
    /*priting data*/ {
        auto elapsedS = std::chrono::duration_cast<std::chrono::seconds>(finish - start);
        auto elapsedM = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
        auto elapsedU = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
        auto elapsedN = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

        std::cout << "List length: " << length << "\nList range: " << range << "\n";
        std::cout << elapsedS.count() << " seconds\n";
        std::cout << elapsedM.count() << " milliseconds\n";
        std::cout << elapsedU.count() << " microseconds\n";
        std::cout << elapsedN.count() << " nanoseconds\n";
        
        for (double i : a)
        {
            std::cout << i << " ";
        }
    }

    std::cout << "\n\n\n\n\n\n\n";

    std::vector<int> b;
    length = 10000;
    range = 1000;
    createRandVect(b, length, range);

    std::vector<person> testVect;

    for (int i = 0; i < length; i++) testVect.push_back(person(b[i], "Sam " + std::to_string(i)));

    start = std::chrono::high_resolution_clock::now();

    //quick sort using the age of the person (given as a boolean by a lambda function)
    quickSort(testVect, [](person a, person b) { return (a.age <= b.age); });

    finish = std::chrono::high_resolution_clock::now();

    /*priting data*/ {
        auto elapsedS = std::chrono::duration_cast<std::chrono::seconds>(finish - start);
        auto elapsedM = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
        auto elapsedU = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
        auto elapsedN = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

        std::cout << "List length: " << length << "\nList range: " << range << "\n";
        std::cout << elapsedS.count() << " seconds\n";
        std::cout << elapsedM.count() << " milliseconds\n";
        std::cout << elapsedU.count() << " microseconds\n";
        std::cout << elapsedN.count() << " nanoseconds\n";

        for (person i : testVect)
        {
            std::cout << i.name << ", age: " << i.age << " ";
        }
    }

    //stops cmd from exiting
    char temp;
    std::cin >> temp;
}