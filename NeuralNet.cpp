#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>


//overloads * operator to multiply vectors
std::vector<double> operator* (std::vector<double> a, std::vector<double> b)
{
    //creates new vector
    std::vector<double> newVect;

    //times each value by the corresponding value
    for (int i = 0; i < a.size(); i++)
    {
        newVect.push_back(a[i] * b[i]);
    }

    return newVect;
}

//overloads * operator to multiply vectors and matrices
std::vector<std::vector<double>> operator* (std::vector<double> a, std::vector<std::vector<double>> b)
{
    //creates new vector
    std::vector<double> newVect;
    std::vector<std::vector<double>> newMultiVect;

    //times each value by the corresponding value
    for (int i = 0; i < b[0].size(); i++)
    {
        newVect.clear();
        for (int j = 0; j < b.size(); j++)
        {
            newVect.push_back(a[j] * b[j][i]);
        }
        newMultiVect.push_back(newVect);
    }

    return newMultiVect;
}

//overloads - operator to subtract vectors
std::vector<double> operator- (std::vector<double> a, std::vector<double> b)
{
    //creates new vector
    std::vector<double> newVect;

    //times each value by the corresponding value
    for (int i = 0; i < a.size(); i++)
    {
        newVect.push_back(a[i] - b[i]);
    }

    return newVect;
}

//overloads - operator to subtract vectors
std::vector<double> operator- (double a, std::vector<double> b)
{
    //creates new vector
    std::vector<double> newVect;

    //times each value by the corresponding value
    for (int i = 0; i < b.size(); i++)
    {
        newVect.push_back(a - b[i]);
    }

    return newVect;
}

//overloads - operator to subtract vectors
std::vector<double> operator* (double a, std::vector<double> b)
{
    //creates new vector
    std::vector<double> newVect;

    //times each value by the corresponding value
    for (int i = 0; i < b.size(); i++)
    {
        newVect.push_back(a * b[i]);
    }

    return newVect;
}

//overloads + operator to add vectors and matrices
std::vector<std::vector<double>> operator+ (double a, std::vector<std::vector<double>> b)
{
    //times each value by the corresponding value
    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < b[0].size(); j++)
        {
            b[i][j] = b[i][j] + a;
        }
    }

    return b;
}

//overloads + operator to add vectors and matrices
std::vector<std::vector<double>> operator* (double a, std::vector<std::vector<double>> b)
{
    //times each value by the corresponding value
    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < b[0].size(); j++)
        {
            b[i][j] = b[i][j] * a;
        }
    }

    return b;
}

//overloads + operator to add vectors and matrices
std::vector<std::vector<double>> operator+ (std::vector<double> a, std::vector<std::vector<double>> b)
{
    //times each value by the corresponding value
    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < b[0].size(); j++)
        {
            b[i][j] = b[i][j] + a[i];
        }
    }

    return b;
}

//overloads + operator to add vectors and matrices
std::vector<std::vector<double>> operator+ (std::vector<std::vector<double>> a, std::vector<std::vector<double>> b)
{
    //times each value by the corresponding value
    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < b[0].size(); j++)
        {
            b[i][j] = b[i][j] + a[i][j];
        }
    }

    return b;
}


class NeuralNetwork
{
    private:
        //gets number vector from file
        std::vector<double> getNum(std::string fileName, int lineNo)
        {
            //opens file
            std::fstream file;
            file.open(fileName);

            for (int i = 0; i <= lineNo; i++)
            {
                std::string place;
                std::getline(file, place);
            }

            //gets line and saves it to string
            std::string line;
            std::getline(file, line);

            //makes string vector
            std::vector<std::string> values_string;

            //splits string with commas and adds it to the vector
            std::string split;
            std::istringstream ss(line);

            while (std::getline(ss, split, ','))
            {
                values_string.push_back(split);
            }

            //makes int vector
            std::vector<double> values;

            //converts every element to doubles and makes them a %
            for (int i = 0; i < values_string.size(); i++)
            {
                std::stringstream ints(values_string[i]);

                double temp;
                ints >> temp;

                if (i != 0)
                {
                    //normalises values
                    temp = temp / 255 == 0 ? 0.01 : temp / 255 * 0.99;
                }
                
                values.push_back(temp);
            }

            file.close();

            return values;
        }

    public:
        //initializes variables
        std::vector<double> values;
        std::vector<double> hidden;
        std::vector<double> output;
        int correct;
        int iNode;
        int hNode;
        int oNode;

        //creates synapse matrices
        std::vector<std::vector<double>> ih_weight;
        std::vector<std::vector<double>> ho_weight;

