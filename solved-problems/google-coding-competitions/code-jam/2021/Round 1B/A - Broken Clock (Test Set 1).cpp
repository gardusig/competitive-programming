#include <bits/stdc++.h>

const int64_t NANO = 1'000'000'000;
const int64_t SECONDS = 60;
const int64_t MINUTES = 60;
const int64_t HOURS = 12;

bool is_valid(int64_t hour, int64_t minute, int64_t second) {
  if (hour < 0 or minute < 0 or second < 0) {
    return false;
  }
  if (minute % HOURS) {
    return false;
  }
  minute /= HOURS;
  if (second % (HOURS * MINUTES)) {
    return false;
  }
  second /= (HOURS * MINUTES);

  const int64_t hour_nano = hour % NANO;
  hour /= NANO;
  const int64_t hour_seconds = hour % SECONDS;
  hour /= SECONDS;
  const int64_t hour_minutes = hour % MINUTES;
  hour /= MINUTES;
  const int64_t hour_hours = hour;

  const int64_t minute_nano = minute % NANO;
  minute /= NANO;
  const int64_t minute_seconds = minute % SECONDS;
  minute /= SECONDS;
  const int64_t minute_minutes = minute % MINUTES;
  minute /= MINUTES;
  const int64_t minute_hours = minute;

  const int64_t second_nano = second % NANO;
  second /= NANO;
  const int64_t second_seconds = second % SECONDS;
  second /= SECONDS;
  const int64_t second_minutes = second % MINUTES;
  second /= MINUTES;
  const int64_t second_hours = second;

  if (second_nano != minute_nano or second_seconds != minute_seconds or
      second_minutes > minute_minutes or second_hours > hour_hours) {
    return false;
  }
  if (minute_nano != hour_nano or minute_seconds != hour_seconds or
      minute_minutes != hour_minutes or minute_hours > hour_minutes) {
    return false;
  }
  return true;
}

void solve_test_case(const int test) {
  std::vector<int64_t> v(3);
  for (auto& i : v) {
    std::cin >> i;
  }
  std::sort(v.begin(), v.end());
  bool valid = false;
  do {
    for (int rotation = 0; rotation < 60 * 60 * 12; rotation += 1) {
      for (auto& i : v) {
        i += 1LL * 1'000'000'000 * rotation;
      }
      if (is_valid(v[0], v[1], v[2])) {
        valid = true;
        break;
      }
      for (auto& i : v) {
        i -= 1LL * 1'000'000'000 * rotation;
      }

      for (auto& i : v) {
        i -= 1LL * 1'000'000'000 * rotation;
      }
      if (is_valid(v[0], v[1], v[2])) {
        valid = true;
        break;
      }
      for (auto& i : v) {
        i += 1LL * 1'000'000'000 * rotation;
      }
    }
  } while (!valid and std::next_permutation(v.begin(), v.end()));
  assert(valid);
  int64_t value = v[0];
  const int64_t nano = value % NANO;
  value /= NANO;
  const int64_t seconds = value % SECONDS;
  value /= SECONDS;
  const int64_t minutes = value % MINUTES;
  value /= MINUTES;
  const int64_t hours = value % HOURS;
  std::cout << "Case #" << test << ": " << hours << " " << minutes << " "
            << seconds << " " << nano << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  int T;
  std::cin >> T;
  for (int test = 1; test <= T; test += 1) {
    solve_test_case(test);
  }
  return 0;
}