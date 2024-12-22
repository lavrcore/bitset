

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Bitset {
private:
    vector<bool> bits;

public:
    Bitset(size_t size) : bits(size, false) {}

    // Перегрузка оператора []
    bool operator[](size_t index) const {
        if (index >= bits.size()) {
            throw std::out_of_range("Index out of range");
        }
        return bits[index];
    }
    void set(size_t index, bool value) {
        if (index >= bits.size()) {
            throw std::out_of_range("Index out of range");
        }
        bits[index] = value;
    }
    Bitset operator&(const Bitset& other) const {
        if (bits.size() != other.bits.size()) {
            throw invalid_argument("Bitsets must be of the same size");
        }
        Bitset result(bits.size());
        for (size_t i = 0; i < bits.size(); ++i) {
            result.set(i, bits[i] && other.bits[i]);
        }
        return result;
    }
    Bitset operator|(const Bitset& other) const {
        if (bits.size() != other.bits.size()) {
            throw std::invalid_argument("Bitsets must be of the same size");
        }
        Bitset result(bits.size());
        for (size_t i = 0; i < bits.size(); ++i) {
            result.set(i, bits[i] || other.bits[i]);
        }
        return result;
    }
    Bitset operator^(const Bitset& other) const {
        if (bits.size() != other.bits.size()) {
            throw std::invalid_argument("Bitsets must be of the same size");
        }
        Bitset result(bits.size());
        for (size_t i = 0; i < bits.size(); ++i) {
            result.set(i, bits[i] != other.bits[i]);
        }
        return result;
    }
    void leftShift(size_t count) {
        count %= bits.size();
        std::vector<bool> newBits(bits.size());
        for (size_t i = 0; i < bits.size(); ++i) {
            newBits[i] = bits[(i + count) % bits.size()];
        }
        bits = newBits;
    }
    void rightShift(size_t count) {
        count %= bits.size();
        vector<bool> newBits(bits.size());
        for (size_t i = 0; i < bits.size(); ++i) {
            newBits[i] = bits[(i + bits.size() - count) % bits.size()];
        }
        bits = newBits;
    }
    void print() const {
        for (bool bit : bits) {
            std::cout << bit;
        }
        std::cout << std::endl;
    }
};

int main() {
    Bitset b1(8);
    Bitset b2(8);

    b1.set(0, true);
    b1.set(1, true);
    b1.set(3, true);

    b2.set(2, true);
    b2.set(3, true);
    b2.set(4, true);

    cout << "Bitset 1: ";
    b1.print();
    cout << "Bitset 2: ";
    b2.print();

    Bitset andResult = b1 & b2;
    cout << "AND Result: ";
    andResult.print();

    Bitset orResult = b1 | b2;
    cout << "OR Result: ";
    orResult.print();

    Bitset xorResult = b1 ^ b2;
    cout << "XOR Result: ";
    xorResult.print();

    b1.leftShift(1);
    cout << "Left Shift Bitset 1: ";
    b1.print();

    b1.rightShift(2);
    cout << "Right Shift Bitset 1: ";
    b1.print();

    return 0;
}


