#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

constexpr std::string kInputFilename = "input.txt";
constexpr std::string kExampleFilename = "example.txt";

std::vector<std::vector<int>> read_input(const std::string &filename) {
  std::vector<std::vector<int>> data;

  if (std::ifstream file{filename}) {
    std::string line;
    std::vector<int> elf;
    while (std::getline(file, line)) {
      if (line.empty()) {
        data.push_back(elf);
        elf.clear();
      } else {
        elf.push_back(std::stoi(line));
      }
    }
    data.push_back(elf);
  }

  return data;
}

int solution_part_1(const std::vector<std::vector<int>> &data) {
  return std::ranges::max(data | std::views::transform([](auto &vec) {
                            return std::accumulate(vec.begin(), vec.end(), 0);
                          }));
}

int solution_part_2(const std::vector<std::vector<int>> &data) {
  auto sumed_view = data | std::views::transform([](auto &vec) {
                      return std::accumulate(vec.begin(), vec.end(), 0);
                    });
  std::vector<int> sum_values{sumed_view.begin(), sumed_view.end()};
  auto third = sum_values.end() - 3;
  std::nth_element(sum_values.begin(), third, sum_values.end());

  return std::accumulate(third, sum_values.end(), 0);
}

int main(int argc, const char *argv[]) {

  const std::string &filename =
      (argc > 1 && argv[1][0] == 'i') ? kInputFilename : kExampleFilename;

  auto data_set = read_input(filename);
  int solution_one = solution_part_1(data_set);
  int solution_two = solution_part_2(data_set);

  std::print("solution one: {}\nsolution two: {}\n", solution_one, solution_two);
}