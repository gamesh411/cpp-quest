# Session 10: Template Codex

## 🎯 Quest Overview

**Narrative:** *"Discover the ultimate abstraction: spells that work on any type of magic. The power of templates awaits."*

**Learning Objectives:**
- Understand function templates
- Implement class templates
- Use template specialization
- Apply type deduction
- Master template best practices
- Understand when to use templates

**Estimated Time:** 3 hours

---

## 📖 Background Story

You've mastered classes, inheritance, and polymorphism. But you notice repetition: a `Stack` for integers, another for strings, another for characters. Each implementation is nearly identical, just with different types.

The ancient **Template Codex** reveals the solution: write code once, use it with any type. This is **generic programming** - the ultimate form of code reuse.

---

## 🎓 Concepts Covered

### 1. Function Templates

```cpp
// Without templates: repetition
int max(int a, int b) { return a > b ? a : b; }
double max(double a, double b) { return a > b ? a : b; }
std::string max(std::string a, std::string b) { return a > b ? a : b; }

// With templates: write once
template<typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

// Usage - type deduced automatically
int i = max(5, 10);           // T = int
double d = max(3.14, 2.71);   // T = double
std::string s = max("hello", "world");  // T = std::string
```

**Key:** Compiler generates specific version for each type used.

### 2. Class Templates

```cpp
template<typename T>
class Stack {
private:
    std::vector<T> data_;
    
public:
    void push(const T& item) {
        data_.push_back(item);
    }
    
    T pop() {
        T item = data_.back();
        data_.pop_back();
        return item;
    }
    
    bool empty() const {
        return data_.empty();
    }
    
    size_t size() const {
        return data_.size();
    }
};

// Usage - must specify type
Stack<int> intStack;
intStack.push(42);

Stack<std::string> stringStack;
stringStack.push("hello");
```

### 3. Template Specialization

```cpp
// Primary template
template<typename T>
class Printer {
public:
    void print(const T& value) {
        std::cout << value << "\n";
    }
};

// Specialization for bool
template<>
class Printer<bool> {
public:
    void print(const bool& value) {
        std::cout << (value ? "true" : "false") << "\n";
    }
};

Printer<int> p1;
p1.print(42);  // "42"

Printer<bool> p2;
p2.print(true);  // "true" (not "1")
```

### 4. Type Deduction

```cpp
template<typename T>
void process(T value) {
    // T deduced from argument
}

process(42);        // T = int
process(3.14);      // T = double
process("hello");   // T = const char*

// Explicit specification
process<int>(42);
process<double>(3.14);
```

### 5. Multiple Template Parameters

```cpp
template<typename K, typename V>
class Pair {
private:
    K key_;
    V value_;
    
public:
    Pair(const K& key, const V& value)
        : key_(key), value_(value) {}
    
    K getKey() const { return key_; }
    V getValue() const { return value_; }
};

Pair<std::string, int> p("age", 25);
std::cout << p.getKey() << ": " << p.getValue() << "\n";
```

### 6. Template Constraints (C++20 Concepts)

```cpp
#include <concepts>

// Concept: type must be comparable
template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
};

// Only works with Comparable types
template<Comparable T>
T max(T a, T b) {
    return a > b ? a : b;
}

max(5, 10);      // OK: int is Comparable
max("a", "b");   // OK: const char* is Comparable
// max(SomeClass{}, SomeClass{});  // Error if not Comparable
```

---

## 🎮 Core Quest: Generic Game Systems

### Requirements

Implement generic game systems using templates:

#### 1. `Container<T>` Template

```cpp
template<typename T>
class Container {
private:
    std::vector<T> items_;
    size_t capacity_;

public:
    Container(size_t capacity);
    
    bool add(const T& item);
    bool remove(const T& item);
    const T* find(const T& item) const;
    size_t size() const;
    size_t capacity() const;
    bool isFull() const;
    void clear();
};
```

#### 2. `Stat<T>` Template

