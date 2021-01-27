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

std::ostream& operator<< (std::ostream& output, const std::vector<citizen>& live) /*перегрузка оператора для вывода всех жителей*/
{
    for (const auto& i : live)
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

std::ostream& operator<< (std::ostream& output, citizen& live) /*перегрузка оператора для вывода одного жителя*/
{
    output << "Full name: " << live.snp << std::endl;
    output << "Street living: " << live.hmo.street << std::endl;
    output << "House living: " << live.hmo.house_number << std::endl;
    output << "Flat living: " << live.hmo.flat_number << std::endl;
    output << "Gender: " << live.gender << std::endl;
    output << "Age: " << live.age << std::endl;
    return output;
}

std::vector<std::string>& operator>> (std::ifstream& input, std::vector<std::string>& current)
{
    if (!input.is_open())
        std::cout << "File not found";
    else
    {
        std::string result;
        while (!input.eof()) /*пока не дойдет до конца файла*/
        {
            std::getline(input, result);
            current.push_back(result);
        }
    }
    return current;
}

void output_file(std::ofstream& output, const std::vector<citizen>& human, int count)
{
    output << "People list: \n";
    output << human;
    output << std::endl << "Number of people which age is after 18 and before 27 is " << count << std::endl;
}


void bin_out(std::ofstream& output, std::vector<citizen>& human, int count)
{
    for (auto& i : human)
    {
        output.write((char*)&i.snp, sizeof(i.snp));
        output.write((char*)&i.hmo.street, sizeof(i.hmo.street));
        output.write((char*)&i.hmo.house_number, sizeof(i.hmo.house_number));
        output.write((char*)&i.hmo.flat_number, sizeof(i.hmo.flat_number));
        output.write((char*)&i.gender, sizeof(i.gender));
        output.write((char*)&i.age, sizeof(i.age));
    }
    output.write((char*)&count, sizeof(count));
}

void binary_input(std::ifstream& input, std::vector<citizen>& current)
{
    citizen element;
    if (!input.is_open())
        std::cout << "File not found";
    else
    {
        while (!input.eof()) /*пока не дойдет до конца файла*/
        {
            input.read((char*)&element.snp, sizeof(element.snp));
            input.read((char*)&element.hmo.street, sizeof(element.hmo.street));
            input.read((char*)&element.hmo.house_number, sizeof(element.hmo.house_number));
            input.read((char*)&element.hmo.flat_number, sizeof(element.hmo.flat_number));
            input.read((char*)&element.gender, sizeof(element.gender));
            input.read((char*)&element.age, sizeof(element.age));

            current.push_back(element);
        }

        for (auto i : current)
            std::cout << i;
    }
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
    for (int i = 0; i < human.size(); i++)
        for (int j = 0; j < human.size() - i - 1; j++)
            if (human[j].snp > human[j + 1].snp)
            {
                auto t = human[j];
                human[j] = human[j + 1];
                human[j + 1] = t;
            }

    // finding number of people
    int k = 0;
    for (int i = 0; i < human.size(); i++)
        if ((human[i].age >= 18) && (human[i].age <= 27) && (human[i].gender == "male"))
            k++;

    // writing file
    std::ofstream OutputFile("Text.txt", std::ios::out);
    output_file(OutputFile, human, k);
    for (int i = 0; i < 4; i++)
        if ((human[i].age >= 18) && (human[i].age <= 27) && (human[i].gender == "male"))
            OutputFile << human[i];
    OutputFile.close();

    // read file
    std::vector<std::string> vec_for_input;
    std::cout << "Reading text from file: \n";
    std::cout << "=======================================\n";
    std::ifstream InputFile("Text.txt", std::ios::in);
    InputFile >> vec_for_input;            /*считаем каждую сторку в ячеку созданного вектора, затем выведем его на экран*/
    for (auto i : vec_for_input)
        std::cout << i << std::endl;
    InputFile.close();
    std::cout << "=======================================\n";

    // writing binary
    std::ofstream BinaryOutput("Binary.txt", std::ios::binary);
    bin_out(BinaryOutput, human, k);
    BinaryOutput.close();

    // reading binary
    std::vector<citizen> current;
    std::cout << "Reading text in binary mode from file: \n";
    std::cout << "=======================================\n";
    std::ifstream BinaryInput("Binary.txt", std::ios::binary);
    binary_input(BinaryInput, current);
    BinaryInput.close();
    std::cout << "=======================================\n";

    return 0;
}
