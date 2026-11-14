#include <iostream>
#include <memory>

#include "collection.hpp"
#include "types.hpp"

int main() {
    Collection<Plain> plain;
    plain.add(Plain("templates"));
    plain.add(Plain("are"));
    plain.add(Plain("generic"));
    for (const Plain& p : plain)
        std::cout << p.myValue() << '\n';
    std::cout << "Plain:      " << joinValues(plain) << " (size " << plain.size() << ")\n";

    Collection<Reversed> reversed;
    reversed.add(Reversed("abc"));
    reversed.add(Reversed("stack"));
    std::cout << "Reversed:   " << joinValues(reversed) << '\n';

    Collection<Upper> upper;
    upper.add(Upper("hello"));
    upper.add(Upper("World"));
    std::cout << "Upper:      " << joinValues(upper) << '\n';

    Collection<Constant> constants;
    constants.add(Constant{});
    constants.add(Constant{});
    std::cout << "Constant:   " << joinValues(constants, ", ") << '\n';

    Collection<AsciiCodes> codes;
    codes.add(AsciiCodes("Hi"));
    codes.add(AsciiCodes("C++"));
    std::cout << "AsciiCodes: " << joinValues(codes) << '\n';

    Upper a("ptr"), b("to");
    Collection<Upper*> pointers;
    pointers.add(&a);
    pointers.add(&b);
    std::cout << "Upper*:     " << joinValues(pointers) << '\n';

    Collection<std::unique_ptr<Reversed>> owners;
    owners.add(std::make_unique<Reversed>("olleh"));
    owners.add(std::make_unique<Reversed>("dlrow"));
    std::cout << "unique_ptr: " << joinValues(owners) << '\n';
}
