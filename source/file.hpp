#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <filesystem>

void read_csv(std::vector<std::vector<double>> &table,
              const std::string path,
              bool header = false,
              bool index = false,
              bool verbose = true,
              const std::pair<size_t, size_t> size = std::pair<size_t, size_t>{0, 0});
void to_csv(const std::vector<double> &table, const std::string path);
void to_csv(const std::vector<std::vector<double>> &table,
            const std::string path,
            const std::vector<std::string> &header = std::vector<std::string>(),
            const bool index = false);

std::vector<std::string> glob(const std::string path);
