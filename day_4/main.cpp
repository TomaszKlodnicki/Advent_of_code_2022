#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <vector>

constexpr std::string kInputFilename = "input.txt";
constexpr std::string kExampleFilename = "example.txt";

using DataSetType = std::vector<std::string>;

DataSetType read_input(const std::string &filename) {
  DataSetType data;

  if (std::ifstream file{filename}) {
    std::string line;
    while (std::getline(file, line)) {
      if (!line.empty()) {
        data.push_back(line);
      }
    }
  }

  return data;
}

std::array<std::array<int, 2>, 2> parse_record(const std::string &record) {
  std::array<std::array<int, 2>, 2> nums;
  int count = std::sscanf(record.data(), "%d-%d,%d-%d", &nums[0][0],
                          &nums[0][1], &nums[1][0], &nums[1][1]);

  if (count != 4) {
    throw std::runtime_error("Failed to parse record: " + record);
  }
  assert(nums[0][0] <= nums[0][1]);
  assert(nums[1][0] <= nums[1][1]);
  return nums;
}

bool is_fully_contained(const std::array<std::array<int, 2>, 2> &nums) {
  return (nums[0][0] >= nums[1][0] && nums[0][1] <= nums[1][1]) ||
         (nums[1][0] >= nums[0][0] && nums[1][1] <= nums[0][1]);
}

bool is_overlapping(const std::array<std::array<int, 2>, 2> &nums) {
  return !(nums[0][1] < nums[1][0] || nums[1][1] < nums[0][0]);
}

int solution_part_1(const DataSetType &data) {
  auto range = data | std::views::transform(parse_record) |
               std::views::filter(is_fully_contained);

  return std::ranges::distance(range);
}

int solution_part_2(const DataSetType &data) {
  auto range = data | std::views::transform(parse_record) |
               std::views::filter(is_overlapping);
  return std::ranges::distance(range);
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