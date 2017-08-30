#pragma once

/*
 * Just having a play for now.
 */

#include <cmath>

class MathElement
{
public:
    std::string id;
    std::vector<MathElement> children;
    enum ElementType
    {
        MATH_ELEMENT,
        APPLY_ELEMENT,
        PREDEFINED_SYMBOL,
        CN_ELEMENT,
        CI_ELEMENT,
        BVAR_ELEMENT,
        CASE_ELEMENT,
        PIECEWISE_ELEMENT
    };

    virtual enum ElementType getType() const;
};

class Math
{

}; // class Math
