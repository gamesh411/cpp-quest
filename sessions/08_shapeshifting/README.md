# Session 8: Shapeshifting

## 🎯 Quest Overview

**Narrative:** *"The ultimate magic: one form, many shapes. Master the art of transformation through virtual dispatch."*

**Learning Objectives:**
- Understand polymorphism and virtual functions
- Implement pure virtual functions (abstract classes)
- Use dynamic dispatch correctly
- Apply the override keyword
- Design polymorphic interfaces
- Understand vtables and runtime behavior

**Estimated Time:** 3 hours

---

## 📖 Background Story

You've learned inheritance - classes sharing a bloodline. But the true power emerges when you treat different types uniformly through a common interface. A Dragon and a Goblin are both Enemies, but they attack differently. **Polymorphism** lets you call `attack()` on any Enemy, and the right version executes automatically.

This is shapeshifting: one interface, many implementations.

---

## 🎓 Concepts Covered

### 1. Virtual Functions

```cpp
class Entity {
public:
    virtual void attack() {
        std::cout << "Entity attacks\n";
    }
};

class Dragon : public Entity {
public:
    void attack() override {  // override keyword
        std::cout << "Dragon breathes fire!\n";
    }
};

class Goblin : public Entity {
public:
    void attack() override {
        std::cout << "Goblin stabs!\n";
    }
};

// Polymorphism in action
Entity* e1 = new Dragon();
Entity* e2 = new Goblin();

e1->attack();  // "Dragon breathes fire!"
e2->attack();  // "Goblin stabs!"
```

**Key:** `virtual` enables dynamic dispatch - the correct function is called based on actual object type, not pointer type.

### 2. Pure Virtual Functions (Abstract Classes)

```cpp
class Entity {
public:
    virtual ~Entity() = default;
    
    // Pure virtual = must be implemented by derived classes
    virtual void attack() = 0;
    virtual void defend() = 0;
};

// Entity e;  // Error: can't instantiate abstract class

class Dragon : public Entity {
public:
    void attack() override { /* implementation */ }
    void defend() override { /* implementation */ }
};

Dragon d;  // OK: Dragon implements all pure virtuals
```

**Abstract class** = class with at least one pure virtual function. Cannot be instantiated.

### 3. Override Keyword

```cpp
class Base {
public:
    virtual void foo() {}
    virtual void bar() const {}
};

class Derived : public Base {
public:
    void foo() override {}  // ✅ OK: overrides Base::foo
    
    // void bar() override {}  // ❌ Error: signature doesn't match
    void bar() const override {}  // ✅ OK: matches signature
    
    // void baz() override {}  // ❌ Error: no virtual baz in Base
};
```

**Always use `override`** - catches mistakes at compile time.

### 4. Virtual Destructors

```cpp
class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor\n";
    }
};

class Derived : public Base {
public:
    ~Derived() override {
        std::cout << "Derived destructor\n";
    }
};

Base* ptr = new Derived();
delete ptr;  // Calls both destructors (Derived, then Base)

// Without virtual destructor:
// Only Base destructor called - memory leak!
```

**Rule:** If a class has virtual functions, it needs a virtual destructor.

### 5. Dynamic Dispatch (vtable)

```cpp
class Entity {
public:
    virtual void attack() { /* ... */ }
};

// Compiler creates vtable (virtual function table)
// Each Entity object has vptr (pointer to vtable)
// At runtime, vptr determines which function to call
```

**Cost:** One pointer per object, one indirection per virtual call.

---

## 🎮 Core Quest: Polymorphic Combat System

### Requirements

Implement a combat system using polymorphism:

#### 1. `Entity` (Abstract Base Class)

```cpp
class Entity {
protected:
    std::string name_;
    int health_;
    int maxHealth_;
    int attackPower_;

public:
    Entity(const std::string& name, int maxHealth, int attackPower);
    virtual ~Entity() = default;
    
    const std::string& getName() const;
    int getHealth() const;
    bool isAlive() const;
    
    void takeDamage(int amount);
    
    // Pure virtual functions
    virtual void attack(Entity* target) = 0;
    virtual void defend() = 0;
    virtual std::string getType() const = 0;
};
```

#### 2. `Warrior` (Derived Class)

```cpp
class Warrior : public Entity {
private:
    int armor_;

public:
    Warrior(const std::string& name, int health, int attackPower, int armor);
    
    void attack(Entity* target) override;
    void defend() override;
    std::string getType() const override;
    
    int getArmor() const;
};
```

#### 3. `Mage` (Derived Class)

