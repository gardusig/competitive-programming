def solve(X, K):
    mn = X << 1
    limit = X * K
    mx = limit * (limit - 1)
    return (mn, mx)


def solve_test_case(test_case):
    X, K = list(map(int, input().split()))
    print(*solve(X, K))


def main():
    test_cases = int(input())
    for test_case in range(1, test_cases + 1):
        solve_test_case(test_case)


main()
