#include <bits/stdc++.h>

class Solution
{
public:

    Solution()
    {
        std::ios_base::sync_with_stdio(0);
        std::cin.tie(0);
        std::cout.tie(0);
    }

    void main()
    {
        std::cin >> T;
        for (int test = 1; test <= T; test += 1)
        {
            readTask();
            solveTask(test);
        }
    }

private:

    void readTask()
    {
        std::cin >> D >> S;
        C.resize(S);
        E.resize(S);
        for (int i = 0; i < S; i += 1)
        {
            std::cin >> C[i] >> E[i];
        }
        A.resize(D);
        B.resize(D);
        for (int i = 0; i < D; i += 1)
        {
            std::cin >> A[i] >> B[i];
        }
    }

    void build()
    {
        v.clear();
        for (int i = 0; i < S; i += 1)
        {
            v.push_back({double(C[i]) / double(E[i]), i});
        }
        std::sort(v.rbegin(), v.rend());
        sumC.resize(S + 1);
        sumC[0] = 0;
        for (int i = 1; i <= S; i += 1)
        {
            sumC[i] = sumC[i - 1] + C[v[i - 1].second];
        }
        sumE.resize(S + 1);
        sumE[0] = 0;
        for (int i = 1; i <= S; i += 1)
        {
            sumE[i] = sumE[i - 1] + E[v[i - 1].second];
        }
    }

    std::string solve()
    {
        build();
        std::string ans = "";
        for (int i = 0; i < D; i += 1)
        {
            bool flag = false;
            if (sumC[S] >= A[i])
            {
                int lo = 1;
                int hi = S;
                while (lo <= hi)
                {
                    const int mid = lo + ((hi - lo) >> 1);
                    if (sumC[mid] < A[i])
                    {
                        lo = mid + 1;
                    }
                    else
                    {
                        hi = mid - 1;
                    }
                }
                const int j = lo;
                const int idx = v[j - 1].second;
                const double qtd = double(A[i] - sumC[j - 1]) / double(C[idx]);
                const double eat = (sumE[S] - sumE[j]) + ((1.0 - qtd) * E[idx]);
                if (eat >= B[i])
                {
                    flag = true;
                }
            }
            ans.push_back((flag == true) ? 'Y' : 'N');
        }
        return ans;
    }

    void solveTask(const int& test)
    {
        std::cout << "Case #" << test << ": " << solve() << std::endl;
    }

    int T;
    int D;
    int S;
    std::vector< int > C;
    std::vector< int > E;
    std::vector< int > A;
    std::vector< int > B;
    std::vector< std::pair< double, int > > v;
    std::vector< int > sumC;
    std::vector< int > sumE;
};

int main()
{
    Solution().main();
    return 0;
}