def solve() -> None:
    return None


def run_test(test_id: int) -> None:
    ans = solve()
    print(f'Case #{test_id}: {ans}')


T = int(input())
for test_id in range(1, T + 1):
    run_test(test_id)
