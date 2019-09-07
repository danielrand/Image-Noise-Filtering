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
        //Leftmost and Rightmost columns:
        for (int i = 1; i <= numRows; i++) {
            mirrorFramedAry[i][0] = mirrorFramedAry[i][1];
            mirrorFramedAry[i][numCols+1] = mirrorFramedAry[i][numCols];
        }
        //Top and bottom rows:
        for (int i = 0; i <= numCols+1; i++) {
            mirrorFramedAry[0][i] = mirrorFramedAry[1][i];
            mirrorFramedAry[numRows+1][i] = mirrorFramedAry[numRows][i];
        }
    }
    
    void loadNeighbors (int row, int col) {
        int index = -1;
        for (int i = row - 1; i <= row + 1; i++)
            for (int j = col - 1; j <= col + 1; j++)
                neighborAry[++index] = mirrorFramedAry[i][j];
    }
    
    void computeAvg () {
        for (int i = 1; i <= numRows; i++) {
            for (int j = 1; j <= numCols; j++) {
                loadNeighbors(i, j);
            }
        }
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
    IP.computeAvg();
    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}
