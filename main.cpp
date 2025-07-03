#include <iostream>
#include <memory>

template <int ind, int head, int... tail>
struct Get {
    static constexpr int val = (ind <= 0 ? head : Get<ind - 1, tail...>::val);
};

template <int ind, int head>
struct Get<ind, head> {
    static constexpr int val = head;
};

template <int el, int ind, int curr_ind, int Head, int... Tail>
struct CntGreatest {
    static constexpr int cnt = ((ind != curr_ind && el > Head || ind > curr_ind && el == Head) ? 1 : 0) +
                               CntGreatest<el, ind, curr_ind + 1, Tail...>::cnt;
};

template <int el, int ind, int curr_ind, int Head>
struct CntGreatest<el, ind, curr_ind, Head> {
    static constexpr int cnt = ((ind != curr_ind && el > Head || ind > curr_ind && el == Head)) ? 1 : 0;
};

template <int size, int ind, int cnt, int Head, int... Tail>
struct FindElementWithCntGreatest {
    static constexpr int el = (CntGreatest<Get<ind, Head, Tail...>::val, ind, 0, Head, Tail...>::cnt == cnt)
                                  ? Get<ind, Head, Tail...>::val
                                  : FindElementWithCntGreatest<size, ind + 1, cnt, Head, Tail...>::el;
};

template <int ind, int cnt, int Head, int... Tail>
struct FindElementWithCntGreatest<ind, ind, cnt, Head, Tail...> {
    static constexpr int el = Get<ind, Head, Tail...>::val;
};

template <int i, int size, int Head, int... Tail>
void print() {  // выводит элемент, перед которым i больших (не меньших) чисел
    std::cout << FindElementWithCntGreatest<size, 0, i, Head, Tail...>::el << " ";
    if constexpr (i + 1 < size) {
        print<i + 1, size, Head, Tail...>();
    }
}

template <int... Args>
void print_sorted() {
    print<0, sizeof...(Args), Args...>();
    std::cout << "\n";
}



int main() {
    // доп память - 0(1)
    print_sorted<4, 3, 1, 2, 5>();                         // 1 2 3 4 5
    print_sorted<4, 1, 5, 5, 5>();                         // 1 4 5 5 5
    print_sorted<4, 1, 1, 1, 1>();                         // 1 1 1 1 4
    print_sorted<4, 1, 1, 5, 5>();                         // 1 1 4 5 5
    print_sorted<5, 1, 2, 2, 3>();                         // 1 2 2 3 5
    print_sorted<1, 1, 1, 1, 1>();                         // 1 1 1 1 1
    print_sorted<5, 4, 3, 2, 1>();                         // 1 2 3 4 5
    print_sorted<1, 2, 3, 4, 5, 5, 5, 63, 2, 3, 32, 3>();  // 1 2 2 3 3 3 4 5 5 5 32 63

}


