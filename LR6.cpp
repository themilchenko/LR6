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

std::ostream& operator<< (std::ofstream& output, const std::vector<citizen>& live)
{
    for(citizen i : live)
    {
        output << "Full name: " << i.snp << std::endl;
        output << "Street living: " << i.hmo.street << std::endl;
        output << "House living: " << i.hmo.house_number << std::endl;
        output << "Flat living: " << i.hmo.flat_number << std::endl;
        output << "Gender: " << i.gender << std::endl;
        output << "Age: " << i.age << std::endl << std::endl;
    }
    return output;
}

std::ostream& operator<< (std::ostream& output, citizen& live)
{
    output << "Full name: " << live.snp << std::endl;
    output << "Street living: " << live.hmo.street << std::endl;
    output << "House living: " << live.hmo.house_number << std::endl;
    output << "Flat living: " << live.hmo.flat_number << std::endl;
    output << "Gender: " << live.gender << std::endl;
    output << "Age: " << live.age << std::endl;
}

std::ifstream& operator>> (std::ifstream& input, const std::vector<citizen> live)
{
    for (auto i : live)
    {
        std::getline(input, i.snp);
        std::getline(input, i.hmo.street);
        input >> i.hmo.house_number;
        input >> i.hmo.flat_number;
        std::getline(input, i.gender);
        input >> i.age;
    }
    return input;
}

int main()
{
    // initialization objects
    citizen first = { "Ivanov Ivan Ivanovich", "World's street", 50, 12, "male", 25 };
    citizen second = { "Pupkin Vasily Sergeevich", "Baker street", 62, 35, "male", 60 };
    citizen third = { "Vasileva Viktoria Pavlovna", "Tverskaya street", 31, 7, "female", 37 };
    citizen fourth = { "Krasnova Maria Alecksandrovna", "Nikolskaya street", 91, 80, "female", 17 };

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

    // finding number of people
    int k = 0;
    for (int i = 0; i < 4; i++)
        if ((human[i].age >= 18) && (human[i].age <= 27) && (human[i].gender == "male"))
            k++;

    // writing file
    std::ofstream OutputFile("Text.txt", std::ios::out);
    OutputFile << "People list: \n";
    OutputFile << human;
    OutputFile << std::endl << "Number of people which age is after 18 and before 27 is " << k << std::endl;
    for (int i = 0; i < 4; i++)
        if ((human[i].age >= 18) && (human[i].age <= 27) && (human[i].gender == "male"))
            OutputFile << human[i];
    OutputFile.close();

    // read file
    std::ifstream input("Text.txt", std::ios::in);
    input >> human;


    // reading binary
    std::ifstream bin_input("Binary.bin", std::ios::binary);
    for (auto& i : human)
    {
        bin_input.read(reinterpret_cast<char*>(&i.snp), sizeof(i.snp));
        bin_input.read(reinterpret_cast<char*>(&i.hmo.street), sizeof(i.hmo.street));
        bin_input.read(reinterpret_cast<char*>(&i.hmo.house_number), sizeof(i.hmo.house_number));
        bin_input.read(reinterpret_cast<char*>(&i.hmo.flat_number), sizeof(i.hmo.flat_number));
        bin_input.read(reinterpret_cast<char*>(&i.gender), sizeof(i.gender));
        bin_input.read(reinterpret_cast<char*>(&i.age), sizeof(i.age));
    }
    bin_input.close();

    // writing binary
    std::ofstream bin_out("Binary.bin", std::ios::binary);
    for (auto& i : human)
    {
        bin_out.write(reinterpret_cast<char*>(&i.snp), sizeof(i.snp));
        bin_out.write(reinterpret_cast<char*>(&i.hmo.street), sizeof(i.hmo.street));
        bin_out.write(reinterpret_cast<char*>(&i.hmo.house_number), sizeof(i.hmo.house_number));
        bin_out.write(reinterpret_cast<char*>(&i.hmo.flat_number), sizeof(i.hmo.flat_number));
        bin_out.write(reinterpret_cast<char*>(&i.gender), sizeof(i.gender));
        bin_out.write(reinterpret_cast<char*>(&i.age), sizeof(i.age));
    }

    return 0;
}
