#include <iostream>
#include "Code.h"
#include <ctime>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <vector>

void Monte_Karlo(std::vector<Code>& sSpace, int N);
void Hill_Climbing_depth(std::vector<Code>& sSpace, int N);
void Hill_Climbing_width(std::vector<Code>& sSpace, int N);
void printOmega(std::vector<Code> &Omega);
int main() {
   const auto size = (unsigned int)pow((float)2,Code::L);

    std::vector<Code> searchSpace(size);
    for (int i = 0; i < size; ++i) {
        searchSpace[i] = Code(i, i);
    }

   // Monte_Karlo(searchSpace,10);

    for (int i = 0; i < size; ++i) {
        int x = searchSpace[i].getDecNum();
        searchSpace[i].setPreference((x - size / 2) * (x - size / 2));
    }
   // Hill_Climbing_depth(searchSpace, 5);
    for (int i = 0; i < size; ++i) {
        searchSpace[i].setPreference(rand() % 201);
    }
    Hill_Climbing_width(searchSpace, 5);




    return 0;
}


//!
//! \param sSpace
//! \param N
void Monte_Karlo(std::vector<Code>& sSpace, int N)
{
    if(sSpace.size() <= 0) return;
    srand((unsigned int)time(nullptr));
    Code maxS;
    int max = 0;
    int i = 0;
    int curr;
    std::unordered_set<int> ri;
    while(i < N) {
        i++;
        std::cout << "i = " << i << std::endl;

        do
        {
            curr = rand() % sSpace.size();
        } while(ri.find(curr) != ri.end());
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
    // std::cout << clock() / 1000.0;

}

//!
//! \param sSpace
//! \param N
void Hill_Climbing_depth(std::vector<Code>& sSpace, int N)
{   if(sSpace.size() <= 0) return;
    srand((unsigned int)time(nullptr));
    int i = 0;
    int curr = rand() % sSpace.size();
    Code maxS = sSpace[curr];
    Code Si = maxS;
    std::vector<Code> Omega = maxS.getOmega(sSpace);
    int max = maxS.getPreference();

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

}

//!
//! \param sSpace
//! \param N
void Hill_Climbing_width(std::vector<Code>& sSpace, int N)
{
    if(sSpace.size() <= 0) return;
    srand((unsigned int)time(nullptr));
    int i = 0;
    Code maxS = sSpace[rand() % sSpace.size()];
    Code Si = maxS;
    std::vector<Code> Omega = maxS.getOmega(sSpace);
    int max = maxS.getPreference();

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
}

void printOmega(std::vector<Code> &Omega)
{   if(Omega.size() > 0) {
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