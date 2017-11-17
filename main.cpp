#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

int main()
{
    double temp = 0;
    int xnum = 0, ynum = 0, znum = 0, maxX = 0, maxY = 0, maxZ = 0, temp2 = 0;
    int minX = 99999999, minY = 99999999, minZ = 99999999;
    char tempCh = ' ';
    ///Find min and max of file first
    ifstream inFile;
    inFile.open("C:\\Users\\dhaslam\\Downloads\\results\\post-processing\\New_test_samples\\4P1T_label.txt");
    while(!inFile.eof())
    {
        inFile >> xnum >> tempCh >> ynum >> tempCh >> znum >> tempCh >> temp >> tempCh >> temp;
        //cout << x << y << z << temp << endl;
        if(xnum < minX)
            minX = xnum;
        if(ynum < minY)
            minY = ynum;
        if(znum < minZ)
            minZ = znum;
        if(xnum > maxX)
            maxX = xnum;
        if(ynum > maxY)
            maxY = ynum;
        if(znum > maxZ)
            maxZ = znum;
    }
    inFile.close();
    cout << "gotMin//Max" << endl;
    //157 101 95
    double *arr;
    arr = (double *) malloc((maxX-minX+1)*(maxY-minY+1)*(maxZ-minZ+1)*sizeof(double));
    double *label;
    label = (double *) malloc((maxX-minX+1)*(maxY-minY+1)*(maxZ-minZ+1)*sizeof(double));

    double *x;
    x = (double *) malloc(7168*sizeof(double));
    double *y;
    y = (double *) malloc(7168*sizeof(double));
    double *z;
    z = (double *) malloc(7168*sizeof(double));
    double *threshold;
    threshold = (double *) malloc(7168*sizeof(double));
    int *labelArr;
    labelArr = (int *) malloc(7168*sizeof(int));

    for(int i = 0; i < 7168; i++)
    {
        x[i] = 0;
        y[i] = 0;
        z[i] = 0;
        threshold[i] = 0;
        label[i] = 0;
    }

    //cout << (maxX-minX) << " " << (maxY-minY)  << " " << (maxZ-minZ) << endl;
    ///Now put data into data structure
    inFile.open("C:\\Users\\dhaslam\\Downloads\\results\\post-processing\\New_test_samples\\4XDA_label.txt");
    while(!inFile.eof())
    {
        inFile >> xnum >> tempCh >> ynum >> tempCh >> znum >> tempCh >> temp >> tempCh >> temp2;
        //cout << (x-minX) << " " << (y-minY) << " " << (z-minZ) << endl;
        arr[((xnum-minX)*(maxY-minY)*(maxZ-minZ))+((ynum-minY)*(maxZ-minZ))+(znum-minZ)] = temp;
        label[((xnum-minX)*(maxY-minY)*(maxZ-minZ))+((ynum-minY)*(maxZ-minZ))+(znum-minZ)] = temp2;
    }
    inFile.close();
    cout << "created arrays" << endl;

    string path = "C:\\Users\\dhaslam\\Downloads\\results\\post-processing\\New_test_samples\\4XDA\\4XDA-";
    int it = 0;

    for(int i = minX+16; i < maxX-16; i+=32)
        for(int j = minY+16; j < maxY-16; j+=32)
            for(int k = minZ+4; k < maxZ-3; k+=7)
            {
                //cout << it << endl;
                ///regular patch
                path = "C:\\Users\\dhaslam\\Downloads\\results\\post-processing\\New_test_samples\\4XDA\\4XDA-";
                ofstream oFile;
                stringstream ss;
                ss << it;
                string str = ss.str();

                path = path + str + ".txt";
                oFile.open(path.c_str());
                it++;
                for(int l = -16; l < 16; l++)
                    for(int m = -16; m < 16; m++)
                        for(int n = -4; n < 3; n++)
                            oFile << i+l << "," <<  j+m << "," << k+n << "," << arr[((i+l)*(maxY-minY)*(maxZ-minZ))+((j+m)*(maxZ-minZ))+(k+n)] << "," << label[((i+l)*(maxY-minY)*(maxZ-minZ))+((j+m)*(maxZ-minZ))+(k+n)] << endl;
                oFile.close();
/*
                ///rotated around x axis
                path = "C:\\Users\\dhaslam\\Downloads\\results\\post-processing\\New_test_samples\\2xs1\\2XS1-";
                stringstream ss2;
                ss2 << it;
                string str2 = ss2.str();

                path = path + str2 + ".txt";
                oFile.open(path.c_str());
                it++;
                int counter = 0;
                for(int l = -16; l < 16; l++)
                    for(int m = -16; m < 16; m++)
                        for(int n = -4; n < 3; n++)
                        {
                            x[counter] = i+l;
                            y[counter] = ((j+m)*cos(90))+((k+n)*sin(90)*-1);
                            z[counter] = ((j+m)*sin(90))+((k+n)*cos(90));
                            threshold[counter] = arr[((i+l)*(maxY-minY)*(maxZ-minZ))+((j+m)*(maxZ-minZ))+(k+n)];
                            labelArr[counter] = label[((i+l)*(maxY-minY)*(maxZ-minZ))+((j+m)*(maxZ-minZ))+(k+n)];
                            counter++;
                        }
                double temp = 0;
                for(int l = 0; l < 7168; l++)
                    for(int m = l+1; m < 7168; m++)
                    {
                        if(x[l] > x[m])
                        {
                            temp = x[l];
                            x[l] = x[m];
                            x[m] = temp;
                            temp = y[l];
                            y[l] = y[m];
                            y[m] = temp;
                            temp = z[l];
                            z[l] = z[m];
                            z[m] = temp;
                            temp = threshold[l];
                            threshold[l] = threshold[m];
                            threshold[m] = temp;
                            temp = labelArr[l];
                            labelArr[l] = labelArr[m];
                            labelArr[m] = temp;
                        }
                        else if(x[l] == x[m] && y[l] < y[m])
                        {
                            temp = x[l];
                            x[l] = x[m];
                            x[m] = temp;
                            temp = y[l];
                            y[l] = y[m];
                            y[m] = temp;
                            temp = z[l];
                            z[l] = z[m];
                            z[m] = temp;
                            temp = threshold[l];
                            threshold[l] = threshold[m];
                            threshold[m] = temp;
                            temp = labelArr[l];
                            labelArr[l] = labelArr[m];
                            labelArr[m] = temp;
                        }
                        else if(x[l] == x[m] && y[l] == y[m] && z[l] < z[m])
                        {
                            temp = x[l];
                            x[l] = x[m];
                            x[m] = temp;
                            temp = y[l];
                            y[l] = y[m];
                            y[m] = temp;
                            temp = z[l];
                            z[l] = z[m];
                            z[m] = temp;
                            temp = threshold[l];
                            threshold[l] = threshold[m];
                            threshold[m] = temp;
                            temp = labelArr[l];
                            labelArr[l] = labelArr[m];
                            labelArr[m] = temp;
                        }
                    }
                for(int l = 0; l < 7168; l++)
                    oFile << x[l] << "," <<  y[l] << "," << z[l] << "," << threshold[l] << "," << labelArr[l] << endl;
                oFile.close();
                for(int i = 0; i < 7168; i++)
                {
                    x[i] = 0;
                    y[i] = 0;
                    z[i] = 0;
                    threshold[i] = 0;
                    labelArr[i] = 0;
                }
                counter = 0;

                ///rotated around y axis
                path = "C:\\Users\\dhaslam\\Downloads\\results\\post-processing\\New_test_samples\\2xs1\\2XS1-";
                stringstream ss3;
                ss3 << it;
                string str3 = ss3.str();

                path = path + str3 + ".txt";
                oFile.open(path.c_str());
                it++;
                for(int l = -16; l < 16; l++)
                    for(int m = -16; m < 16; m++)
                        for(int n = -4; n < 3; n++)
                        {
                            x[counter] = ((i+l)*cos(90))+((k+n)*sin(90));
                            y[counter] = j+m;
                            z[counter] = ((i+l)*sin(90)*-1)+((k+n)*cos(90));
                            threshold[counter] = arr[((i+l)*(maxY-minY)*(maxZ-minZ))+((j+m)*(maxZ-minZ))+(k+n)];
                            labelArr[counter] = label[((i+l)*(maxY-minY)*(maxZ-minZ))+((j+m)*(maxZ-minZ))+(k+n)];
                            counter++;
                        }
                for(int l = 0; l < 7168; l++)
                    for(int m = l+1; m < 7168; m++)
                    {
                        if(x[l] > x[m])
                        {
                            temp = x[l];
                            x[l] = x[m];
                            x[m] = temp;
                            temp = y[l];
                            y[l] = y[m];
                            y[m] = temp;
                            temp = z[l];
                            z[l] = z[m];
                            z[m] = temp;
                            temp = threshold[l];
                            threshold[l] = threshold[m];
                            threshold[m] = temp;
                            temp = labelArr[l];
                            labelArr[l] = labelArr[m];
                            labelArr[m] = temp;
                        }
                        else if(x[l] == x[m] && y[l] < y[m])
                        {
                            temp = x[l];
                            x[l] = x[m];
                            x[m] = temp;
                            temp = y[l];
                            y[l] = y[m];
                            y[m] = temp;
                            temp = z[l];
                            z[l] = z[m];
                            z[m] = temp;
                            temp = threshold[l];
                            threshold[l] = threshold[m];
                            threshold[m] = temp;
                            temp = labelArr[l];
                            labelArr[l] = labelArr[m];
                            labelArr[m] = temp;
                        }
                        else if(x[l] == x[m] && y[l] == y[m] && z[l] < z[m])
                        {
                            temp = x[l];
                            x[l] = x[m];
                            x[m] = temp;
                            temp = y[l];
                            y[l] = y[m];
                            y[m] = temp;
                            temp = z[l];
                            z[l] = z[m];
                            z[m] = temp;
                            temp = threshold[l];
                            threshold[l] = threshold[m];
                            threshold[m] = temp;
                            temp = labelArr[l];
                            labelArr[l] = labelArr[m];
                            labelArr[m] = temp;
                        }
                    }
                for(int l = 0; l < 7168; l++)
                    oFile << x[l] << "," <<  y[l] << "," << z[l] << "," << threshold[l] << "," << labelArr[l] << endl;
                oFile.close();
                for(int i = 0; i < 7168; i++)
                {
                    x[i] = 0;
                    y[i] = 0;
                    z[i] = 0;
                    threshold[i] = 0;
                    labelArr[i] = 0;
                }
                counter = 0;

                ///rotated around z axis
                path = "C:\\Users\\dhaslam\\Downloads\\results\\post-processing\\New_test_samples\\2xs1\\2XS1-";
                stringstream ss4;
                ss4 << it;
                string str4 = ss4.str();

                path = path + str4 + ".txt";
                oFile.open(path.c_str());
                it++;
                for(int l = -16; l < 16; l++)
                    for(int m = -16; m < 16; m++)
                        for(int n = -4; n < 3; n++)
                        {
                            x[counter] = ((i+l)*cos(90))+((j+m)*sin(90)*-1);
                            y[counter] = ((i+l)*sin(90))+((j+m)*cos(90));
                            z[counter] = k+n;
                            threshold[counter] = arr[((i+l)*(maxY-minY)*(maxZ-minZ))+((j+m)*(maxZ-minZ))+(k+n)];
                            labelArr[counter] = label[((i+l)*(maxY-minY)*(maxZ-minZ))+((j+m)*(maxZ-minZ))+(k+n)];
                            counter++;
                        }
                for(int l = 0; l < 7168; l++)
                    for(int m = l+1; m < 7168; m++)
                    {
                        if(x[l] > x[m])
                        {
                            temp = x[l];
                            x[l] = x[m];
                            x[m] = temp;
                            temp = y[l];
                            y[l] = y[m];
                            y[m] = temp;
                            temp = z[l];
                            z[l] = z[m];
                            z[m] = temp;
                            temp = threshold[l];
                            threshold[l] = threshold[m];
                            threshold[m] = temp;
                            temp = labelArr[l];
                            labelArr[l] = labelArr[m];
                            labelArr[m] = temp;
                        }
                        else if(x[l] == x[m] && y[l] < y[m])
                        {
                            temp = x[l];
                            x[l] = x[m];
                            x[m] = temp;
                            temp = y[l];
                            y[l] = y[m];
                            y[m] = temp;
                            temp = z[l];
                            z[l] = z[m];
                            z[m] = temp;
                            temp = threshold[l];
                            threshold[l] = threshold[m];
                            threshold[m] = temp;
                            temp = labelArr[l];
                            labelArr[l] = labelArr[m];
                            labelArr[m] = temp;
                        }
                        else if(x[l] == x[m] && y[l] == y[m] && z[l] < z[m])
                        {
                            temp = x[l];
                            x[l] = x[m];
                            x[m] = temp;
                            temp = y[l];
                            y[l] = y[m];
                            y[m] = temp;
                            temp = z[l];
                            z[l] = z[m];
                            z[m] = temp;
                            temp = threshold[l];
                            threshold[l] = threshold[m];
                            threshold[m] = temp;
                            temp = labelArr[l];
                            labelArr[l] = labelArr[m];
                            labelArr[m] = temp;
                        }
                    }
                for(int l = 0; l < 7168; l++)
                    oFile << x[l] << "," <<  y[l] << "," << z[l] << "," << threshold[l] << "," << labelArr[l] << endl;
                oFile.close();
                for(int i = 0; i < 7168; i++)
                {
                    x[i] = 0;
                    y[i] = 0;
                    z[i] = 0;
                    threshold[i] = 0;
                    labelArr[i] = 0;
                }
                counter = 0;
                */
            }

    return 0;
}
