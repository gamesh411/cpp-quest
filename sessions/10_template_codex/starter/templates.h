#pragma once
#include <vector>

// ============================================================================
// REQUIRED TYPES AND CLASSES FOR TESTS
// ============================================================================

/**
 * Container<T> class template - A generic bounded collection
 *
 * Requirements for tests:
 * - Constructor: Container(capacity)
 * - add(const T&) - returns false if full
 * - remove(const T&) - returns false if not found
 * - find(const T&) const - returns const T* (nullptr if not found)
 * - size() const, capacity() const, isFull() const, clear()
 *
 * Hints:
 * - How do you search for an element in a vector?
 * - What does it mean to parameterize a class on a type?
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/language/class_template
 */
template <typename T>
class Container {
    // TODO: Implement Container
};

/**
 * Stat<T> class template - A numeric stat with min/max bounds
 *
 * Requirements for tests:
 * - Constructor: Stat(base, min, max) - current value starts at base
 * - modify(amount) - adds amount, keeps value within [min, max]
 * - set(value) - sets value, keeps within [min, max]
 * - get() const - returns current value
 * - getBase() const - returns base value
 * - reset() - restores current value to base
 *
 * Hints:
 * - Read the tests to see what types T can be (int, float, double)
 */
template <typename T>
class Stat {
    // TODO: Implement Stat
};

/**
 * clamp<T> function template
 * Returns value constrained to [min, max] range
 */
template <typename T>
T clamp(T value, T min, T max) {
    // TODO: Implement (currently just returns value unchanged)
    (void)min;
    (void)max;
    return value;
}

/**
 * swap<T> function template
 * Exchanges the values of a and b
 */
template <typename T>
void swap(T& a, T& b) {
    // TODO: Implement
    (void)a;
    (void)b;
}
