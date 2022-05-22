def solve_test_case(test_case):
    lucky_digit = 7
    digits = set(map(int, input().split()))
    if lucky_digit in digits:
        print('YES')
    else:
        print('NO')


def main():
    test_cases = int(input())
    for test_case in range(1, test_cases + 1):
        solve_test_case(test_case)


main()
