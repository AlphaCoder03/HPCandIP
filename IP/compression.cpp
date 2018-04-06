//Huffman Tree

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

struct Node
{
    int count = 0;  // sum of two minimum
    int parent = -1; // -1 initially (change once we merge two minimum)
    int left = -1;   // first minimum
    int right = -1;  // second minimum
    int used = -1;   // Remove from list of repetation
} huffmanTree[511];

int main()
{
    ifstream infile  ("Fig0222(b)(cameraman).bmp", std::ios::binary);                //input image
    ofstream outfile ("compression.bmp", std::ios::binary);                          //output image
    ofstream debug   ("debugCompression.txt");                                       //data( compress ) file
    const int size = 256;
    int imgArray [size][size] = { {0} };
    //int histogram [size] = {0};
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
                huffmanTree[index].count++;     //histogram[index]++;
                imgArray [i][i1] = index;                
            }
        }
        
        for (int  i = 0; i < size; i++)
        {
            debug << "[" << i+1 << "]: " << setw(3) << huffmanTree[i].count << "\n";
        }
        
        
        int highestCount = 1;
        for(int i = size; i > 0; i--)
        {
            if (huffmanTree[i].count >= highestCount) // Compares smallest value with current element
            {
                highestCount = huffmanTree[i].count;
            }
        }
        
        int lowestCount = highestCount;
        int lowIndex = 0;
        for(int i = size; i > 0; i--)
        {
            if (huffmanTree[i].count <= lowestCount && huffmanTree[i].count != 0) // Compares smallest value with current element
            {
                lowestCount = huffmanTree[i].count;
                lowIndex = i;
            }
        }
        
        int slowestCount = highestCount;
        int slowIndex = 0;
        for(int i = size; i > 0; i--)
        {
            if ((huffmanTree[i].count <= slowestCount && huffmanTree[i].count >= lowestCount) && (i != lowIndex)) // Compares smallest value with current element
            {
                slowestCount = huffmanTree[i].count;
                slowIndex = i;
            }
        }
        
        huffmanTree[size].count = lowestCount + slowestCount;
        //huffmanTree[size].parent = -1;
        huffmanTree[size].left = lowIndex;
        huffmanTree[size].right = slowIndex;
        //huffmanTree[size].used = -1;
        huffmanTree[lowIndex].parent = size;
        huffmanTree[slowIndex].parent = size;
        huffmanTree[lowIndex].used = 1;
        huffmanTree[slowIndex].used = 1;
        
        cout  << "\n\nLowest Count:         "  <<  lowestCount << " at: " << ( lowIndex + 1) << "\n"
              << "huffmanTree[" << lowIndex+1 << "].parent: " << huffmanTree[lowIndex].parent+1
              << " huffmanTree[" << lowIndex+1 << "].used: " << huffmanTree[lowIndex].used << "\n";
        cout  << "\n\nSecond Lowest Count:  "  << slowestCount << " at: " << (slowIndex + 1) << "\n"
              << "huffmanTree[" << slowIndex+1 << "].parent: " << huffmanTree[slowIndex].parent+1
              << " huffmanTree[" << slowIndex+1 << "].used: " << huffmanTree[slowIndex].used << "\n";
        cout  << "\n\nhuffmanTree[" << size+1 << "].count: "  << huffmanTree[size].count << "\n"
              << "huffmanTree[" << size+1 << "].left: " << huffmanTree[size].left
              << " huffmanTree[" << size+1 << "].right:" << huffmanTree[size].right << "\n";
    }
    else
        cout << "Error! Unable to open file...";
        
    infile.close();
    outfile.close();
    debug.close();
    return 0;
}