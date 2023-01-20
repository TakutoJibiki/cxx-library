#include <ostream>
#include <pair>

/*-----------------------------------------------
*
* std::pair の中身を出力
*
-----------------------------------------------*/
template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &stream, const std::pair<T1, T2> &data)
{
    std::cout << "(" << data.first << ", " << data.second << ")";
    return stream;
}
/*-----------------------------------------------
*
* std::tuple の中身を出力
*
-----------------------------------------------*/
template <typename... Args>
std::ostream &operator<<(std::ostream &stream, const std::tuple<Args...> &data)
{
    std::size_t param_size = sizeof...(Args);
    std::size_t cnt = 0;
    auto print = [&](auto it)
    {
        std::cout << (cnt == 0 ? "(" : "")
                  << it
                  << (cnt != param_size - 1 ? ", " : ")");
        ++cnt;
    };
    std::apply(
        [&](auto... args) constexpr { (print(args), ...); }, data);
    return stream;
}
/*-----------------------------------------------
*
* std::vector の中身を出力
*
-----------------------------------------------*/
template <typename T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> &arg)
{
    for (std::size_t i = 0; i < arg.size(); ++i)
    {
        if (i == 0)
            std::cout << "[";
        std::cout << arg[i];
        if (i != arg.size() - 1)
            std::cout << ", ";
        else
            std::cout << "]";
    }
    return stream;
}
