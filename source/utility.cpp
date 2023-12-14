#include <iostream>
#include <cmath>
#include <filesystem>
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
std::vector<double> split_d(std::string str, char del)
{
    auto s = split(str, del);
    std::vector<double> ret(s.size());
    for (size_t i = 0; i < s.size(); ++i)
        ret[i] = std::stod(s[i]);
    return ret;
}

/*-----------------------------------------------
*
* パスの文字列からファイル名を取得
*
-----------------------------------------------*/
std::string get_filename(const std::string &path)
{
    std::filesystem::path p(path);
    return p.stem();
}

/*-----------------------------------------------
*
* 指定したディレクトリ内のファイルパスを取得する
*
-----------------------------------------------*/
void get_filepath(const std::string &target_dir, std::vector<std::string> &filepaths)
{
    filepaths.clear();
    for (const auto &x : std::filesystem::directory_iterator(target_dir))
        filepaths.emplace_back(x.path());
}

/*-----------------------------------------------
*
* 複数のパスの文字列をファイル名の数字順にソートするための比較関数
*
* 使用例
* std::sort(img_paths.begin(), img_paths.end(), filename_comparator);
*
-----------------------------------------------*/
bool filename_comparator(const std::string &a, const std::string &b)
{
    std::filesystem::path ap(a);
    int ai = std::stoi(ap.stem());
    std::filesystem::path bp(b);
    int bi = std::stoi(bp.stem());
    return ai < bi;
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
* 経過時間を計算
*
-----------------------------------------------*/
const std::string calc_passed_time(time_point time)
{
    std::string ret;
    auto passed_time = calc_sec(time);
    ret += std::to_string(int(std::floor(passed_time / 3600))) + " (h) ";
    passed_time -= std::floor(passed_time / 3600) * 3600;
    ret += std::to_string(int(std::floor(passed_time / 60))) + " (m) ";
    passed_time -= std::floor(passed_time / 60) * 60;
    ret += std::to_string(int(std::floor(passed_time))) + " (s)";
    return ret;
}

/*-----------------------------------------------
*
* リストを連結して文字列に
*
-----------------------------------------------*/
std::string join(const std::vector<std::string> vec, const char sep)
{
    std::string dst = "";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        dst += vec[i];
        if (i < vec.size() - 1)
            dst += ",";
    }
    return dst;
}

std::string join(const std::vector<double> vec, const char sep)
{
    std::string dst = "";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        dst += std::to_string(vec[i]);
        if (i < vec.size() - 1)
            dst += ",";
    }
    return dst;
}

/*-----------------------------------------------
*
* 与えられた数列を一定間隔に分割
*
-----------------------------------------------*/
std::vector<double> discretize(const std::vector<double> &in, const double step)
{
    std::vector<double> discretized{in[0]};
    for (int i = 1; i < int(in.size()); ++i)
    {
        double x1 = in[i - 1];
        double x2 = in[i];
        double dx = x2 - x1;
        int n = std::abs(int(dx / step));

        for (int j = 0; j < n; ++j)
        {
            double cand = x1 + step * (j + 1) * sign(dx);
            if (cand * sign(dx) < x2 * sign(dx))
                discretized.push_back(cand);
        }
        discretized.push_back(x2);
    }
    return discretized;
}