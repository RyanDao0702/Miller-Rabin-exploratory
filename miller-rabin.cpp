#include <iostream>
#include <random>
#include <chrono>

//A helper function to handle the modular exponentiation

//This accepts inputs a, d, and n
long long modPow(long long a, long long d, long long n) {
    //Declare b0 
    long long b0;
    //This calculate the b0 by gather the powers that sum up d 
    for (b0 = 1; d; d >>= 1) {
        //d must be odd number
        if (d & 1) {
            //This gather the correct powers that sum up d
            b0 = (b0 * a) % n;
        }
        //This will increase the power based on 
        a = (a * a) % n;
    }
    return b0;
}   

//true = composite
//false = probably prime

//This helper function helps keep checking whether the n is the prime or not using witness. 

//This function accepts inputs x (b0), n, s from 2^s * d
bool witness(long long x, long long n, long long s) {
    //Declare bi 
    long long bi = x;
    //This ensures that the test is within s times since 
    for (long long i = 1; i < s; i++) {
        //Repeating square
        bi = (x * x) % n; //30^2 mod 53
        if (bi == 1) {
            return true; //composite
        }
        if (bi == n-1) {
            return false;  //probably prime
        }
        else {
            x = bi; //b1 = x = 5
        }
    }
    //never reach n-1, meaning that is definitely not prime
    return true;
    
}

//true = composite
//false = probably prime

//Miller-Rabin test

//This accepts n and k times
bool millerRabin(long long n, int k) {
    //Edge cases
    //Check n is valid or not
    if (n < 2) {
        return true;
    }
    //Special case where n = 2 and n = 3 since they are primes but 2 % 2 = 0 and 3 % 2 = 0
    if (n == 2 || n == 3) {
        return false;
    }
    if (n % 2 == 0) {
        return true;
    }
    //Let s > 0
    long long s = 1;
    //Compute the first d when s = 1 
    long long d = (n-1) / 2;

    //While d is still even
    while (d % 2 == 0 && d > 0) {
        //Just take d is divided by 2 to get d odd
        d /= 2;
        s++;
    }

    //generate random a between 2 and n-2 since 1 < a < n-1
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> distr(2, n-2);

    //While the test is tested in valid k times
    while (k > 0) {
        //generate random a
        long long a = distr(gen);

        //compute b0
        long long x = modPow(a, d, n);

        //if b0 = n-1 or 1
        if (x == n - 1 || x == 1) {
            //countdown the k times 
            k--;
            //skip continue with other bases a
            continue;
        }
        //if composite = false then skip
        //if composite = true then continuen testing
        if (witness(x, n, s)) {
            return true; //definitely composite
        }
        //countdown the k times
        k--;
    }
    //All k bases passes
    return false;
}

