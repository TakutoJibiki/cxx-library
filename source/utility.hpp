#pragma once
#include <chrono>
#include <vector>
#include <string>
#include <exception>
#include <fstream>
#include "picojson.h"

std::vector<std::string> split(std::string str, char del);
std::string get_filename(const std::string &path);
void get_filepath(const std::string &target_dir, std::vector<std::string> &filepaths);
bool filename_comparator(const std::string &a, const std::string &b);
std::string join(const std::vector<std::string> vec, const char sep);
std::string join(const std::vector<double> vec, const char sep);

/*-----------------------------------------------
*
* 時間
*
-----------------------------------------------*/
using time_point = std::chrono::system_clock::time_point; /* get_time で使用する型 */

/* 時間を取得 */
inline time_point get_time(void) noexcept { return std::chrono::system_clock::now(); }

double calc_sec(time_point start, time_point end = get_time()); /* 時間差を計算 */
const std::string calc_passed_time(time_point time);

/*-----------------------------------------------
*
* json
*
-----------------------------------------------*/
/* picojson は動作が重いため繰り返し処理では使わないこと */
/* TODO : 存在しないキーが指定されたときの例外処理 */
class PicojsonWrapper
{
    using obj = picojson::object;

public:
    PicojsonWrapper(const std::string json_path)
    {
        std::ifstream ifs(json_path);
        if (!ifs)
            throw std::runtime_error("cannot open " + json_path);
        ifs >> val;
    }

    template <typename T>
    T get(const std::string key) const
    {
        try
        {
            auto s = split(key, '/');
            return get_val(s).get<T>();
        }
        catch (std::exception &e)
        {
            throw std::runtime_error("picojson key error. [" + key + "]");
        }
    }

public:
    picojson::value val;

private:
    picojson::value get_val(std::vector<std::string> keys) const
    {
        if (keys.size() == 1)
            return val.get<obj>().at(keys.back());
        auto next_key = keys.back();
        keys.erase(keys.end() - 1);
        return get_val(keys).get<obj>().at(next_key);
    }
};