```cpp
class Mage : public Entity {
private:
    int mana_;

public:
    Mage(const std::string& name, int health, int attackPower, int mana);
    
    void attack(Entity* target) override;
    void defend() override;
    std::string getType() const override;
    
    int getMana() const;
};
```

#### 4. `CombatSystem`

```cpp
class CombatSystem {
private:
    std::vector<Entity*> combatants_;

public:
    void addCombatant(Entity* entity);
    void executeTurn(int attackerIndex, int targetIndex);
    void displayStatus() const;
    int getCombatantCount() const;
};
```

### Success Criteria

✅ Entity is abstract (pure virtual functions)  
✅ Warrior and Mage implement all pure virtuals  
✅ Override keyword used correctly  
✅ Virtual destructor in base class  
✅ Polymorphic behavior works (different attack implementations)  
✅ All tests pass  
✅ Code compiles with `-Wall -Wextra -Werror`  

---

## 🧪 Testing Your Implementation

```bash
# Build and run tests
cd cpp-quest
cmake -B build
cmake --build build
./build/sessions/08_shapeshifting/test_session08

# Run demo
./build/sessions/08_shapeshifting/combat_demo
```

**Expected Output:**
```
================================
  SHAPESHIFTING (POLYMORPHISM)
================================

Creating combatants...
✓ Created Warrior: Conan
✓ Created Mage: Gandalf

Combat Status:
  Warrior: Conan (HP: 150/150, Armor: 50)
  Mage: Gandalf (HP: 80/80, Mana: 100)

Turn 1: Conan attacks Gandalf
⚔️ Conan slashes with sword for 30 damage!
✓ Gandalf took 30 damage

Turn 2: Gandalf attacks Conan
🔮 Gandalf casts fireball for 40 damage!
✓ Conan took 40 damage

Combat Status:
  Warrior: Conan (HP: 110/150, Armor: 50)
  Mage: Gandalf (HP: 50/80, Mana: 90)
```

---

## 🌟 Side Quests (Optional)

### Side Quest 1: Rogue Class
**XP:** +50

Add a third class with unique mechanics:
```cpp
class Rogue : public Entity {
    int critChance_;
public:
    void attack(Entity* target) override;  // Can crit!
    void defend() override;  // Dodge
};
```

### Side Quest 2: Special Attacks
**XP:** +50

Add polymorphic special attacks:
```cpp
class SpecialAttack {
public:
    virtual ~SpecialAttack() = default;
    virtual void execute(Entity* user, Entity* target) = 0;
    virtual std::string getName() const = 0;
};

class Fireball : public SpecialAttack { /* ... */ };
class PowerStrike : public SpecialAttack { /* ... */ };
```

### Side Quest 3: Combat AI
**XP:** +50

Implement AI decision-making:
```cpp
class Entity {
public:
    virtual int chooseTarget(const std::vector<Entity*>& enemies) = 0;
    // Different classes choose targets differently
};
```

### Side Quest 4: Vtable Visualization & Analysis
**XP:** +50

Understand virtual function implementation:

```cpp
// Visualize vtable structure
class Entity {
public:
    virtual void attack() {}
    virtual void defend() {}
};

class Dragon : public Entity {
public:
    void attack() override {}
    void defend() override {}
};

/*
Memory layout:

Entity object:
┌─────────────┐
│ vptr        │ ──→ Entity vtable:
├─────────────┤     ┌──────────────────┐
│ name_       │     │ Entity::attack() │
│ health_     │     │ Entity::defend() │
└─────────────┘     └──────────────────┘

Dragon object:
┌─────────────┐
│ vptr        │ ──→ Dragon vtable:
├─────────────┤     ┌──────────────────┐
│ name_       │     │ Dragon::attack() │
│ health_     │     │ Dragon::defend() │
│ firepower_  │     └──────────────────┘
└─────────────┘
*/

// Tasks:
// 1. Measure sizeof() with and without virtual functions
// 2. Benchmark virtual vs non-virtual call performance
// 3. Use debugger to inspect vptr
// 4. Document vtable structure for your hierarchy
```

### Side Quest 5: Virtual Destructor Deep Dive
**XP:** +50

Demonstrate importance of virtual destructors:

