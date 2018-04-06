#include<iostream>
    using std::cout;
    using std::cin;

#include<fstream>
    using std::ifstream;
    using std::ofstream;
    
int main()
{
    ifstream infile ("1000x1000White.bmp");
    ofstream outfile ("1000x1000Green.bmp");
    
    if (infile.is_open())
    {
        for (int  i = 0; i < 54; i++)
        {
            char ch;
            infile.read(&ch, 1);
            outfile.write(&ch, 1);
        }
        
        for (int  i = 0; i < 1000000; i++)
        {
            for (int  j = 0; j < 1; j++)    //B
            {
                char ch;
                infile.read(&ch, 1);
                const char zero = 0;
                outfile.write(&zero, 1);
            }
            for (int  j = 1; j < 2; j++)    //G
            {
                char ch;
                infile.read(&ch, 1);
                outfile.write(&ch, 1);
            }
            for (int  j = 2; j < 3; j++)    //R
            {
                char ch;
                infile.read(&ch, 1);
                const char zero = 0;
                outfile.write(&zero, 1);
            }
        }
    }
    else
        cout << "Error! Unable to open file...";
        
    infile.close();
    outfile.close();
    return 0;
}