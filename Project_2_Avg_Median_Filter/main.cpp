//  CV_Project_2_Avg_Median_Filter
//  Created by Daniel Rand on 9/6/19.

#include <iostream>
#include <fstream>
using namespace std;

class ImageProcesing {
    
public:
    
    int numRows, numCols, minVal, maxVal, newMin, newMax;
    int ** avgAry, ** mirrorFramedAry, ** medianAry, * neighborAry;
    
    ImageProcesing (ifstream & inFile) {
        inFile >> numRows >> numCols >> minVal >> maxVal;
        mirrorFramedAry = new int * [numRows+2];
        avgAry = new int * [numRows+2];
        medianAry = new int * [numRows+2];
        neighborAry = new int [9] ();
        for (int i = 0; i < numRows + 2; i++) {
            mirrorFramedAry[i] = new int [numCols + 2] ();
            avgAry[i] = new int [numCols + 2] ();
            medianAry[i] = new int [numCols + 2] ();
        }
        /* Print ary just in case
        for (int i = 0; i < numRows +2; i++) {
            for (int j = 0; j< numCols +2; j++) {
                cout << mirrorFramedAry[i][j] << " ";
            } cout << endl;
        }
         */
        
    }
    // read from input file and load onto mirrorFramedAry begin at [1][1]
    void loadImage (ifstream & inFile) {
        for (int i = 0; i < numRows; i++)
            for (int j = 0; j < numCols; j++)
                inFile >> mirrorFramedAry[i+1][j+1];
    }
    
    void mirrorFraming () {
        
    }
    
    void processImage (ifstream & inFile,ofstream &outFile) {
        for (int i = 1; i <= numRows; i++) {
            for (int j = 1; j <= numCols; j++) {
                int pixelVal;
                inFile >> pixelVal;
                if (pixelVal > 0)
                    outFile << "1 ";
                else outFile << "  ";
            } outFile << endl;
        }
    }
};

int main(int argc, const char * argv[]) {
    ifstream inFile;
    ofstream outFile1, outFile2;
    inFile.open(argv[1]);
    outFile1.open(argv[2]);
    outFile2.open(argv[3]);
    ImageProcesing IP (inFile);
    IP.loadImage(inFile);
    IP.mirrorFraming();
    cout << "Hello, World!\n";
    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}
