#include <math.h>
#include <stdbool.h>
#include "prime.h"

/**
 * @brief Return whether x is prime or not
 * 
 * @param x Number to be checked
 * @return true x is a prime
 * @return false x is not a prime
 */
bool isPrime(const int x){
    if(x <= 1) {return false;}
    if(x == 2) {return true;}
    if((x % 2) == 0) {return false;}

    for(int i = 3; i <= floor(sqrt((double) x)); i += 2){
        if((x % i) == 0){
            return false;
        }
    }
    return true;
}

/**
 * @brief Return the next prime after x, or x if x is prime
 * 
 * @param x Number from which we start searching for the prime number
 * @return int Return the nearest next prime number
 */
int nextPrime(int x){
    while (isPrime(x) != true){
        x++;
    }
    return x;
}