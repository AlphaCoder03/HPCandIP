//Writing grey color of image

#include<iostream>
    using std::cout;
    using std::cin;

#include<fstream>
    using std::fstream;
    using std::ifstream;
    using std::ofstream;

#include <cmath>
    using std::pow;

int main()
{
    ifstream infile  ("Lenna.bmp", std::ios::binary);
    ofstream outfile ("lennaGrey.bmp", std::ios::binary);
    ofstream debug   ("debugGrey.txt");
    
    int histogram [256] = {0};
        
    if (infile.is_open())
    {
        for (int  i = 0; i < 54; i++)
        {
            char ch;
            infile.read(&ch, 1);
            outfile.write(&ch, 1);
        }
        
        int sum = 0;
        char avg = 0;
        
        for (int  i = 0; i < 512; i++)
        {
            for (int  i1 = 0; i1 < 512; i1++)    
            {
                char bgr [3];               //B, G, R
                infile.read (bgr, 3);
                
                unsigned char ubgr [3];
                for (int i = 0; i < 3; i++)
                   ubgr[i] = bgr[i];
                
                int ibgr[3];
                for (int i = 0; i < 3; i++)
                   ibgr[i] = ubgr[i];
                
                sum = ibgr[0] + ibgr[1] + ibgr[2];
                avg = sum / 3;
                histogram[sum / 3]++;
                
                for(int j = 0; j < 3; j++)
                {
                    outfile.write(&avg, 1);     
                }
            }
        }
    }
    else
        cout << "Error! Unable to open file...";
        
    infile.close();
    outfile.close();
    debug.close();
    return 0;
}