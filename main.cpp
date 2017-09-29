#include <iostream>
#include "Code.h"
#include <ctime>
#include <cmath>
#include <unordered_set>
#include <vector>

void Monte_Karlo(std::vector<Code>& sSpace, int N);

int main() {
   const auto size = (unsigned int)pow((float)2,Code::L);

    std::vector<Code> searchSpace(size);
    for (int i = 0; i < size; ++i) {
        searchSpace[i] = Code(i, i);
    }
    Monte_Karlo(searchSpace,10);

    return 0;
}

void Monte_Karlo(std::vector<Code>& sSpace, int N)
{
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
    std::cout << clock() / 1000.0;

}