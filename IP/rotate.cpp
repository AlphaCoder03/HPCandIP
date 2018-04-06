//Rotating image depend on angle, user's entered. 

#include<iostream>
    using std::cout;
    using std::cin;
#include<fstream>
    using std::fstream;
    using std::ifstream;
    using std::ofstream;
#include <cmath>
    using std::pow;
#include<iomanip>
    using std::setw;
    using std::setprecision;
    using std::fixed;

const double PI = 3.14159265;

int main()
{
    ifstream infile  ("Fig0222(b)(cameraman).bmp", std::ios::binary);                //input image
    ofstream outfile ("rotate.bmp", std::ios::binary);                            //output image
    
    const int size = 256;
    int imgArray [size][size] = { {0} };
    int rotate [size] = {0};
    
    if (infile.is_open())
    {
        for (int  i = 0; i < 54; i++)
        {
            char ch;
            infile.read(&ch, 1);
            outfile.write(&ch, 1);
        }
        
        int sum = 0;
        int index;
        
        for (int  i = 0; i < size; i++)
        {
            for (int  i1 = 0; i1 < size; i1++)    //B, G, R
            {
                char bgr [3];
                infile.read (bgr, 3);           //read all three color of pixel 
                
                unsigned char ubgr [3];         
                for (int i = 0; i < 3; i++)     //assign pixel value from char to unsigned 
                   ubgr[i] = bgr[i];
                
                int ibgr[3];
                for (int i = 0; i < 3; i++)     //assign pixel value from unsigned to integer
                   ibgr[i] = ubgr[i];
                
                sum = ibgr[0] + ibgr[1] + ibgr[2];
                index = sum / 3;
                rotate[index]++;
                imgArray [i][i1] = index;
                
            }
        }
        
        double px [size] = {0}, py [size] = {0},
               px1[size] = {0}, py1[size] = {0};
        int    px2[size] = {0}, py2[size] = {0};
        const double sub = 127.5;
        double temp, temp1, param;
        
        cout << "\nEnter Rotation Angle: ";
        cin >> param;
        
        for (int  i = 0; i < size; i++)
        {
            temp = i;
            px[i]   = temp - sub;
            
            for (int  i1 = 0; i1 < size; i1++)    //B, G, R
            {
                temp1 = i1;
                py[i1]  = temp1 - sub;
                px1[i]  = (px[i]  * cos ( param * PI / 180.0 )) - (py[i]  * sin ( param * PI / 180.0 ));
                py1[i1] = (px[i1] * sin ( param * PI / 180.0 )) + (py[i1] * cos ( param * PI / 180.0 ));
                px2[i]  = static_cast <int> ((floor((px1[i]   + sub) + 0.5)));
                py2[i1] = static_cast <int> ((floor((py1[i1]  + sub) + 0.5)));
                cout << "[" << i << "][ " << i1 << "]: " << px2[i] << ", " << py2[i1] << "\n";         
            }
        }
        
    }
    else
        cout << "Error! Unable to open file...";
        
    infile.close();
    outfile.close();
    
    return 0;
}