```cpp
template<typename T>
class Stat {
private:
    T baseValue_;
    T currentValue_;
    T minValue_;
    T maxValue_;

public:
    Stat(T base, T min, T max);
    
    void modify(T amount);
    void set(T value);
    T get() const;
    T getBase() const;
    void reset();
};
```

#### 3. Generic Functions

```cpp
template<typename T>
T clamp(T value, T min, T max);

template<typename T>
void swap(T& a, T& b);

template<typename Container, typename T>
bool contains(const Container& container, const T& value);
```

### Success Criteria

✅ Function templates work with multiple types  
✅ Class templates instantiate correctly  
✅ Template specialization (if needed)  
✅ Type deduction works  
✅ All tests pass  
✅ Code compiles with `-Wall -Wextra -Werror`  

---

## 🧪 Testing Your Implementation

```bash
# Build and run tests
cd cpp-quest
cmake -B build
cmake --build build
./build/sessions/10_template_codex/test_session10

# Run demo
./build/sessions/10_template_codex/template_demo
```

**Expected Output:**
```
================================
  TEMPLATE CODEX
================================

Testing Container<int>...
✓ Added 5 items
✓ Container size: 5
✓ Found item: 42

Testing Container<string>...
✓ Added 3 items
✓ Container size: 3
✓ Found item: hello

Testing Stat<int>...
✓ Base: 100, Current: 100
✓ Modified by +20: 120
✓ Modified by -50: 70
✓ Reset to base: 100

Testing Stat<double>...
✓ Base: 1.0, Current: 1.0
✓ Modified by +0.5: 1.5

Testing generic functions...
✓ clamp(15, 0, 10) = 10
✓ swap(a, b) works
✓ contains() found element
```

---

## 🌟 Side Quests (Optional)

### Side Quest 1: Generic Inventory
**XP:** +50

```cpp
template<typename Item>
class Inventory {
    Container<Item> items_;
public:
    bool addItem(const Item& item);
    bool removeItem(const Item& item);
    Item* findItem(const std::string& name);
};
```

### Side Quest 2: Template Specialization
**XP:** +50

Specialize `Stat` for `bool`:
```cpp
template<>
class Stat<bool> {
    // Boolean stats work differently
};
```

### Side Quest 3: Concepts (C++20)
**XP:** +50

```cpp
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
T average(const std::vector<T>& values);
```

### Side Quest 4: Type Demangling & Debugging
**XP:** +50

Implement type name utilities for template debugging:

```cpp
#include <typeinfo>
#include <string>
#include <cxxabi.h>  // GCC/Clang only

// Get human-readable type name
template<typename T>
std::string type_name() {
    int status;
    char* demangled = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
    std::string result = (status == 0) ? demangled : typeid(T).name();
    free(demangled);
    return result;
}

// Usage:
std::cout << type_name<int>() << "\n";  // "int"
std::cout << type_name<std::vector<std::string>>() << "\n";  // "std::vector<std::string, ...>"

// Type detection utility
template<typename T>
void print_type_info() {
    std::cout << "Type: " << type_name<T>() << "\n";
    std::cout << "Size: " << sizeof(T) << " bytes\n";
    std::cout << "Is const: " << std::is_const_v<T> << "\n";
    std::cout << "Is reference: " << std::is_reference_v<T> << "\n";
    std::cout << "Is pointer: " << std::is_pointer_v<T> << "\n";
}
```

**Task:** Create comprehensive type inspection tool for debugging templates.

### Side Quest 5: Template Metaprogramming Basics
**XP:** +50

Explore compile-time computation:

```cpp
// Compile-time factorial
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

// Usage:
constexpr int f5 = Factorial<5>::value;  // Computed at compile time!

// Type traits
template<typename T>
struct RemoveConst {
    using type = T;
};

template<typename T>
struct RemoveConst<const T> {
    using type = T;
};

// Usage:
using IntType = RemoveConst<const int>::type;  // int

// Modern version (C++11+):
template<typename T>
using remove_const_t = typename std::remove_const<T>::type;
```

