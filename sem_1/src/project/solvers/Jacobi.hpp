//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_JACOBI_HPP
#define SLAE_JACOBI_HPP
#include "../sparse/CSR.hpp"
#include "project/utility/Norm.hpp"
#include "project/utility/overloads.hpp"

template<typename T>
std::vector<T> Jacobi(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &initialState, const T &tolerance)
{
    std::vector<T> r = A * initialState - b;
    std::vector<T> currentState = initialState;
    std::vector<T> tempState(currentState.size());

    T sum;

    while (norm(r, NormType::ThirdNorm) > tolerance)
    {
        for (int i = 0; i < A.get_row_size(); ++i)
        {
            sum = static_cast<T>(0);
            int skip = A.rows_[i];
            int count = A.rows_[i + 1] - skip;
            for (int k = skip; k < skip + count; ++k)
            {
                if (A.cols_[k] != i)
                    sum += A.values_[k] * currentState[i];
            }
            tempState[i] = (b[i] - sum) / A(i, i);
        }

        currentState = tempState;
        r = A * currentState - b;
    }

    return currentState;
}

#endif//SLAE_JACOBI_HPP
