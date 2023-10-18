#include "file.hpp"
#include "utility.hpp"
using std::cout, std::endl;

/*-----------------------------------------------
*
* CSV ファイル読み込み
*
-----------------------------------------------*/
void read_csv(std::vector<std::vector<double>> &table,
              const std::string path,
              bool header,
              bool index,
              bool verbose,
              const std::pair<int, int> size)
{
    std::ifstream ifs(path);
    assert(ifs);
    std::string line;

    if (header)
        ifs >> line;

    if (size == std::pair<int, int>{0, 0})
    {
        int cnt1 = 0;
        int cnt2 = 0;
        table.clear();

        while (ifs >> line, !ifs.eof())
        {
            if (verbose)
            {
                cnt1 += 1;
                if (cnt1 % 10 == 0)
                {
                    cnt2 += 1;
                    cnt2 %= 3;
                }
                cout << "\rCSV loading";
                for (int i = 0; i < cnt2 + 1; ++i)
                    cout << ".";
                cout << std::flush;
            }

            /* 読み込み */
            auto s = split(line, ',');
            if (index)
                s = std::vector<std::string>(s.begin() + 1, s.end());

            std::vector<double> tmp(s.size());
            for (int i = 0; i < s.size(); ++i)
                tmp[i] = std::stod(s[i]);
            table.emplace_back(tmp);
        }
        if (verbose)
            cout << endl;
    }
    else
    {
        auto [rows, cols] = size;
        table = std::vector<std::vector<double>>(rows, std::vector<double>(cols));

        for (int i = 0; i < rows; ++i)
        {
            if (verbose)
                cout << "\rCSV loading... " << int((i + 1) * 100.0 / rows) << " %" << std::flush;
            ifs >> line;
            auto s = split(line, ',');

            if (index)
                s = std::vector<std::string>(s.begin() + 1, s.end());

            assert(s.size() == cols);
            for (int j = 0; j < cols; ++j)
                table[i][j] = std::stod(s[j]);
        }
        if (verbose)
            cout << endl;
        ifs >> line;
        assert(ifs.eof());
    }
}

/*-----------------------------------------------
*
* CSV ファイル書き出し
*
-----------------------------------------------*/
void to_csv(const std::vector<double> &table, const std::string path)
{
    std::ofstream ofs(path);
    assert(ofs);

    for (auto i : table)
        ofs << i << endl;
}

void to_csv(const std::vector<std::vector<double>> &table,
            const std::string path,
            const std::vector<std::string> &header,
            const bool index)
{
    std::ofstream ofs(path);
    assert(ofs);

    if (!header.empty())
    {
        assert(header.size() == table[0].size());
        if (index)
            ofs << ",";
        ofs << join(header, ',') << endl;
    }

    for (int i = 0; i < table.size(); ++i)
    {
        if (index)
            ofs << i << ",";
        ofs << join(table[i], ',') << endl;
    }
}

/*-----------------------------------------------
*
* ファイル列挙
*
-----------------------------------------------*/
std::vector<std::string> glob(const std::string path)
{
    std::vector<std::string> dst;
    for (const std::filesystem::directory_entry &x : std::filesystem::directory_iterator(path))
        dst.emplace_back(x.path());
    return std::move(dst);
}
