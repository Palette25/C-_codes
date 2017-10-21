#include"Bitset.h"
bitset::bitset() {
    for (int i = 0; i < N; i++) a[i] = 0;
}
void bitset::set(int pos) {
    int x = pos / 32;
    int y = pos % 32;
    a[x] |= 1 << y;
}
void bitset::reset(int pos) {
    int x = pos / 32;
    int y = pos % 32;
    a[x] &= ~(1 << y);
}
int bitset::count() const {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 32; j++) {
            if (a[i] & (1 << j)) sum++;
        }
    }
    return sum;
}
bool bitset::test(int pos) const {
    int x = pos / 32;
    int y = pos % 32;
    return (a[x] & (1 << y));
}
bool bitset::any() const {
    return count() > 0;
}
bool bitset::none() const {
    return count() == 0;
}
bool bitset::all() const {
    return count() == max_length;
}
bitset& bitset::operator&= (const bitset& b) {
    for (int i = 0; i < N; i++) a[i] &= b.a[i];
    return *this;
}
bitset& bitset::operator|= (const bitset& b) {
    for (int i = 0; i < N; i++) a[i] |= b.a[i];
    return *this;
}
bitset& bitset::operator^= (const bitset& b) {
    for (int i = 0; i < N; i++) a[i] ^= b.a[i];
    return *this;
}
bitset& bitset::operator <<= (int pos) {
    while (pos--) {
        for (int i = N-1; i >= 0; i--) {
            if (i == 0) {
                a[i] <<= 1;
                continue;
            }
            a[i] <<= 1;
            if (a[i-1] & (1 << 31))
                a[i] |= 1;
            else
                a[i] &= ~1;
        }
    }
    return *this;
}
bitset& bitset::operator>>= (int pos) {
    while (pos--) {
        for (int i = 0; i < N; i++) {
            if (i == N-1) {
                a[i] >>= 1;
                continue;
            }
            a[i] >>= 1;
            if (a[i+1] & 1)
                a[i] |= 1 << 31;
            else
                a[i] &= ~(1 << 31);
        }
    }
    return *this;
}
bitset& bitset::operator= (const bitset& b) {
    for (int i = 0; i < N; i++) a[i] = b.a[i];
    return *this;
}
bitset bitset::operator~() const {
    bitset s;
    for (int i = 0; i < N; i++) s.a[i] = ~a[i];
    return s;
}
bitset bitset::operator& (const bitset& b) const {
    bitset s;
    s = *this;
    return s &= b;
}
bitset bitset::operator| (const bitset& b) const {
    bitset s;
    s = *this;
    return s |= b;
}
bitset bitset::operator^ (const bitset& b) const {
    bitset s;
    s = *this;
    return s ^= b;
}
bitset bitset::operator << (int pos) const {
    bitset s;
    s = *this;
    return s <<= pos;
}
bitset bitset::operator >> (int pos) const {
    bitset s;
    s = *this;
    return s >>= pos;
}
bool bitset::operator== (const bitset& b) const {
    for (int i = 0; i < N; i++)
        if (a[i] != b.a[i]) return false;
    return true;
}
bool bitset::operator!= (const bitset& b) const {
    for (int i = 0; i < N; i++)
        if (a[i] != b.a[i]) return true;
    return false;
}
bool bitset::operator[] (int pos) const {
    int x = pos / 32;
    int y = pos % 32;
    return a[x] & (1 << y);
}
 