```cpp
class Base {
public:
    Base() { std::cout << "Base constructed\n"; }
    ~Base() { std::cout << "Base destroyed\n"; }  // NOT virtual!
};

class Derived : public Base {
    int* data_;
public:
    Derived() : data_(new int[100]) {
        std::cout << "Derived constructed\n";
    }
    ~Derived() {
        delete[] data_;
        std::cout << "Derived destroyed\n";
    }
};

// Memory leak demonstration:
Base* ptr = new Derived();
delete ptr;  // Only Base destructor called! data_ leaked!

// Output:
// Base constructed
// Derived constructed
// Base destroyed  ← Derived destructor NOT called!

// Fix: Make Base destructor virtual
class Base {
public:
    virtual ~Base() { std::cout << "Base destroyed\n"; }
};

// Now both destructors called:
// Base constructed
// Derived constructed
// Derived destroyed  ← Now called!
// Base destroyed
```

**Task:** Create examples showing memory leaks without virtual destructor, then fix them.

### Side Quest 6: Pure Virtual & Abstract Interfaces
**XP:** +50

Design abstract interfaces:

```cpp
// Abstract interface (all pure virtual)
class IAttacker {
public:
    virtual ~IAttacker() = default;
    virtual void attack(Entity* target) = 0;
    virtual int getDamage() const = 0;
};

class IDefender {
public:
    virtual ~IDefender() = default;
    virtual void defend() = 0;
    virtual int getArmor() const = 0;
};

// Concrete class implements multiple interfaces
class Warrior : public Entity, public IAttacker, public IDefender {
public:
    void attack(Entity* target) override { /* ... */ }
    int getDamage() const override { return 50; }
    void defend() override { /* ... */ }
    int getArmor() const override { return 30; }
};

// Can use through interface pointers
IAttacker* attacker = new Warrior();
attacker->attack(enemy);
```

**Task:** Design interface hierarchy for your game entities.

---

## 💡 Key Takeaways

1. **Polymorphism** = One interface, many implementations
2. **Virtual functions** = Enable dynamic dispatch
3. **Pure virtual** = Abstract interface, must be implemented
4. **Override** = Explicitly mark overriding functions
5. **Virtual destructor** = Required for polymorphic classes

---

## 🔍 Common Pitfalls

### ❌ Forgetting virtual keyword
```cpp
class Base {
    void foo() {}  // Not virtual!
};

class Derived : public Base {
    void foo() override {}  // Error: nothing to override
};
```

### ❌ Missing override keyword
```cpp
class Derived : public Base {
    void foo() {}  // Compiles but doesn't override (typo risk)
};
```

### ❌ Non-virtual destructor
```cpp
class Base {
    ~Base() {}  // Should be virtual!
};

Base* ptr = new Derived();
delete ptr;  // Only Base destructor called - leak!
```

### ❌ Slicing with pass-by-value
```cpp
void process(Entity e) {}  // Slices!

Warrior w;
process(w);  // Loses Warrior-specific data

// ✅ Use references or pointers
void process(Entity& e) {}
void process(Entity* e) {}
```

---

## 📚 Resources

- [C++ Core Guidelines: C.120-129](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c120-use-class-hierarchies-to-represent-concepts-with-inherent-hierarchical-structure)
- [Virtual Functions](https://en.cppreference.com/w/cpp/language/virtual)
- [Abstract Classes](https://en.cppreference.com/w/cpp/language/abstract_class)
- [Vtable Explanation](https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/)

---

## 📝 Homework Expectations

### In-Session Demo (What we'll build together)
- ✅ Basic virtual function (Entity::attack)
- ✅ Override in derived class (Dragon::attack)
- ✅ Virtual destructor
- ✅ Simple polymorphic usage

### Your Homework (What you'll implement)
- 📝 Complete Entity hierarchy with virtual functions
- 📝 Pure virtual functions (abstract Entity)
- 📝 All classes use `override` keyword
- 📝 Vtable visualization (Side Quest 4)
- 📝 Virtual destructor analysis (Side Quest 5)
- 📝 Abstract interfaces (Side Quest 6)
- 📝 Rogue, special attacks, AI (Side Quests 1-3)

**Expected time:** 3-4 hours for core quest + 1 hour per side quest

**Key insight:** Virtual functions add one pointer (vptr) per object. Measure the cost with sizeof() and benchmarks!

---

## 🎯 Achievement Unlocked

Complete this quest to earn:
- **"Shapeshifter Supreme"** badge (100 XP)
- **"Polymorphic Master"** badge (+20 XP for perfect virtual usage)
- Progress toward **Expert** rank

---

## 🔮 What's Next?

In **Session 9: Ancient Powers**, you'll explore advanced inheritance topics including multiple inheritance, virtual inheritance, and the diamond problem. Prepare for forbidden knowledge! 💎

---

**One interface, infinite forms!** 🦎
