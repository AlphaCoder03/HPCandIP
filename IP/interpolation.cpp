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
    ofstream outfile ("interpolation.bmp", std::ios::binary);                       //output image
    ofstream debug   ("debug.txt");                                                 //data( histogram ) file
    
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
                    imgArray [i][i1] = static_cast <unsigned int> (ch);
                    debug << imgArray [i][i1] << "\t";
                }
                debug << "\n\n";
            }
        }
        
        for (int  i = 0; i < 2048; i++)                                             //Generating bitmap file of 2048 * 2048
        {           
            for (int  i1 = 0; i1 < 2048; i1++)    
            {
                for(int j = 0; j < 3; j++)                                          //B, G, R
                {
                    char ch = 127;
                    outfile.write(&ch, 1);
                }
                debug << "\n\n";
            }
        }
        
        int xL = 0, xR = 1, yB = 0, yT = 1;        
        
        cout << imgArray [xL][yB] << " " << imgArray [xR][yB] << " "
             << imgArray [xL][yT] << " " << imgArray [xR][yT] << "\n";
    
        int iLB = imgArray [xL][yB];
        int iRB = imgArray [xR][yB];
        int iLT = imgArray [xL][yT];
        int iRT = imgArray [xR][yT];
        
        for (double y = yT; y > yB; y -= 0.125)                                     // y = yT down to yB
        {
            for (double x = xL; x < xR; x += 0.125)                                 // x = xL to xR
            {
                double dX = xR - x;
                double dY = y - yB;
                double diT = iRT - iLT;
                double diB = iRB - iLB;
                double qB = (xR * iLB) - (x * iRB);
                double qT = (xR * iLT) - (x * iRT);
                double A = ((yT * diB) - (yB * diT)) / (dX * dY);
                double B = (qT - qB) / (dX * dY);
                double C = (diT - diB) / (dX * dY);
                double D = ((yT * qB) - (yB * qT)) / (dX * dY);
                char I = (A * x) + (B * y) + (C * x * y) + D;
                cout << static_cast <int> (I) << "\t";                              // write intensity;
            } // end of inner for
            cout << "\n";// write end-of-line;
        } // end of outer for        
    }
    else
        cout << "Error! Unable to open file...";
        
    infile.close();
    outfile.close();
    debug.close();
    return 0;
}