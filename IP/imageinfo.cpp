//XY - plotation

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
    ifstream infile   ("Fig0222(b)(cameraman).bmp", std::ios::binary);              //input image
    ofstream debug    ("debugImageinfo.txt");                                       //data file
    
    int lowest = 0, highest = 0,  hpixel = 0, lpixel = 0;
    int imgArray  [256][256] = { {0} };                                              //Store all data of reading file      
    int imgArrayX [256][256] = { {0} };
    int imgArrayY [256][256] = { {0} };
    
    if (infile.is_open())
    {
        ofstream outfileX ("imageInfoX.bmp", std::ios::binary);                      //output image X
        ofstream outfileY ("imageInfoY.bmp", std::ios::binary);                      //output image Y
    
        for (int  i = 0; i < 54; i++)
        {
            char ch;
            infile.read(&ch, 1);
            outfileX.write(&ch, 1);
            outfileY.write(&ch, 1);
        }
        
        for (int  i = 0; i < 256; i++)                                              //Reading bitmap file
        {
            for (int  i1 = 0; i1 < 256; i1++)    
            {
                for(int j = 0; j < 3; j++)                                          //B, G, R
                {
                    char ch;
                    infile.read (&ch, 1);
                    unsigned char c = ch;
                    imgArray [i][i1] = c;
                }
            }
        }
        
        hpixel = imgArray [0][0];
        lpixel = imgArray [0][0];
        for (int  i = 0; i < 256; i++)                                              //Finding highest and lowest
        {
            for (int  i1 = 0; i1 < 256; i1++)    
            {
                if (hpixel < imgArray [i][i1])
                    hpixel = imgArray [i][i1];
                if (lpixel > imgArray [i][i1])
                    lpixel = imgArray[i][i1];
            }
        }
        cout << "Highest Value of Pixle is : " << hpixel
             << "\nlowest Value of Pixle is : " << lpixel << "\n";
             
        for (int  i = 0; i < 256; i++)                                              //Finding Delta-X
        {
            for (int  i1 = 0; i1 < 256; i1++)    
            {
                if(i1 < 255)
                {
                    imgArrayX [i][i1] = imgArray [i][i1+1] - imgArray [i][i1];
                    debug << imgArrayX [i][i1] << " ";
                }
                else
                {
                    imgArrayX [i][i1] = imgArray [i][i1];
                    debug << imgArrayX [i][i1] << " ";
                }
            }
            debug << "\n\n";
        }
        
        highest = imgArrayX [0][0];
        lowest  = imgArrayX [0][0];
        for (int  i = 0; i < 256; i++)                                              //Finding highest and lowest for Delta X
        {
            for (int  i1 = 0; i1 < 256; i1++)    
            {
                if (highest < imgArrayX [i][i1])
                    highest = imgArrayX [i][i1];
                if (lowest > imgArrayX [i][i1])
                    lowest = imgArrayX[i][i1];
            }
        }
        cout << "Highest Value of Delta X is : " << highest
             << "\nlowest Value of Delta X is : " << lowest << "\n";
        
        unsigned char nNor = 0;
        double a = 0;
        
        for (int  i = 0; i < 256; i++)                                              //Finding Normalization
        {
            for (int  i1 = 0; i1 < 256; i1++)    
            {
                a = (static_cast <double> (imgArrayX [i][i1]) - lowest) / (static_cast <double>(highest)- lowest);
                nNor = 255 * a;
                for(int j = 0; j < 3; j++)      //B, G, R
                {
                    outfileX.write((char*) &nNor, 1);     
                }
            }
            debug << "\n\n";
        }
        
        for (int  i = 0; i < 256; i++)                                              //Finding Delta-Y
        {
            for (int  i1 = 0; i1 < 256; i1++)    
            {
                if(i < 255)
                {
                    imgArrayY [i][i1] = imgArray [i+1][i1] - imgArray [i][i1];
                    debug << imgArrayY [i][i1] << " ";
                }
                else
                {
                    imgArrayY [i][i1] = imgArray [i][i1];
                    debug << imgArrayY [i][i1] << " ";
                }
            }
            debug << "\n\n";
        }
        
        highest = imgArrayY [0][0];
        lowest  = imgArrayY [0][0];
        for (int  i = 0; i < 256; i++)                                              //Finding highest and lowest for Delta Y
        {
            for (int  i1 = 0; i1 < 256; i1++)    
            {
                if (highest < imgArrayY [i][i1])
                    highest = imgArrayY [i][i1];
                if (lowest > imgArrayY [i][i1])
                    lowest = imgArrayY [i][i1];
            }
        }
        cout << "Highest Value of Delta Y is : " << highest
             << "\nlowest Value of Delta Y is : " << lowest << "\n";
        
        nNor = 0;
        a = 0;
        
        for (int  i = 0; i < 256; i++)                                              //Finding Normalization
        {
            for (int  i1 = 0; i1 < 256; i1++)    
            {
                a = (static_cast <double> (imgArrayY [i][i1]) - lowest) / (static_cast <double>(highest)- lowest);
                nNor = 255 * a;
                for(int j = 0; j < 3; j++)      //B, G, R
                {
                    outfileY.write((char*) &nNor, 1);     
                }
            }
            debug << "\n\n";
        }
        outfileX.close();
        outfileY.close();
        ifstream infileX  ("imageInfoX.bmp", std::ios::binary);
        ifstream infileY  ("imageInfoY.bmp", std::ios::binary);
        if (infileX.is_open() && infileY.is_open())
        {
            ofstream outfileXY ("imageInfoXY.bmp", std::ios::binary);                    //output image XY
            for (int  i = 0; i < 54; i++)
            {
                char ch, ch1;
                infileX.read(&ch, 1);
                infileY.read(&ch1, 1);
                outfileXY.write(&ch, 1);
            }
            
            for (int  i = 0; i < 256; i++)                                              //Reading bitmap file
            {
                for (int  i1 = 0; i1 < 256; i1++)    
                {
                    for(int j = 0; j < 3; j++)                                          //B, G, R
                    {
                        char ch1, ch2;
                        infileX.read (&ch1, 1);
                        infileY.read (&ch2, 1);
                        unsigned char c1 = ch1;
                        unsigned char c2 = ch2;
                        unsigned char temp;
                        if(c1 <= c2)
                            temp = c2;
                        else
                            temp = c1;
                        outfileXY.write((char*) &temp, 1);
                    }
                }
            }
        }
        else
            cout << "Error! Unable to open file...";    
    }
    else
        cout << "Error! Unable to open file...";
        
    infile.close();
    debug.close();
    return 0;
}