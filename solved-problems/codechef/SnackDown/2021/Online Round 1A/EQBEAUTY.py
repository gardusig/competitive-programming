import bisect


def get_minimum_cost_to_make_array_equal(V):
    N = len(V)
    goal = V[N >> 1] if (N & 1) else ((V[N >> 1] + V[(N >> 1) - 1]) >> 1)
    ans = 0
    for i in V:
        ans += abs(goal - i)
    return ans


def solve(N, V):
    V.sort()

    ans = (1 << 60)

    # [0, ..., N - 2] | [N-1]
    ans = min(ans, get_minimum_cost_to_make_array_equal(V[0:-1]))

    # [0] | [1, ..., N-1]
    ans = min(ans, get_minimum_cost_to_make_array_equal(V[1:]))

    #          ----------------------
    # --------------------
    # [0, ..., [j, ..., i], ..., N-1]
    total = V[0] + V[-1]
    for i in range(1, N - 1):
        idx = bisect.bisect_left(V, total - V[i])
        L = max(1, idx - 2)
        R = min(i, idx + 2)
        for j in range(L, R):
            ans = min(ans, abs(total - (V[i] + V[j])))

    return ans


def solve_test_case(test_case):
    N = int(input())
    V = list(map(int, input().split()))
    print(solve(N, V))


def main():
    test_cases = int(input())
    for test_case in range(1, test_cases + 1):
        solve_test_case(test_case)


main()