        //constructor function (like __init__)
        NeuralNetwork(int iNodes, int hNodes, int oNodes)
        {
            //sets variables
            iNode = iNodes;
            hNode = hNodes;
            oNode = oNodes;
            
            //populates matrices with random nums
            //ih
            for (int i = 0; i < hNode; i++)
            {
                std::vector<double> place;
                for (int j = 0; j < iNode; j++)
                {
                    double random = std::rand() % 100;
                    if (random / 100 == 0)
                    {
                        place.push_back(0.01);
                    }
                    else
                    {
                        place.push_back(random / 100 -0.5);;
                    }
                }
                ih_weight.push_back(place);
            }
            //ho
            for (int i = 0; i < oNode; i++)
            {
                std::vector<double> place;
                for (int j = 0; j < hNode; j++)
                {
                    double random = std::rand() % 100;
                    if (random / 100 == 0)
                    {
                        place.push_back(0.01);
                    }
                    else
                    {
                        place.push_back(random / 100 -0.5);
                    }
                }
                ho_weight.push_back(place);
            }
        }

        //print number function
        void printNum(int index, std::string file)
        {
            std::vector<double> values2 = getNum(file, index);
            values2.erase(values2.begin());

            //initialises square characters
            char whiteSquare = 219;
            char blackSquare = ' ';

            //for i in row
            for (int i = 0; i <= 28; i++)
            {
                //for j in collumn
                for (int j = 0; j <= 28; j++)
                {
                    //if value is less than 0.5 then its white else its black
                    if (values2[i * 28 + j] < 0.5)
                    {
                        std::cout << whiteSquare;
                        std::cout << whiteSquare;
                    }
                    else
                    {
                        std::cout << blackSquare;
                        std::cout << blackSquare;
                    }
                }
                std::cout << "\n";
            }
        }
        
        //runs through the nn and returns the result vector
        std::vector<double> calculate(int index, std::string file)
        {
            values.clear();
            correct = 1;
            values = getNum(file, index);
            correct = values[0];
            values.erase(values.begin());

            hidden.clear();
            output.clear();

            //sums up each node
            for (int i = 0; i < hNode; i++)
            {
                std::vector<double> temp;
                temp = values * ih_weight[i];

                double acc = 0;

                for (double i : temp)
                {
                    acc = acc + i;
                }

                acc = acc / (1 + abs(acc));

                hidden.push_back(acc);
            }

            //sums up each node
            for (int i = 0; i < oNode; i++)
            {
                std::vector<double> temp;
                temp = hidden * ho_weight[i];

                double acc = 0;

                for (double i : temp)
                {
                    acc = acc + i;
                }

                acc = acc / (1+abs(acc));

                output.push_back(acc);
            }

            return output;
        }
        
        //trains the NN
        void train()
        {
            for (int i = 0; i < 150; i++)
            {
                std::vector<double> output = calculate(i, "mnist_train.csv");

                //printNum(i, "mnist_train.csv");

                std::vector<double> correctOut;

                switch (correct)
                {
                    case 0:
                        correctOut = { 0.99,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01 };
                        break;
                    case 1:
                        correctOut = { 0.01,0.99,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01 };
                        break;
                    case 2:
                        correctOut = { 0.01,0.01,0.99,0.01,0.01,0.01,0.01,0.01,0.01,0.01 };
                        break;
                    case 3:
                        correctOut = { 0.01,0.01,0.01,0.99,0.01,0.01,0.01,0.01,0.01,0.01 };
                        break;
                    case 4:
                        correctOut = { 0.01,0.01,0.01,0.01,0.99,0.01,0.01,0.01,0.01,0.01 };
                        break;
                    case 5:
                        correctOut = { 0.01,0.01,0.01,0.01,0.01,0.99,0.01,0.01,0.01,0.01 };
                        break;
                    case 6:
                        correctOut = { 0.01,0.01,0.01,0.01,0.01,0.01,0.99,0.01,0.01,0.01 };
                        break;
                    case 7:
                        correctOut = { 0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.99,0.01,0.01 };
                        break;
                    case 8:
                        correctOut = { 0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.99,0.01 };
                        break;
                    case 9:
                        correctOut = { 0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.99 };
                        break;
                    default:
                        break;
                }

                for (double i : output)
                {
                    std::cout << i << " ";
                }
                std::cout << "\n";

                std::vector<double> output_error = correctOut - output;

                std::vector<std::vector<double>> hidden_error = output_error * ho_weight;

                ho_weight = 0.3 * ((output_error * output * (1.0 - output)) * hidden) + ho_weight;

                std::vector<std::vector<double>> place = 0.3 * (values * (hidden * (1.0 - hidden) * hidden_error));
                ih_weight =  place  + ih_weight;   
            }
        }
};

int main()
{
    NeuralNetwork nn(784,100,10);
    nn.printNum(50, "mnist_test.csv");

    /*
    //prints ouput vector
    for (double i : nn.calculate(150, "mnist_train.csv"))
    {
        std::cout << i << " ";
    }

    std::cout << "\n";
    */
    nn.train();

    std::vector<double> out = nn.calculate(50, "mnist_test.csv");
    for (double i : out)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}