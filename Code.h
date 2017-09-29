//
// Created by Trojan on 27.09.2017.
//

#ifndef GA_LABS1_3_CODE_H
#define GA_LABS1_3_CODE_H


#include <ostream>

class Code {

    int decNum;
    int preference;

public:
    static const int L = 5;
    static int hammingDistance(Code& lhs, Code& rhs);


    int getPreference() const;

    void setPreference(int preference);

    int getDecNum() const;

    void setDecNum(int decNum);

    explicit Code(int decNum){
        this->decNum = decNum;
        preference = 0;
    }

    Code(int decNum, int pref){
        this->decNum = decNum;
        preference = pref;
    }

    Code() {
        decNum = 0;
        preference = 0;
    };

    friend std::ostream &operator<<(std::ostream &os, const Code &code);

};


#endif //GA_LABS1_3_CODE_H
