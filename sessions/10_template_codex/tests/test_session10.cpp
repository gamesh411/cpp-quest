#include "../starter/templates.h"

#include <string>

#include <catch2/catch_all.hpp>

/*
 * Session 10 Test Coverage
 *
 * Core Requirements Tested:
 * ✅ Container template (add, remove, find, size)
 * ✅ Container with different types (int, string, double)
 * ✅ Stat template (modify, set, get, reset)
 * ✅ Stat with different types (int, float, double)
 * ✅ Function templates (clamp, swap)
 * ✅ Type deduction
 * ✅ Edge cases (full container, empty container)
 * ✅ Template instantiation with multiple types
 *
 * Coverage: 14 test cases, 60+ assertions
 */

TEST_CASE("Container with int", "[session10][container]") {
    Container<int> container(5);

    REQUIRE(container.size() == 0);
    REQUIRE(container.capacity() == 5);
    REQUIRE_FALSE(container.isFull());
}

TEST_CASE("Container add items", "[session10][container]") {
    Container<int> container(3);

    SECTION("Add single item") {
        REQUIRE(container.add(10));
        REQUIRE(container.size() == 1);
    }

    SECTION("Add multiple items") {
        REQUIRE(container.add(10));
        REQUIRE(container.add(20));
        REQUIRE(container.add(30));
        REQUIRE(container.size() == 3);
        REQUIRE(container.isFull());
    }

    SECTION("Cannot add when full") {
        container.add(10);
        container.add(20);
        container.add(30);
        REQUIRE_FALSE(container.add(40));
        REQUIRE(container.size() == 3);
    }
}

TEST_CASE("Container remove items", "[session10][container]") {
    Container<int> container(5);
    container.add(10);
    container.add(20);
    container.add(30);

    SECTION("Remove existing item") {
        REQUIRE(container.remove(20));
        REQUIRE(container.size() == 2);
    }

    SECTION("Remove non-existent item") {
        REQUIRE_FALSE(container.remove(99));
        REQUIRE(container.size() == 3);
    }
}

TEST_CASE("Container find items", "[session10][container]") {
    Container<int> container(5);
    container.add(10);
    container.add(20);

    SECTION("Find existing item") {
        const int* found = container.find(10);
        REQUIRE(found != nullptr);
        REQUIRE(*found == 10);
    }

    SECTION("Find non-existent item") {
        const int* found = container.find(99);
        REQUIRE(found == nullptr);
    }
}

TEST_CASE("Container clear", "[session10][container]") {
    Container<int> container(5);
    container.add(10);
    container.add(20);
    container.add(30);

    container.clear();
    REQUIRE(container.size() == 0);
    REQUIRE_FALSE(container.isFull());
}

TEST_CASE("Container with string", "[session10][container][types]") {
    Container<std::string> container(3);

    REQUIRE(container.add("hello"));
    REQUIRE(container.add("world"));
    REQUIRE(container.size() == 2);

    const std::string* found = container.find("hello");
    REQUIRE(found != nullptr);
    REQUIRE(*found == "hello");

    REQUIRE(container.remove("hello"));
    REQUIRE(container.size() == 1);
}

TEST_CASE("Container with double", "[session10][container][types]") {
    Container<double> container(3);

    REQUIRE(container.add(3.14));
    REQUIRE(container.add(2.71));
    REQUIRE(container.size() == 2);

    const double* found = container.find(3.14);
    REQUIRE(found != nullptr);
    REQUIRE(*found == 3.14);
}

TEST_CASE("Stat with int", "[session10][stat]") {
    Stat<int> health(100, 0, 150);

    REQUIRE(health.get() == 100);
    REQUIRE(health.getBase() == 100);
}

TEST_CASE("Stat modify", "[session10][stat]") {
    Stat<int> health(100, 0, 150);

    SECTION("Increase value") {
        health.modify(20);
        REQUIRE(health.get() == 120);
    }

    SECTION("Decrease value") {
        health.modify(-30);
        REQUIRE(health.get() == 70);
    }

    SECTION("Clamp to max") {
        health.modify(100);
        REQUIRE(health.get() == 150);
    }

    SECTION("Clamp to min") {
        health.modify(-200);
        REQUIRE(health.get() == 0);
    }
}

TEST_CASE("Stat set", "[session10][stat]") {
    Stat<int> health(100, 0, 150);

    SECTION("Set valid value") {
        health.set(80);
        REQUIRE(health.get() == 80);
    }

    SECTION("Set above max") {
        health.set(200);
        REQUIRE(health.get() == 150);
    }

    SECTION("Set below min") {
        health.set(-50);
        REQUIRE(health.get() == 0);
    }
}

TEST_CASE("Stat reset", "[session10][stat]") {
    Stat<int> health(100, 0, 150);

    health.modify(30);
    REQUIRE(health.get() == 130);

    health.reset();
    REQUIRE(health.get() == 100);
}

TEST_CASE("Stat with float", "[session10][stat][types]") {
    Stat<float> mana(50.0f, 0.0f, 100.0f);

    REQUIRE(mana.get() == 50.0f);

    mana.modify(25.5f);
    REQUIRE(mana.get() == 75.5f);

    mana.set(90.0f);
    REQUIRE(mana.get() == 90.0f);
}

TEST_CASE("Stat with double", "[session10][stat][types]") {
    Stat<double> stamina(100.0, 0.0, 200.0);

    stamina.modify(-50.5);
    REQUIRE(stamina.get() == 49.5);
}

TEST_CASE("Function template clamp", "[session10][function]") {
    SECTION("Clamp int") {
        REQUIRE(clamp(5, 0, 10) == 5);
        REQUIRE(clamp(-5, 0, 10) == 0);
        REQUIRE(clamp(15, 0, 10) == 10);
    }

    SECTION("Clamp double") {
        REQUIRE(clamp(5.5, 0.0, 10.0) == 5.5);
        REQUIRE(clamp(-1.0, 0.0, 10.0) == 0.0);
        REQUIRE(clamp(11.0, 0.0, 10.0) == 10.0);
    }
}

TEST_CASE("Function template swap", "[session10][function]") {
    SECTION("Swap int") {
        int a = 5, b = 10;
        swap(a, b);
        REQUIRE(a == 10);
        REQUIRE(b == 5);
    }

    SECTION("Swap string") {
        std::string a = "hello", b = "world";
        swap(a, b);
        REQUIRE(a == "world");
        REQUIRE(b == "hello");
    }

    SECTION("Swap double") {
        double a = 3.14, b = 2.71;
        swap(a, b);
        REQUIRE(a == 2.71);
        REQUIRE(b == 3.14);
    }
}

TEST_CASE("Multiple template instantiations", "[session10][integration]") {
    Container<int> intContainer(5);
    Container<std::string> stringContainer(3);
    Container<double> doubleContainer(4);

    intContainer.add(10);
    stringContainer.add("test");
    doubleContainer.add(3.14);

    REQUIRE(intContainer.size() == 1);
    REQUIRE(stringContainer.size() == 1);
    REQUIRE(doubleContainer.size() == 1);
}

TEST_CASE("Complex template usage", "[session10][integration]") {
    Stat<int> health(100, 0, 150);
    Stat<int> mana(50, 0, 100);

    health.modify(-30);
    mana.modify(20);

    REQUIRE(health.get() == 70);
    REQUIRE(mana.get() == 70);

    health.reset();
    mana.reset();

    REQUIRE(health.get() == 100);
    REQUIRE(mana.get() == 50);
}
