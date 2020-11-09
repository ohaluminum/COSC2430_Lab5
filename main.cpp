#include <iostream>
#include <fstream>
#include <map>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output" and "command"
    string input = am.get("input");
    string output = am.get("output");

    //Test
    //string input = "input3.txt";
    //string output = "output3.txt";

    ifstream inFS;
    ofstream outFS;

    try
    {
        //Open input file and output file  
        inFS.open(input);
        outFS.open(output);

        //Throw exception if the file doesn't exist
        if (!inFS.is_open())
        {
            throw runtime_error("ERROR: File not found");
        }

        //Throw exception if the file is empty
        if (inFS.peek() == EOF)
        {
            throw runtime_error("ERROR: File is empty");
        }
    }
    catch (runtime_error & e)
    {
        outFS << e.what() << endl;
    }

    int numOfFruit = 0;
    string fruitName = "";

    map<string, int> fruitMap;

    inFS >> numOfFruit;

    //Loop through the fruit list
    for (int i = 0; i < numOfFruit; i++)
    {
        inFS >> fruitName;

        //Find a particular fruit
        auto result = fruitMap.find(fruitName);

        //Fruit is found in the map
        if (result != fruitMap.end())
        {
            //Increase the counter
            result->second += 1;
        }
        //Fruit is not found in the map
        else
        {
            fruitMap[fruitName] = 1;
        }
    }

    //Loop through fruit map
    for (auto i : fruitMap)
    {
        outFS << i.first << ": " << i.second << endl;
    }

    //Close files
    inFS.close();
    outFS.close();

    return 0;
}