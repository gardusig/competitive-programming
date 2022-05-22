def solve_test_case(N):
    for i in range(1, N):
        print('M', i, N, flush=True)
        pos = int(input())
        if pos == i:
            continue
        print('S', i, pos, flush=True)
        response = int(input())
    print('D')
    response = int(input())
    assert response == 1


def main():
    T, N = map(int, input().split())
    while T > 0:
        T -= 1
        solve_test_case(N)


main()
