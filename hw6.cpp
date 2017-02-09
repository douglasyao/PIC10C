/** @file hw6.cpp
 @author Douglas Yao
 @date February 16, 2016
 
 Uses recursion to calculate partitions, Stirling numbers, and factorials for user inputted numbers. Outputs the numbers in separate .txt files.
 */

#include <iostream>
#include <fstream>
#include "binary_integer.h"

binary_integer partition(const int& k, const int& n);
binary_integer stirling1(const int& k, const int& n);
binary_integer stirling2(const int& k, const int& n);
binary_integer factorial(const int& k);

int main() {
    
    binary_integer m;
    std::cout << "Welcome! Please input a number m: ";
    std::cin >> m;
    
    std::cout << std::endl << "Creating Partition.txt file ... ";
    std::ofstream fout("Partition.txt");
    
    // calculates partitions f(k,m) for all k and m values from 1 to m. Outputs values to a .txt file in an mxm grid.
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            fout << partition(i,j) << " ";
        }
        fout << std::endl;
    }
    
    std::cout << "Done." << std::endl;
    
    fout.close();
    
    std::cout << "Creating Stirling1.txt file ... ";
    fout.open("Stirling1.txt");
    
    // calculates Stirling1 numbers f(k,m) for all k and m values from 1 to m. Outputs values to a .txt file in an mxm grid.
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            fout << stirling1(i,j) << " ";
        }
        fout << std::endl;
    }
    
    std::cout << "Done." << std::endl;
    
    fout.close();
    
    std::cout << "Creating Stirling2.txt file ... ";
    fout.open("Stirling2.txt");
    
    // calculates Stirling2 numbers f(k,m) for all k and m values from 1 to m. Outputs values to a .txt file in an mxm grid.
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            fout << stirling2(i,j) << " ";
        }
        fout << std::endl;
    }
    
    std::cout << "Done." << std::endl;
    
    fout.close();
    
    std::cout << "Creating Factorials.txt file ... ";
    fout.open("Factorials.txt");
    
    // calculates factorials for all values from 1 to m. Outputs values to a .txt file.
    for (int i = 1; i <= m; ++i) {
        fout << factorial(i) << std::endl;
    }
    
    std::cout << "Done." << std::endl << std::endl;
    fout.close();
    
    return 0;
}


/** Calculates the partitions for two inputted integers
 @param k is the smaller parameter
 @param n is the larger parameter
 @return the partition as a binary_integer class object
 */
binary_integer partition(const int& k, const int& n) {
    if (k < 0 || n < 0)
        return 0;
    if (k == 0 && n == 0)
        return 0;
    if (k == 0 && n > 0)
        return 0;
    if (k > 0 && n == 0)
        return 1;
    if (k > n)
        return partition(n,n);
    while (k >= 1 && n >= k)
        return partition(k,n-k) + partition(k-1,n);
    return 0;
}


/** Calculates the Stirling number (type 1) for two inputted integers
 @param k is the smaller parameter
 @param n is the larger parameter
 @return the Stirling number as a binary_integer class object
 */
binary_integer stirling1(const int& k, const int& n) {
    if (k < 0 || n < 0)
        return 0;
    if (k == 0 && n == 0)
        return 1;
    if (k == 0 && n > 0)
        return 0;
    if (k > 0 && n == 0)
        return 0;
    if (k > n)
        return 0;
    while (k >= 1 && n >= k)
        return -(n-1)*stirling1(k,n-1) + stirling1(k-1,n-1);
    return 0;
}


/** Calculates the Stirling number (type 2) for two inputted integers
 @param k is the smaller parameter
 @param n is the larger parameter
 @return the Stirling number as a binary_integer class object
 */
binary_integer stirling2(const int& k, const int& n) {
    if (k < 0 || n < 0)
        return 0;
    if (k == 0 && n == 0)
        return 1;
    if (k == 0 && n > 0)
        return 0;
    if (k > 0 && n == 0)
        return 0;
    if (k > n)
        return 0;
    while (k >= 1 && n >= k)
        return k*stirling2(k,n-1) + stirling2(k-1,n-1);
    return 0;
}


/** Calculates the factorial of an integer
 @param k is the integer
 @return the factorial as a binary_integer class object
 */
binary_integer factorial (const int& k) {
    binary_integer factorial(1);
    for (int i = 1; i <= k; ++i) {
        factorial *= i;
    }
    return factorial;
}

