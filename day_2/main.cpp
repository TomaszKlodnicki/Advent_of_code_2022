#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <utility>
#include <vector>

constexpr std::string kInputFilename = "input.txt";
constexpr std::string kExampleFilename = "example.txt";

const std::set<char> allowed_chars{'A', 'B', 'C', 'X', 'Y', 'Z'};

struct Sign {
  Sign(const char &in) {
    assert(allowed_chars.contains(in));
    value = in;
  }

  char value;

  Sign converted_for_sol_1() const {
    if (this->value > 'C')
      return Sign{static_cast<char>(this->value - 'X' + 'A')};
    else
      return Sign{this->value};
  }

  bool operator>(const Sign &other) const {
    switch (this->value) {
    case 'A':
      if (other.value == 'C')
        return true;
      return false;
    case 'B':
      if (other.value == 'A')
        return true;
      return false;
    case 'C':
      if (other.value == 'B')
        return true;
      return false;
    }
    assert(false);
    return false;
  };

  bool operator==(const Sign &other) const {
    return this->value == other.value;
  }

  int sol_1(const Sign &other) const {
    return converted_for_sol_1().fight(other);
  }

  Sign reverse() const {
    switch (this->value) {
    case 'C':
      return {'A'};
    case 'A':
    case 'B':
      return {static_cast<char>(this->value + 1)};
    }
    assert(false);
    return {'A'};
  }

  int sol_2(const Sign &other) const {
    if (this->value == 'X')
      return other.reverse().reverse().bonus();
    if (this->value == 'Y')
      return 3 + other.bonus();
    if (this->value == 'Z')
      return 6 + other.reverse().bonus();

    assert(false);
    return 0;
  }

  int fight(const Sign &other) const {
    if (*this == other)
      return 3 + this->bonus();

    if (*this > other)
      return 6 + this->bonus();

    return this->bonus();
  }

  int bonus() const { return static_cast<int>(value - 'A' + 1); }
};

using DataSetType = std::vector<std::pair<Sign, Sign>>;

DataSetType read_input(const std::string &filename) {
  DataSetType data;

  if (std::ifstream file{filename}) {
    std::string line;
    while (std::getline(file, line)) {
      if (!line.empty()) {
        data.push_back(std::make_pair<Sign, Sign>({line[0]}, {line[2]}));
      }
    }
  }

  return data;
}

int solution_part_1(const DataSetType &data) {
  auto range = data | std::views::transform(
                          [](auto &a) { return a.second.sol_1(a.first); });
  return std::accumulate(range.begin(), range.end(), 0);
}

int solution_part_2(const DataSetType &data) {
  auto range = data | std::views::transform(
                          [](auto &a) { return a.second.sol_2(a.first); });
  return std::accumulate(range.begin(), range.end(), 0);
}

int main(int argc, const char *argv[]) {

  const std::string &filename =
      (argc > 1 && argv[1][0] == 'i') ? kInputFilename : kExampleFilename;

  auto data_set = read_input(filename);
  int solution_one = solution_part_1(data_set);
  int solution_two = solution_part_2(data_set);

  std::print("solution one: {}\nsolution two: {}\n", solution_one,
             solution_two);
}