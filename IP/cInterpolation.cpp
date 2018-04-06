//Bicubic Interpolation

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
    ifstream infile  ("Fig0222(b)(cameraman).bmp", std::ios::binary);               //input image
    ofstream outfile ("cInterpolation.bmp", std::ios::binary);                      //output image
    ofstream debug   ("debugCinterpolation.txt");                                   //data( histogram ) file
    
    int imgArray [256][256] = { {0} };                                              //Store all data of reading file      
    
    if (infile.is_open())
    {
        for (int  i = 0; i < 18; i++)                                               //Reading first 18 byte
        {
            char ch;
            infile.read(&ch, 1);
            outfile.write(&ch, 1);
        }
        
        int oldWidth;                                                               //Changing Width
        infile.read (reinterpret_cast <char*> (&oldWidth), 4);
        int newWidth = 8 * oldWidth;
        outfile.write (reinterpret_cast <char*> (&newWidth), 4);
        
        int oldHeight;                                                              //Changing Height
        infile.read (reinterpret_cast <char*> (&oldHeight), 4);
        int newHeight = 8 * oldHeight;
        outfile.write (reinterpret_cast <char*> (&newHeight), 4);
        
        for (int  i = 26; i < 54; i++)                                              //Reading last bytes of header
        {
            char ch;
            infile.read(&ch, 1);
            outfile.write(&ch, 1);
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
                    debug << imgArray [i][i1] << "\t";
                }
                debug << "\n\n";
            }
        }
        
        //for (int  i = 0; i < 2048; i++)                                             //Generating bitmap file of 2048 * 2048
        //{           
        //    for (int  i1 = 0; i1 < 2048; i1++)    
        //    {
        //        for(int j = 0; j < 3; j++)                                          //B, G, R
        //        {
        //            char ch = 127;
        //            outfile.write(&ch, 1);
        //        }
        //        debug << "\n\n";
        //    }
        //}
        //
        //int c = 0;
        //for (int  i = 0; i < 256; i++)                                              //Writing first  line of image
        //{
        //    
        //    c++;
        //    if(c <= 10)
        //    {
        //        cout << imgArray [0][i] << "\t";
        //    }
        //    else
        //    {
        //        cout << "\n";
        //        c = 0;
        //    }
        //}
        //cout << "\n";
        
        //int xL = 20, xR = 21, yB = 30, yT = 31;        
        
        //Dr.Hammerand
        //cout << "(" << xL << ", " << yT << ")     : " << imgArray [xL][yT]     << "\n"
        //     << "(" << xR << ", " << yT << ")     : " << imgArray [xR][yT]     << "\n"
        //     << "(" << xL << ", " << yB << ")     : " << imgArray [xL][yB]     << "\n"
        //     << "(" << xR << ", " << yB << ")     : " << imgArray [xR][yB]     << "\n";
        
        //Printing all the 16 points values around Corner Points
        //cout << "(xL-1, yT+1) : " << imgArray [xL-1][yT+1] << " " << "(xL, yT+1)   : " << imgArray [xL][yT+1]   << "  "
        //     << "(xR, yT+1)   : " << imgArray [xR][yT+1]   << " " << "(xR+1, yT+1) : " << imgArray [xR+1][yT+1] << "\n"
        //     << "(xL-1, yT)   : " << imgArray [xL-1][yT]   << " " << "(xL, yT)     : " << imgArray [xL][yT]     << " "
        //     << "(xR, yT)     : " << imgArray [xR][yT]     << " " << "(xR+1, yT)   : " << imgArray [xR+1][yT]   << "\n"
        //     << "(xL-1, yB)   : " << imgArray [xL-1][yB]   << " " << "(xL, yB)     : " << imgArray [xL][yB]     << " "
        //     << "(xR, yB)     : " << imgArray [xR][yB]     << " " << "(xR+1, yB)   : " << imgArray [xR+1][yB]   << "\n"
        //     << "(xL-1, yB-1) : " << imgArray [xL-1][yB-1] << " " << "(xL, yB-1)   : " << imgArray [xL][yB-1]   << " "
        //     << "(xR, yB-1)   : " << imgArray [xR][yB-1]   << " " << "(xR+1, yB-1) : " << imgArray [xR+1][yB-1] << "\n";
        
        int I[4][4], iUV[4][4], iU[4][4], iV[4][4];
         
        cout << "\n";
        
        for (int i = 30; i < 32; i++)  //Corner Points
        {
            for (int i1 = 20; i1 < 22; i1++)
            {
                I[i1][i] = imgArray[i1][i];
                cout << "I(" << i1 << ", " << i << ") : " << I[i1][i] << "\n";
            }
        }
        
        cout << "\n";
        
        for (int i = 30; i < 32; i++)  //Horizontal
        {
            for (int i1 = 20; i1 < 22; i1++)
            {
                iU[i1][i] = (imgArray[i1+1][i] - imgArray[i1-1][i]) / 2;
                cout << "iU(" << i1 << ", " << i << ") : " << iU[i1][i] << "\n";
            }
        }
        
        cout << "\n";
        
        for (int i = 30; i < 32; i++)  //Vertical
        {
            for (int i1 = 20; i1 < 22; i1++)
            {
                iV[i1][i] = (imgArray[i1][i+1] - imgArray[i1][i-1]) / 2;
                cout << "iV(" << i1 << ", " << i << ") : " << iV[i1][i] << "\n";
            }
        }
        
        cout << "\n";
        
        for (int i = 30; i < 32; i++)  //Cross
        {
            for (int i1 = 20; i1 < 22; i1++)
            {
                iUV[i1][i] = ((imgArray[i1-1][i-1] + imgArray[i1+1][i+1])-(imgArray[i1+1][i-1] + imgArray[i1-1][i+1])) / 4;
                cout << "iUV(" << i1 << ", " << i << ") : " << iUV[i1][i] << "\n";
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