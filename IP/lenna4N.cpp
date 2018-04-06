//Bilinear Interpolation

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
    ifstream infile  ("Lenna.bmp", std::ios::binary);             //input image
    ofstream outfile ("lenna4N.bmp", std::ios::binary);           //output image
    ofstream debug   ("debug4N.txt");                             //data( histogram ) file
    
    int iMax = 512, i1Max = 512;
    int imgArray [512][512] = { {0} };
    int histogram [256] = {0};
    int total = 0, standardDeviation = 0;
    int lowest = 1, highest = 0, hpixel, lpixel, average = 0;
    int N, S, E, W;
    int ibgr[3];            //B, G, R
    unsigned char ubgr [3];
    char bgr [3];
    
    if (infile.is_open())
    {
        debug << "Header: \n\n";
        for (int  i = 0; i < 54; i++)
        {
            char ch;
            infile.read(&ch, 1);
            int num = (unsigned int) ch; 
            outfile.write(&ch, 1);
            debug << num << "\t";
        }
        
        debug << "\ni1 \tBlue \tGreen \tRed \tSum \tAvg \n";
        int sum = 0;
        char avg = 0;
        
        for (int  i = 0; i < 512; i++)
        {
            for (int  i1 = 0; i1 < 512; i1++)    
            {
                                   
                infile.read (bgr, 3);           //read all three color of pixel 
                
                         
                for (int i = 0; i < 3; i++)     //assign pixel value from char to unsigned 
                   ubgr[i] = bgr[i];
                
                
                for (int i = 0; i < 3; i++)     //assign pixel value from unsigned to integer
                   ibgr[i] = ubgr[i];
                
                sum = ibgr[0] + ibgr[1] + ibgr[2];
                avg = sum / 3;
                histogram[sum / 3]++;
                imgArray [i][i1] = sum / 3;
            }
        }
        char nAvg = 0;
        for (int  i = 0; i < iMax; i++)
        {
            N = i + 1;                         //addr of North, South neighbor
            S = i - 1;
            if(N >= 512) N = iMax - 1;         //stay in-bounds 
            if(S < 0) S = 0;
            
            for (int  i1 = 0; i1 < i1Max; i1++)    
            {
                E = i1 + 1;                    //address of East, West neighbor
                W = i1 - 1;
                if(E >= i1Max) E = i1Max-1;    //stay in-bounds 
                if(W < 0) W=0;
                
                N = imgArray [i1][N];         // find neighborhood pixels
                S = imgArray [i1][S];
                E = imgArray [E][i];
                W = imgArray [W][i];
                
                nAvg = (N + S + E + W) / 4;
                
                
                debug << i1 << ' ' << ibgr[0] << ' ' << ibgr[1] << ' ' << ibgr[2] //<< ' ' << blue << ' ' << green << ' ' << red
                      << ' ' << sum << ' ' << static_cast <unsigned int> (avg) << "\n";      
                debug << "N: " << N << ' ' << "S: " << S << '\n'
                      << "E: " << E << ' ' << "W: " << W << '\n';
                
                for(int j = 0; j < 3; j++)      //B, G, R
                {
                    outfile.write(&nAvg, 1);     
                }
            }
            debug << "\navg: " << avg;
        }

        for(int i = 0; i < 256; i++)
        {
            debug << histogram[i] << "\n";
            total = total + histogram[i];
            if(histogram[i] > highest) // Compare biggest value with current element
            {
                highest = histogram[i];
                hpixel = i + 1;
            }
            if (histogram[i] <= lowest && histogram[i] >= lowest) // Compares smallest value with current element
            {
                lowest = histogram[i];
                lpixel = i + 1;
            }
            average = total / 256;
        }
        
        for(int i = 0; i < 256; i++)
            standardDeviation += pow(histogram[i] - average, 2);

        
        debug <<"\nTotal:             " << total << "\n"
              <<"Highest Pixel color: " << hpixel << "\tNo. of time repeat: " << highest << "\n"
              <<"Lowest Pixel color:  " << lpixel << "\tNo. of time repeat: " << lowest << "\n"
              <<"Pixel color average: " << average << "\n"
              <<"Standard Deviation:  " << sqrt(standardDeviation / 256) << "\n";
    }
    else
        cout << "Error! Unable to open file...";
        
    infile.close();
    outfile.close();
    debug.close();
    return 0;
}