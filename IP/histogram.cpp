//Histogram Equalization

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

int main()
{
    ifstream infile  ("Fig0222(b)(cameraman).bmp", std::ios::binary);                //input image
    ofstream outfile ("histogram.bmp", std::ios::binary);                            //output image
    ofstream debug   ("debugHistogram.txt");                                         //data( histogram ) file
    const int size = 256;
    int imgArray [size][size] = { {0} };
    int histogram [size] = {0};
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
                infile.read (bgr, 3);             //read all three color of pixel 
                
                unsigned char ubgr [3];         
                for (int i = 0; i < 3; i++)       //assign pixel value from char to unsigned 
                   ubgr[i] = bgr[i];
                
                int ibgr[3];
                for (int i = 0; i < 3; i++)      //assign pixel value from unsigned to integer
                   ibgr[i] = ubgr[i];
                
                sum = ibgr[0] + ibgr[1] + ibgr[2];
                index = sum / 3;
                histogram[index]++;
                imgArray [i][i1] = index;
                
            }
        }
        debug << fixed << setprecision(8);
        sum = 0;
        double psum = 0, sk = 0;
        int roundsk[255];
        for (int  i = 0; i < size; i++)
        {
            sum += histogram[i];
            psum += (static_cast <double>(histogram[i]) / (size * size));
            sk = (size - 1) * psum;
            roundsk[i] = static_cast <int> ((floor(sk + 0.5)));
            debug << "[" << i+1 << "]: " << setw(3) << histogram[i] << setw(05) << "\tp(rk): "
                  << setw(10) << (static_cast <double> (histogram[i]) / (size * size))  << "\tsk: "  << setw(10) << sk
                  << "\troundsk " << roundsk[i] << "\n"; 
        }
        roundsk[0] = 0;
        int tempsum[size] = {0};
        int temp = histogram[0];
        for (int  i = 0; i < size; i++)
        {
            temp = histogram[i];
            while(roundsk[i+1] == roundsk[i])
            {
                temp += histogram[i+1];
                i++;                
            }
            tempsum [i] = temp;
        }
        for (int  i = 0; i < size; i++)
        {
            debug << "n'k[" << i+1 << "]: " << tempsum[i] << "\tps(sk): " << (static_cast <double> (tempsum[i]) / sum) << "\n";
        }
        debug << "Total: " << sum << "\ttotal p(rk): " << psum << "\n";  
    }
    else
        cout << "Error! Unable to open file...";
        
    infile.close();
    outfile.close();
    debug.close();
    return 0;
}