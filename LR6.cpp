﻿/* LR6 // VARIANT_16 */

#include <iostream>
#include <string>
#include <vector>

struct address
{
    std::string street;
    int house_number;
    int flat_number;
};

struct citizen
{
    std::string snp; // surname name patronymic
    address hmo; // housing maintenance office 
    std::string gender;
    int age;
};

void swap (std::string& a, std::string& b)
{
    std::string t = a;
    a = b;
    b = t;
}

int main()
{
    std::vector <citizen> human (4);
    human[0] = {"Ivanon Ivan Ivanovich", "World's street", 50, 12, "male", 25 };
    human[1] = {"Pupkin Vasily Sergeevich", "Baker street", 62, 35, "male", 60 };
    human[2] = {"Vasileva Viktoria Pavlovna", "Tverskaya street", 31, 7, "female", 37 };
    human[3] = {"Krasnova Maria Alecksandrova", "Nikolskaya street", 91, 80, "female", 17};
    
    for (int i = 0; i < 4; i++) // sorting names
        for (int j = 0; j < 4 - i - 1; j++)
            swap (snp[j], snp[j + 1];
}
