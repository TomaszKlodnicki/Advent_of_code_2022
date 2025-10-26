#include <algorithm>
#include <cassert>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <utility>
#include <vector>

constexpr std::string kInputFilename = "input.txt";
constexpr std::string kExampleFilename = "example.txt";

using DataSetType = std::vector<std::vector<char>>;

DataSetType read_input(const std::string &filename) {
  DataSetType data;

  if (std::ifstream file{filename}) {
    std::string line;
    while (std::getline(file, line)) {
      if (!line.empty()) {
        data.push_back(std::vector<char>{line.begin(), line.end()});
      }
    }
  }

  return data;
}

int solution_part_1(const DataSetType &data) {
  auto range =
      data | std::views::transform([](auto &a) {
        auto half = a.size() / 2;
        auto first_pair = a | std::views::take(half);
        auto first_set = std::set(first_pair.begin(), first_pair.end());
        auto filtered =
            a | std::views::drop(half) | std::views::filter([&](const auto &b) {
              return first_set.contains(b);
            });

        auto letter = *filtered.begin();
        auto value = (letter < 'a') ? (static_cast<int>(letter - 'A') + 27)
                                    : static_cast<int>(letter - 'a') + 1;
        return value;
      });

  return std::accumulate(range.begin(), range.end(), 0);
}

int solution_part_2(const DataSetType &data) {
    int return_value = 0;

  for (size_t i = 0; i < data.size(); i += 3) {
    auto set_1 =
        std::set<char>{(data.begin() + i)->begin(), (data.begin() + i)->end()};
    auto set_2 = std::set<char>{(data.begin() + i + 1)->begin(),
                                (data.begin() + i + 1)->end()};
    auto range =
        data[i + 2] |
        std::views::filter([&](const auto &a) { return set_1.contains(a); }) |
        std::views::filter([&](const auto &a) { return set_2.contains(a); });

    auto letter = *range.begin();
    auto value = (letter < 'a') ? (static_cast<int>(letter - 'A') + 27)
                                : static_cast<int>(letter - 'a') + 1;

    return_value += value;
  }

  return return_value;
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