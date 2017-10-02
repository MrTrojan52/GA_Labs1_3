#include <iostream>
#include "Code.h"
#include <ctime>
#include <cmath>
#include <algorithm>
#include <unordered_set>


/* Algorithms */
Code Monte_Karlo(std::vector<Code>& sSpace, int N, Code* startVertex = nullptr);
Code Hill_Climbing_depth(std::vector<Code>& sSpace, int N, Code* startVertex = nullptr);
Code Hill_Climbing_width(std::vector<Code>& sSpace, int N, Code* startVertex = nullptr);
Code Hill_Climbing_Gray(std::vector<Code>& sGray, int N, Code* startVertex = nullptr);
Code Multiple_startup(std::vector<Code>& sSpace, int N);

void printOmega(std::vector<Code> &Omega);

int main() {
    Code maxS;
    Code::setLength(5);
    const auto size = (unsigned int)pow((float)2,Code::getLength());

    std::vector<Code> searchSpace(size);
    for (int i = 0; i < size; ++i) {
        searchSpace[i] = Code(i, i);
    }

    /*
    for (int i = 0; i < size; ++i) {
        searchSpace[i].setPreference(5*sin((double)i) + log((double)i));
    }
    maxS =  Multiple_startup(searchSpace, 5);
    */

    maxS = Monte_Karlo(searchSpace,10);

    /*
    for (int i = 0; i < size; ++i) {
        int x = searchSpace[i].getDecNum();
        searchSpace[i].setPreference((x - size / 2) * (x - size / 2));
    }
    maxS = Hill_Climbing_depth(searchSpace, 5);
    */

    /*
    for (int i = 0; i < size; ++i) {
        searchSpace[i].setPreference(rand() % 201);
    }
    maxS = Hill_Climbing_Gray(searchSpace, 5);
    maxS = Hill_Climbing_width(searchSpace, 5);
    */


    system("pause");
    return 0;
}


//!
//! \param sSpace
//! \param N
Code Monte_Karlo(std::vector<Code>& sSpace, int N, Code* startVertex)
{
    if(sSpace.empty()) return Code();
    srand((unsigned int)time(nullptr));
    Code maxS;
    double max = 0;
    int i = 0;
    int curr;
    std::unordered_set<int> ri;
    while(i < N) {
        i++;
        std::cout << "i = " << i << std::endl;
        if(i == 1 && startVertex != nullptr) maxS = *startVertex;
        do {
            curr = rand() % sSpace.size();
        } while (ri.find(curr) != ri.end());

        ri.insert(curr);

        if(sSpace[curr].getPreference() > max) {
           std::cout << "max = " << max << " ---> max = " << sSpace[curr].getPreference() << std::endl;
            max = sSpace[curr].getPreference();

            maxS = sSpace[curr];
            std::cout << "maxS ---> maxS = " << maxS << std::endl << std::endl;
        }

        std::cout << "max = " << max << std::endl;
        std::cout << "maxS = " << maxS << std::endl;
        std::cout << "Si = " << sSpace[curr] << std::endl;
        std::cout << "--------------------" << std::endl;
    }

    std::cout << "\n\n------------------" << std::endl;
    std::cout << "maxS = " << maxS << "\nmax = " << max << std::endl;
    std::cout << "------------------" << std::endl;
    return maxS;
}

//!
//! \param sSpace
//! \param N
Code Hill_Climbing_depth(std::vector<Code>& sSpace, int N, Code* startVertex)
{   if(sSpace.empty()) return Code();
    srand((unsigned int)time(nullptr));
    int i = 0;
    int curr = rand() % sSpace.size();
    Code maxS;
    if(startVertex != nullptr)
        maxS = *startVertex;
    else
        maxS = sSpace[curr];
    Code Si = maxS;
    std::vector<Code> Omega = maxS.getOmega(sSpace);
    double max = maxS.getPreference();

    while(i < N)
    {
        i++;
        std::cout << "------------------" << std::endl;
        std::cout << "i = " << i << std::endl;
        std::cout << "maxS = " << maxS << std::endl;
        std::cout << "max = " << max << std::endl;
        std::cout << "Si = " << Si << std::endl;
        std::cout << "Omega = ";
        printOmega(Omega);
        std::cout << std::endl;
        if(!Omega.empty())
        {
            curr = rand() % Omega.size();
            Si =  Omega[curr];
            std::cout << "Si ---> Si = " << Si << std::endl;
            Omega.erase(Omega.begin() + curr);
            std::cout << "Delete " << Si << " from Omega" << std::endl;
            if(max < Si.getPreference())
            {
                maxS = Si;
                max = maxS.getPreference();
                Omega = maxS.getOmega(sSpace);
                std::cout << std::endl;
                std::cout << "maxS ---> maxS = " << maxS << std::endl;
                std::cout << "max ---> max = " << max << std::endl;
                std::cout << "Omega ---> Omega = ";
                printOmega(Omega);
                std::cout << std::endl;
            }
        }
        else
            break;
    }
    std::cout << "\n\n------------------" << std::endl;
    std::cout << "maxS = " << maxS << "\nmax = " << max << std::endl;
    std::cout << "------------------" << std::endl;
    return maxS;
}

