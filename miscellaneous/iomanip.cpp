#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

void printFile(const string& ifilename)
{
    ifstream in{ifilename};
    if(in)
    {
        double buf;
        cout << fixed << setprecision(3);
        while(in >> buf)
        {
            cout << buf << endl;
        }
    }
    else
    {
        cout << "Error" << endl;
    }

}

void printTable(const string& csvFileName)
{
    ifstream in{csvFileName};
    if(in)
    {
        size_t rows = 0, columns = 0;
        in >> rows;
        in >> columns;

        for(size_t row = 0; row < rows; row++)
        {
            int new_value;
            for(size_t column = 0; column < columns; column++)
            {
                in >> new_value;
                in.ignore(1);
                cout << setw(10) << new_value;
                if(column < columns -1)
                {
                    cout << " ";
                }
            }
            if(row < rows - 1)
            {
                cout << endl;
            }
        }
    }
    else
    {
        cout << "Error" << endl;
    }

}

int main()
{
   printTable("input.txt");
   /*
      2 3
      1,2,3
      4,5,6
    */
   return 0;
}
