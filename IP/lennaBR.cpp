//Writing only blue and red color of image

#include<iostream>
    using std::cout;
    using std::cin;

#include<fstream>
    using std::ifstream;
    using std::ofstream;
    
int main()
{
    ifstream infile ("Lenna.bmp", std::ios::binary);
    ofstream outfile ("lennaBR.bmp", std::ios::binary);
    
    if (infile.is_open())
    {
        for (int  i = 0; i < 54; i++)
        {
            char ch;
            infile.read(&ch, 1);
            outfile.write(&ch, 1);
        }
        
        for (int  i = 0; i < 262144; i++)
        {
            for (int  j = 0; j < 1; j++)    //B
            {
                char ch;
                infile.read(&ch, 1);
                outfile.write(&ch, 1);
            }
            for (int  j = 1; j < 2; j++)    //G
            {
                char ch;
                infile.read(&ch, 1);
                const char zero = 0;
                outfile.write(&zero, 1);
            }
            for (int  j = 2; j < 3; j++)    //R
            {
                char ch;
                infile.read(&ch, 1);
                outfile.write(&ch, 1);
            }
        }
    }
    else
        cout << "Error! Unable to open file...";
        
    infile.close();
    outfile.close();
    return 0;
}