//!
//! \param sSpace
//! \param N
Code Hill_Climbing_width(std::vector<Code>& sSpace, int N, Code* startVertex)
{
    if(sSpace.empty()) return Code();
    srand((unsigned int)time(nullptr));
    int i = 0;
    Code maxS;
    if(startVertex != nullptr)
        maxS = *startVertex;
    else
        maxS = sSpace[rand() % sSpace.size()];
    Code Si = maxS;
    std::vector<Code> Omega = maxS.getOmega(sSpace);
    double max = maxS.getPreference();

    while(i < N)
    {
        i++;
        std::cout << "------------------" << std::endl;
        std::cout << "i = " << i << std::endl;
        std::cout << "maxS = " << maxS << std::endl;
        std::cout << "max = " << max << std::endl;
        std::cout << "Si = " << Si << std::endl;
        std::cout << "Omega = ";
        printOmega(Omega);
        std::cout << std::endl;
        if(!Omega.empty())
        {
            std::sort(Omega.begin(),Omega.end(),
                      [](Code &lhs,Code &rhs){return lhs.getPreference() > rhs.getPreference();});

            Si =  Omega[0];
            std::cout << "Si ---> Si = " << Si << std::endl;


            if(max < Si.getPreference())
            {
                maxS = Si;
                max = maxS.getPreference();
                Omega = maxS.getOmega(sSpace);
                std::cout << std::endl;
                std::cout << "maxS ---> maxS = " << maxS << std::endl;
                std::cout << "max ---> max = " << max << std::endl;
                std::cout << "Omega ---> Omega = ";
                printOmega(Omega);
                std::cout << std::endl;
            }
            else
                break;
        }
        else
            break;
    }
    std::cout << "\n\n------------------" << std::endl;
    std::cout << "maxS = " << maxS << "\nmax = " << max << std::endl;
    std::cout << "------------------" << std::endl;
    return maxS;
}

Code Hill_Climbing_Gray(std::vector<Code>& sGray, int N, Code* startVertex)
{
    for (int i = 0; i < sGray.size(); ++i) {
        sGray[i] = sGray[i].encodeToGray();
    }
    if(startVertex != nullptr)
        *startVertex = startVertex->encodeToGray();
    Code s = Hill_Climbing_width(sGray, N, startVertex).decodeFromGray();
    for (int i = 0; i < sGray.size(); ++i) {
        sGray[i] = sGray[i].decodeFromGray();
    }
    return s;

}

Code Multiple_startup(std::vector<Code>& sSpace, int N)
{
    int i = 0;
    double max = 0;
    Code maxS;
    Code maxi = sSpace[rand() % sSpace.size()];
    while(i < N)
    {
        i++;
        std::cout << "------------------" << std::endl;
        std::cout << "i = " << i << std::endl;
        int k = rand() % 3;
        switch(k)
        {
            case 0:
            {
                std::cout << "Call Monte_Karlo" << std::endl;
                maxi = Monte_Karlo(sSpace,1, &maxi);
                break;
            }
            case 1:
            {
                std::cout << "Call Hill_Climbing_depth" << std::endl;
                maxi = Hill_Climbing_depth(sSpace,1, &maxi);
                break;
            }
            case 2:
            {
                std::cout << "Call Hill_Climbing_width" << std::endl;
                maxi = Hill_Climbing_width(sSpace, 1, &maxi);
                break;
            }
            default:
                break;
        }
        if(maxi.getPreference() > max)
        {
            max = maxi.getPreference();
            maxS = maxi;
            std::cout << "maxS ---> maxS = " << maxS << std::endl;
            std::cout << "max ---> max = " << max << std::endl;
        }

    }
    std::cout << "\n\n------------------" << std::endl;
    std::cout << "maxS = " << maxS << "\nmax = " << max << std::endl;
    std::cout << "------------------" << std::endl;
    return maxS;
}

void printOmega(std::vector<Code> &Omega)
{   if(!Omega.empty()) {
        std::cout << '[';
        for (int i = 0; i < Omega.size() - 1; ++i) {
            std::cout << Omega[i] << " : " << Omega[i].getPreference() << ", ";
        }

        std::cout << Omega[Omega.size() - 1] << " : " << Omega[Omega.size() - 1].getPreference() << ']';
    }
    else
    {
        std::cout << "[]";
    }
}