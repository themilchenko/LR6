/* LR6 // VARIANT_16 */

#include <fstream>
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

int main()
{
    // initialization objects
    citizen first = { "Ivanon Ivan Ivanovich", "World's street", 50, 12, "male", 25 };
    citizen second = { "Pupkin Vasily Sergeevich", "Baker street", 62, 35, "male", 60 };
    citizen third = { "Vasileva Viktoria Pavlovna", "Tverskaya street", 31, 7, "female", 37 };
    citizen fourth = { "Krasnova Maria Alecksandrova", "Nikolskaya street", 91, 80, "female", 17 };

    // adding this objects in vector
    std::vector <citizen> human(4);
    human[0] = first;
    human[1] = second;
    human[2] = third;
    human[3] = fourth;

    // sorting names
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4 - i - 1; j++)
            if (human[j].snp > human[j + 1].snp)
        {
            auto t = human[j];
            human[j] = human[j + 1];
            human[j + 1] = t;
        }

    int k = 0;
    for (int i = 0; i < 4; i++)
        if ((human[i].age >= 18) && (human[i].age <= 27) && (human[i].gender == "male"))
        {
            k++;
            std::cout << "Full name: " << human[i].snp << std::endl;
            std::cout << "Street living: " << human[i].hmo.street << std::endl;
            std::cout << "House living: " << human[i].hmo.house_number << std::endl;
            std::cout << "Flat living:  " << human[i].hmo.flat_number << std::endl;
            std::cout << "Gender: " << human[i].gender << std::endl;
            std::cout << "Age: " << human[i].age << std::endl;
        }
    std::cout << "Numer of people which age is after 18 and before 27 is " << k;

    std::ofstream OutputFile("Text.txt", std::ios::out); // writing file
    OutputFile << "People list: \n";
    for (int i = 0; i < 4; i++) // writing people in sort list
    {
        OutputFile << "Full name: " << human[i].snp << std::endl;
        OutputFile << "Street living: " << human[i].hmo.street << std::endl;
        OutputFile << "House living: " << human[i].hmo.house_number << std::endl;
        OutputFile << "Flat living:  " << human[i].hmo.flat_number << std::endl;
        OutputFile << "Gender: " << human[i].gender << std::endl;
        OutputFile << "Age: " << human[i].age << std::endl << std::endl;
    }
    OutputFile << std::endl << "Numer of people which age is after 18 and before 27 is " << k << std::endl;
    for (int i = 0; i < 4; i++)
        if ((human[i].age >= 18) && (human[i].age <= 27) && (human[i].gender == "male"))
        {
            OutputFile << "Full name: " << human[i].snp << std::endl;
            OutputFile << "Street living: " << human[i].hmo.street << std::endl;
            OutputFile << "House living: " << human[i].hmo.house_number << std::endl;
            OutputFile << "Flat living:  " << human[i].hmo.flat_number << std::endl;
            OutputFile << "Gender: " << human[i].gender << std::endl;
            OutputFile << "Age: " << human[i].age << std::endl << std::endl;
        }
    OutputFile.close();
    return 0;
}
