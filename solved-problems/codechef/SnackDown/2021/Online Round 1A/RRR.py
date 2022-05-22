# max, qty: [wins per team]
# 9, 1: 0 1 2 3 4 5 6 7 8 9
# 8, 3: 0 1 2 3 4 5 6 8 8 8
# 7, 5: 0 1 2 3 4 7 7 7 7 7
# 6, 7: 0 1 2 6 6 6 6 6 6 6

def solve(N, K):
    N -= 1
    K -= 1
    qty = (K >> 1) + (K & 1)
    N -= qty
    return N << 1


def solve_test_case(test_case):
    N, K = list(map(int, input().split()))
    print(solve(N, K))


def main():
    test_cases = int(input())
    for test_case in range(1, test_cases + 1):
        solve_test_case(test_case)


main()
