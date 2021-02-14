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

bool to_vec(std::string& current, std::vector<citizen>& vec, int count)
{
    if (current.find("Full name") != -1)
    {
        int pos = current.find(':');
        current.erase(current.begin(), current.begin() + pos + 2);
        vec[count].snp = current;
        return true;
    }
    else if (current.find("Street living") != -1)
    {
        int pos = current.find(':');
        current.erase(current.begin(), current.begin() + pos + 2);
        vec[count].hmo.street = current;
        return true;
    }
    else if (current.find("House living") != -1)
    {
        int pos = current.find(':');
        current.erase(current.begin(), current.begin() + pos + 2);
        vec[count].hmo.house_number = std::stoi(current);
        return true;
    }
    else if (current.find("Flat living") != -1)
    {
        int pos = current.find(':');
        current.erase(current.begin(), current.begin() + pos + 2);
        vec[count].hmo.flat_number = std::stoi(current);
        return true;
    }
    else if (current.find("Gender") != -1)
    {
        int pos = current.find(':');
        current.erase(current.begin(), current.begin() + pos + 2);
        vec[count].gender = current;
        return true;
    }
    else if (current.find("Age") != -1)
    {
        int pos = current.find(':');
        current.erase(current.begin(), current.begin() + pos + 2);
        vec[count].age = std::stoi(current);
        return true;
    }

    return false;
}

std::vector<citizen>& operator>>(std::ifstream& input, std::vector<citizen>& current)
{
    int current_count = 0;
    int count = 0;

    int size_of_vec = 1;
    current.resize(size_of_vec++);

    if (!input.is_open())
        std::cout << "File not found";
    else
    {
        std::string result;
        do
        {
            std::getline(input, result, '\n');
            
            if (current_count == 6)
            {
                current.resize(size_of_vec++);
                current_count = 0;
                count++;
            }
            else if (to_vec(result, current, count))
                current_count++;

            if (result.find("Nu") != -1)
                break;

        } while (!input.eof()); /*пока не дойдет до конца файла*/

        current.erase(current.begin() + current.size() - 1);

    }
    return current;
}

void output_file(std::ofstream& output, const std::vector<citizen>& human, int count)
{
    output << "People list: \n";
    output << human;
    output << std::endl << "Number of people which age is after 18 and before 27 is " << count << std::endl;
}


void bin_out(std::ofstream& output, std::vector<citizen>& human)
{
    if (output.is_open())
    {
        int citizen_size = human.size(); 
        output.write(reinterpret_cast<char*>(&citizen_size), sizeof(citizen_size));    /*запишу в файл количество жителей*/

        for (auto& i : human)
        {
            int size1 = i.snp.size();
            output.write(reinterpret_cast<char*>(&size1), sizeof(size1));              /*пишу в файл размер строки*/
            output.write(i.snp.c_str(), size1 * sizeof(char));                         /*затем саму строку*/

            int size2 = i.hmo.street.size();
            output.write(reinterpret_cast<char*>(&size2), sizeof(size2));
            output.write(i.hmo.street.c_str(), size2 * sizeof(char));

            output.write(reinterpret_cast<char*>(&i.hmo.house_number), sizeof(int));    /*просто пишу число, т.к. у типа инт константный размер*/

            output.write(reinterpret_cast<char*>(&i.hmo.flat_number), sizeof(int));

            int size5 = i.gender.size();
            output.write(reinterpret_cast<char*>(&size5), sizeof(size5));
            output.write(i.gender.c_str(), size5 * sizeof(char));

            output.write(reinterpret_cast<char*>(&i.age), sizeof(int));
        }
    }
}

void binary_input(std::ifstream& input, std::vector<citizen>& current)
{
    if (!input.is_open())
        std::cout << "File not found";
    else
    {

        int citizen_num = 0;
        input.read(reinterpret_cast<char*>(&citizen_num), sizeof(int));      /*считываю количество жителей*/

        for (int i = 0; i < citizen_num; i++)
        {
            citizen people;

            int num1 = 0;
            input.read(reinterpret_cast<char*>(&num1), sizeof(int));         /*читаю размер строки*/
            people.snp.resize(num1);                                         /*изменяю размер строки*/
            input.read(people.snp.data(), num1);                             /*считываю строку*/

            int num2 = 0;
            input.read(reinterpret_cast<char*>(&num2), sizeof(int));
            people.hmo.street.resize(num2);
            input.read(people.hmo.street.data(), num2);

            input.read(reinterpret_cast<char*>(&people.hmo.house_number), sizeof(int));     /*считываю число*/

            input.read(reinterpret_cast<char*>(&people.hmo.flat_number), sizeof(int));

            int num5 = 0;
            input.read(reinterpret_cast<char*>(&num5), sizeof(int));
            people.gender.resize(num5);
            input.read(people.gender.data(), num5);

            input.read(reinterpret_cast<char*>(&people.age), sizeof(int));

            current.push_back(people);
        }

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
    std::vector<citizen> vec_for_input;
    std::cout << "Reading text from file: \n";
    std::cout << "=======================================\n";
    std::ifstream InputFile("Text.txt", std::ios::in);
    InputFile >> vec_for_input;

    for (int i = 0; i < vec_for_input.size(); i++)
        std::cout << vec_for_input[i];

    InputFile.close();
    std::cout << "=======================================\n";

    // writing binary
    std::ofstream BinaryOutput("Binary.txt", std::ios::binary);
    bin_out(BinaryOutput, human);
    BinaryOutput.close();

    // reading binary
    std::vector<citizen> current;
    std::cout << "Reading text in binary mode from file: \n";
    std::cout << "=======================================\n";
    std::ifstream BinaryInput("Binary.txt", std::ios::binary);
    binary_input(BinaryInput, current);

    std::cout << current;

    BinaryInput.close();
    std::cout << "=======================================\n";

    return 0;
}