**Task:** Implement compile-time fibonacci, type trait utilities.

### Side Quest 6: SFINAE (Substitution Failure Is Not An Error)
**XP:** +50

Enable/disable templates based on type properties:

```cpp
#include <type_traits>

// Only for integral types
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
increment(T value) {
    return value + 1;
}

// Only for floating point types
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
increment(T value) {
    return value + 0.1;
}

// Usage:
int i = increment(5);      // Calls integral version
double d = increment(3.14); // Calls floating point version

// Modern version (C++17+):
template<typename T>
std::enable_if_t<std::is_integral_v<T>, T>
increment(T value) {
    return value + 1;
}

// Even better (C++20 concepts):
template<std::integral T>
T increment(T value) {
    return value + 1;
}

// Detect if type has method:
template<typename T, typename = void>
struct has_size : std::false_type {};

template<typename T>
struct has_size<T, std::void_t<decltype(std::declval<T>().size())>> 
    : std::true_type {};

// Usage:
static_assert(has_size<std::vector<int>>::value);  // true
static_assert(!has_size<int>::value);              // true
```

**Task:** Implement SFINAE-based function overloading, create type detection utilities.

---

## 💡 Key Takeaways

1. **Templates** = Generic code that works with any type
2. **Function templates** = Generic functions with type deduction
3. **Class templates** = Generic classes (must specify type)
4. **Specialization** = Custom behavior for specific types
5. **Concepts** = Constrain template parameters (C++20)

---

## 🔍 Common Pitfalls

### ❌ Forgetting template keyword
```cpp
// Error: not a template
class Stack {
    void push(T item);  // What is T?
};
```

### ❌ Template definition in .cpp file
```cpp
// header.h
template<typename T>
class Stack {
    void push(const T& item);
};

// source.cpp
template<typename T>
void Stack<T>::push(const T& item) {  // Linker error!
    // Implementation must be in header
}
```

### ❌ Not specifying type for class template
```cpp
Stack s;  // Error: Stack<what?>
Stack<int> s;  // OK
```

### ❌ Template bloat
```cpp
// Each instantiation creates new code
Stack<int> s1;
Stack<long> s2;
Stack<short> s3;
// Three complete Stack implementations in binary!
```

---

## 📚 Resources

- [C++ Core Guidelines: T.1-T.150](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#t1-use-templates-to-raise-the-level-of-abstraction-of-code)
- [Templates](https://en.cppreference.com/w/cpp/language/templates)
- [Concepts](https://en.cppreference.com/w/cpp/language/constraints)
- [Type Traits](https://en.cppreference.com/w/cpp/header/type_traits)
- [SFINAE](https://en.cppreference.com/w/cpp/language/sfinae)

---

## 📝 Homework Expectations

### In-Session Demo (What we'll build together)
- ✅ Basic function template (max, min)
- ✅ Simple class template (Stack)
- ✅ Template type deduction
- ✅ Basic template specialization

### Your Homework (What you'll implement)
- 📝 Complete generic Stat system
- 📝 Multiple template parameters
- 📝 Template specializations for specific types
- 📝 Type demangling utility (Side Quest 4)
- 📝 Template metaprogramming (Side Quest 5)
- 📝 SFINAE-based overloading (Side Quest 6)
- 📝 C++20 concepts (Side Quest 3)
- 📝 Generic inventory (Side Quest 1)

**Expected time:** 3-4 hours for core quest + 1-2 hours per side quest

**Key insight:** Templates are compile-time code generation. Use type_name() to debug what types are actually instantiated!

---

## 🎯 Achievement Unlocked

Complete this quest to earn:
- **"Template Master"** badge (100 XP)
- **"Generic Wizard"** badge (+20 XP for clean templates)
- Progress toward **Expert** rank

---

## 🔮 What's Next?

In **Session 11: Standard Library**, you'll explore the STL - a treasure trove of template-based containers and algorithms. The power of the standard library awaits! 📚

---

**Write once, use everywhere!** 📜
