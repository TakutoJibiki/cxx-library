#include "utility.hpp"

/*-----------------------------------------------
*
* del 区切りで文字列を vector に分割
*
-----------------------------------------------*/
std::vector<std::string> split(std::string str, char del)
{
    auto get_last = [](std::string str, char del, std::size_t first)
    {
        auto last = str.find_first_of(del, first);
        return (last != std::string::npos ? last : str.size());
    };

    std::size_t first = 0;
    std::size_t last = get_last(str, del, first);
    std::vector<std::string> ret;

    while (first < str.size())
    {
        std::string sub_str(str, first, last - first);
        ret.emplace_back(sub_str);
        first = last + 1;
        last = get_last(str, del, first);
    }
    return ret;
}

/*-----------------------------------------------
*
* 時間差を計算
*
-----------------------------------------------*/
double calc_sec(time_point start, time_point end)
{
    double duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return duration * 1E-6;
}

/*-----------------------------------------------
*
* 経過時間を出力
*
-----------------------------------------------*/
void print_passed_time(time_point time)
{
    auto passed_time = calc_sec(time);
    std::cout << std::floor(passed_time / 3600) << " (h) ";
    passed_time -= std::floor(passed_time / 3600) * 3600;
    std::cout << std::floor(passed_time / 60) << " (m) ";
    passed_time -= std::floor(passed_time / 60) * 60;
    std::cout << std::floor(passed_time) << " (s)" << std::endl;
}