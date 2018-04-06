//Reading and Writing image file as it is.

#include<iostream>
    using std::cout;
    using std::cin;

#include<fstream>
    using std::ifstream;
    using std::ofstream;
    
int main()
{
    ifstream infile ("Lenna.bmp", std::ios::binary);
    ofstream outfile ("lennaW.bmp", std::ios::binary);
    ofstream debug ("debugLenna.txt");
    
    if (infile.is_open())
    {
        debug << "header\n\n";
        for (int  i = 0; i < 54; i++)
        {
            char ch;
            infile.read(&ch, 1);
            int num = (unsigned int) ch; 
            outfile.write(&ch, 1);
            debug << num << "\n";
        }
        
        debug << "\n\n\nColor data\n\n\n";
        
        for (int  i = 0; i < 512; i++)
        {
            debug << i << "\n";
            for (int  i1 = 0; i1 < 512; i1++)    
            {
                for(int j = 0; j < 3; j++)  //B, G, R
                {
                    char ch;
                    infile.read(&ch, 1);
                    int num = (unsigned int)ch;
                    outfile.write(&ch, 1);
                    debug << num << "\t";
                }
                debug << "\n";
            }
            debug << "\n";
        }
    }
    else
        cout << "Error! Unable to open file...";
        
    infile.close();
    outfile.close();
    debug.close();
    return 0;
}