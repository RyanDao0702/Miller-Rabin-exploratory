#include <iostream>
#include <chrono>

//I want to test whether more k times or more bases a tested, producing more accurate results. 
//This raise a question regarding the runtime cost of this benchmark.
//Would the extra tests worth the additional runtime cost since extra tests meaning extra work.

//Use the function in miller-rabin file
bool millerRabin(long long n, int k);

int main() {
    long long n;
    std::cout << "Please choose a number > 2\n";
    std::cin >> n;
    //Create a set of k times for the tests
    int kTimes[] = {1,2,5,10,20,50,100};

    //Imaging this is like a clockdown timer, when I press "start" and run the Miller-Rabin test, then "end", and see what is the runtime cost of this process.

    //Each k time will be repeated 1000 times to test whether there is n that can be both composite and probably prime
    int repitition = 1000;
    

    for (int k : kTimes) {
        //Count how many times it is composite or probably prime
        int compositeCount = 0;
        int probablyPrimeCount = 0;
        
        std::cout << "k = " << k << "\n";
        
        //Begin the clock
        auto begin = std::chrono::high_resolution_clock::now();
        //Declare the result
        bool result;

        //For each k time, repeat it 1000 times
        for (int i = 0; i < repitition; i++) {
            //Run the test
            result = millerRabin(n,k);
            //true == composite
            if (result == true) {
                compositeCount++;
            } 
            else {
            //false == probably prime
                probablyPrimeCount++;
            }
        }
        //stop the clock
        auto end = std::chrono::high_resolution_clock::now();

        //calculate the elasped time
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

        if (result) {
            std::cout << n << " is composite\n";
        }
        else {
            std::cout << n << " is probably prime\n";
        }
        
        std::cout << "Composite count : " << compositeCount << "\n";
        std::cout << "Probably prime count: " << probablyPrimeCount << "\n";
        //As the Miller-Rabin is extremely fast, so reading seconds will be harder than reading microseconds
        std::cout << "Time: " << duration.count() << " microseconds\n"; //this gives the numerical value of duration

        //calculate the average runtime cost between 1000 times to avoid noises and increase accuracy
        double average = static_cast<double> (duration.count()) / repitition; //this gives the runtime cost of each Miller-Rabin test
        std::cout << "Average: " << average << " microseconds\n"; 

        } 
        
    
    return 0;
    
}