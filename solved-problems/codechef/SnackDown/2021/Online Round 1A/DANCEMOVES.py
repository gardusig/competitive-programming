def solve(X, Y):
    if X >= Y:
        return X - Y
    diff = (Y - X) >> 1
    if X + (diff << 1) == Y:
        return diff
    return diff + 2


def solve_test_case(test_case):
    X, Y = list(map(int, input().split()))
    print(solve(X, Y))


def main():
    test_cases = int(input())
    for test_case in range(1, test_cases + 1):
        solve_test_case(test_case)


main()
