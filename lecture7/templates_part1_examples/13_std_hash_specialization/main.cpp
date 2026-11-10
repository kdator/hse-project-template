#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>

struct Document {
    std::string title;
    int year;
    bool operator==(const Document& o) const {
        return title == o.title && year == o.year;
    }
};

namespace std {

template <>
struct hash<Document> {
    size_t operator()(const Document& d) const noexcept {
        return hash<string>{}(d.title) ^ (hash<int>{}(d.year) << 1);
    }
};

}

int main() {
    std::unordered_set<Document> docs;      // хешер не передаётся
    docs.insert({"Dune", 1965});
    docs.insert({"Dune", 1965});            // дубликат
    docs.insert({"Solaris", 1961});
    std::cout << "size = " << docs.size() << '\n';
}
