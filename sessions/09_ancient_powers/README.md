# Session 9: Ancient Powers

## 🎯 Quest Overview

**Narrative:** *"Delve into forbidden knowledge: multiple bloodlines, const mysteries, and the diamond of power."*

**Learning Objectives:**
- Understand multiple inheritance
- Solve the diamond problem with virtual inheritance
- Master const overloading
- Use final and override keywords effectively
- Design complex class hierarchies
- Recognize when to use advanced inheritance

**Estimated Time:** 3 hours

---

## 📖 Background Story

You've mastered single inheritance and polymorphism. But the ancient texts speak of more powerful techniques: entities that inherit from multiple bloodlines, const correctness that enables optimization, and the dreaded **diamond problem** that can corrupt your magic.

These are the **Ancient Powers** - advanced inheritance techniques that few dare to master.

---

## 🎓 Concepts Covered

### 1. Multiple Inheritance

```cpp
class Combatant {
public:
    virtual void attack() = 0;
    virtual ~Combatant() = default;
};

class Trader {
public:
    virtual void trade() = 0;
    virtual ~Trader() = default;
};

// Inherits from both!
class Merchant : public Combatant, public Trader {
public:
    void attack() override {
        std::cout << "Merchant defends shop!\n";
    }
    
    void trade() override {
        std::cout << "Merchant sells goods\n";
    }
};

Merchant m;
m.attack();  // Can do both
m.trade();
```

**Use cases:**
- Mixins (adding functionality)
- Interface implementation
- Complex entity behaviors

### 2. The Diamond Problem

```cpp
class Entity {
protected:
    std::string name_;
public:
    Entity(const std::string& name) : name_(name) {}
};

class Combatant : public Entity {
public:
    Combatant(const std::string& name) : Entity(name) {}
};

class Trader : public Entity {
public:
    Trader(const std::string& name) : Entity(name) {}
};

// Diamond! Merchant has TWO Entity subobjects
class Merchant : public Combatant, public Trader {
public:
    Merchant(const std::string& name)
        : Combatant(name), Trader(name) {}
    
    // m.name_ is ambiguous! Which Entity?
};
```

**Problem:** `Merchant` has two copies of `Entity` - ambiguous and wasteful.

### 3. Virtual Inheritance (Solution)

```cpp
class Entity {
protected:
    std::string name_;
public:
    Entity(const std::string& name) : name_(name) {}
};

// Virtual inheritance
class Combatant : public virtual Entity {
public:
    Combatant(const std::string& name) : Entity(name) {}
};

class Trader : public virtual Entity {
public:
    Trader(const std::string& name) : Entity(name) {}
};

// Only ONE Entity subobject!
class Merchant : public Combatant, public Trader {
public:
    Merchant(const std::string& name)
        : Entity(name),  // Most derived class initializes virtual base
          Combatant(name),
          Trader(name) {}
};

Merchant m("Bob");
std::cout << m.name_;  // No ambiguity!
```

**Key:** Virtual inheritance ensures only one copy of the base class.

### 4. Const Overloading

```cpp
class GameWorld {
    std::vector<Entity*> entities_;
    
public:
    // Non-const version - can modify returned entity
    Entity* findEntity(const std::string& name) {
        for (auto* e : entities_) {
            if (e->getName() == name) return e;
        }
        return nullptr;
    }
    
    // Const version - returns const pointer
    const Entity* findEntity(const std::string& name) const {
        for (auto* e : entities_) {
            if (e->getName() == name) return e;
        }
        return nullptr;
    }
};

GameWorld world;
Entity* e = world.findEntity("Hero");  // Non-const

const GameWorld& cworld = world;
const Entity* ce = cworld.findEntity("Hero");  // Const version
```

**Benefit:** Const objects can call const methods, non-const can call either.

### 5. Final and Override

```cpp
class Base {
public:
    virtual void foo() {}
    virtual void bar() final {}  // Cannot be overridden
};

class Derived : public Base {
public:
    void foo() override {}  // OK
    // void bar() override {}  // Error: bar is final
};

class Final final : public Base {  // Cannot be inherited from
    void foo() override {}
};

// class MoreDerived : public Final {};  // Error: Final is final
```

**Use cases:**
- `final` method: prevent further overriding
- `final` class: prevent inheritance
- `override`: catch mistakes

---

## 🎮 Core Quest: Complex NPC System

### Requirements

Implement a flexible NPC system with multiple inheritance:

#### 1. Interface Classes

```cpp
class Combatant {
public:
    virtual ~Combatant() = default;
    virtual void attack() = 0;
    virtual int getAttackPower() const = 0;
};

class Trader {
public:
    virtual ~Trader() = default;
    virtual void trade() = 0;
    virtual int getGold() const = 0;
};

class QuestGiver {
public:
    virtual ~QuestGiver() = default;
    virtual void giveQuest() = 0;
    virtual std::string getQuestName() const = 0;
};
```

#### 2. Base Entity (Virtual Inheritance)

```cpp
class Entity {
protected:
    std::string name_;
    
public:
    Entity(const std::string& name);
    virtual ~Entity() = default;
    
    const std::string& getName() const;
};
```

#### 3. Concrete NPCs

```cpp
class Merchant : public virtual Entity, public Combatant, public Trader {
private:
    int attackPower_;
    int gold_;
    
public:
    Merchant(const std::string& name, int attackPower, int gold);
    
    void attack() override;
    int getAttackPower() const override;
    
    void trade() override;
    int getGold() const override;
};

class QuestMaster : public virtual Entity, public QuestGiver, public Trader {
private:
    std::string questName_;
    int gold_;
    
public:
    QuestMaster(const std::string& name, const std::string& quest, int gold);
    
    void giveQuest() override;
    std::string getQuestName() const override;
    
    void trade() override;
    int getGold() const override;
};
```

#### 4. NPC Manager with Const Overloading

```cpp
class NPCManager {
private:
    std::vector<Entity*> npcs_;
    
public:
    void addNPC(Entity* npc);
    
    Entity* findNPC(const std::string& name);
    const Entity* findNPC(const std::string& name) const;
    
    int getNPCCount() const;
};
```

### Success Criteria

✅ Multiple inheritance implemented correctly  
✅ Virtual inheritance used to avoid diamond problem  
✅ Const overloading for findNPC  
✅ All interfaces implemented  
✅ Override keyword used  
✅ All tests pass  
✅ Code compiles with `-Wall -Wextra -Werror`  

---

## 🧪 Testing Your Implementation

```bash
# Build and run tests
cd cpp-quest
cmake -B build
cmake --build build
./build/sessions/09_ancient_powers/test_session09

# Run demo
./build/sessions/09_ancient_powers/npc_demo
```

**Expected Output:**
```
================================
  ANCIENT POWERS
================================

Creating NPCs...
✓ Created Merchant: Bob
✓ Created QuestMaster: Sage

Testing multiple inheritance...
Bob can attack: Power 20
Bob can trade: Gold 100

Sage can give quests: Find the Artifact
Sage can trade: Gold 50

Testing polymorphism...
Combatant: Bob attacks!
Trader: Bob trades!

QuestGiver: Sage gives quest!
Trader: Sage trades!

Testing const overloading...
✓ Found NPC (non-const): Bob
✓ Found NPC (const): Sage
```

---

## 🌟 Side Quests (Optional)

### Side Quest 1: Guard NPC
**XP:** +50

Create Guard with 3 interfaces:
```cpp
class Guard : public virtual Entity, 
              public Combatant, 
              public QuestGiver, 
              public Trader {
    // Implements all three!
};
```

### Side Quest 2: Ability System
**XP:** +50

Create ability mixins:
```cpp
class Flyable {
public:
    virtual void fly() = 0;
};

class Stealthy {
public:
    virtual void hide() = 0;
};

class Assassin : public Combatant, public Flyable, public Stealthy {
    // Multiple abilities
};
```

### Side Quest 3: Final Classes
**XP:** +50

Use `final` to prevent inheritance:
```cpp
class Boss final : public Combatant {
    // Cannot be inherited from
};
```

### Side Quest 4: Virtual Inheritance Memory Layout
**XP:** +50

Visualize and analyze virtual inheritance:

```cpp
// Without virtual inheritance (Diamond Problem):
class Entity { int health_; };
class Combatant : public Entity {};
class Trader : public Entity {};
class Merchant : public Combatant, public Trader {};

/*
Merchant memory layout (WITHOUT virtual inheritance):
┌──────────────────┐
│ Combatant part:  │
│   Entity (copy1) │ ← First Entity
│   combat data    │
├──────────────────┤
│ Trader part:     │
│   Entity (copy2) │ ← Second Entity (duplicate!)
│   trade data     │
└──────────────────┘
sizeof(Merchant) = 2 * sizeof(Entity) + extras
*/

// With virtual inheritance:
class Entity { int health_; };
class Combatant : public virtual Entity {};
class Trader : public virtual Entity {};
class Merchant : public Combatant, public Trader {};

/*
Merchant memory layout (WITH virtual inheritance):
┌──────────────────┐
│ vptr (Combatant) │ ← Virtual base pointer
│ combat data      │
├──────────────────┤
│ vptr (Trader)    │ ← Virtual base pointer
│ trade data       │
├──────────────────┤
│ Entity (shared)  │ ← Single Entity instance
│   health_        │
└──────────────────┘
sizeof(Merchant) = 1 * sizeof(Entity) + 2 * vptr + extras
*/

// Tasks:
// 1. Measure sizeof() with and without virtual inheritance
// 2. Draw memory layout diagrams for your hierarchy
// 3. Benchmark access time (virtual base has indirection cost)
// 4. Document initialization order
```

### Side Quest 5: Ambiguity Resolution
**XP:** +50

Handle name ambiguity in multiple inheritance:

```cpp
class Combatant {
public:
    void update() { std::cout << "Combat update\n"; }
    int getPriority() const { return 10; }
};

class Trader {
public:
    void update() { std::cout << "Trade update\n"; }
    int getPriority() const { return 5; }
};

class Merchant : public Combatant, public Trader {
public:
    // Ambiguous! Which update()?
    // m.update();  // Error!
    
    // Solution 1: Explicit qualification
    void updateCombat() { Combatant::update(); }
    void updateTrade() { Trader::update(); }
    
    // Solution 2: Override and choose
    void update() override {
        Combatant::update();
        Trader::update();
    }
    
    // Solution 3: Using declaration
    using Combatant::getPriority;  // Choose one
};
```

**Task:** Create examples of all ambiguity types and resolution strategies.

### Side Quest 6: Mixin Pattern
**XP:** +50

Implement reusable mixin classes:

```cpp
// Mixin: adds functionality without data
template<typename Base>
class Serializable : public Base {
public:
    std::string serialize() const {
        return "Serialized: " + Base::getName();
    }
    
    void deserialize(const std::string& data) {
        // Restore from data
    }
};

template<typename Base>
class Loggable : public Base {
public:
    void log(const std::string& msg) const {
        std::cout << "[" << Base::getName() << "] " << msg << "\n";
    }
};

// Combine mixins:
class Entity { /* ... */ };
using LoggableEntity = Loggable<Entity>;
using SerializableLoggableEntity = Serializable<Loggable<Entity>>;

SerializableLoggableEntity e;
e.log("Created");
std::string data = e.serialize();
```

**Task:** Create mixin library for common functionality (logging, serialization, debugging).

---

## 💡 Key Takeaways

1. **Multiple inheritance** = Inherit from multiple base classes
2. **Diamond problem** = Duplicate base class subobjects
3. **Virtual inheritance** = Share single base class instance
4. **Const overloading** = Different behavior for const/non-const
5. **Final** = Prevent overriding or inheritance

---

## 🔍 Common Pitfalls

### ❌ Forgetting virtual inheritance
```cpp
class Merchant : public Combatant, public Trader {
    // Diamond problem if both inherit from Entity!
};
```

### ❌ Not initializing virtual base in most derived
```cpp
class Merchant : public Combatant, public Trader {
    Merchant() : Combatant(), Trader() {}  // Missing Entity()!
};
```

### ❌ Const overload without const method
```cpp
Entity* find(const std::string& name);
// Missing: const Entity* find(const std::string& name) const;
```

### ❌ Overusing multiple inheritance
```cpp
// Bad: inheritance for code reuse
class Player : public Logger, public Serializer, public Renderer {
    // Use composition instead!
};
```

---

## 📚 Resources

- [C++ Core Guidelines: C.135-136](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c135-use-multiple-inheritance-to-represent-multiple-distinct-interfaces)
- [Multiple Inheritance](https://en.cppreference.com/w/cpp/language/derived_class#Multiple_inheritance)
- [Virtual Inheritance](https://en.cppreference.com/w/cpp/language/derived_class#Virtual_base_classes)
- [Diamond Problem Explained](https://isocpp.org/wiki/faq/multiple-inheritance)

---

## 📝 Homework Expectations

### In-Session Demo (What we'll build together)
- ✅ Basic multiple inheritance (two interfaces)
- ✅ Diamond problem demonstration
- ✅ Virtual inheritance solution
- ✅ Simple const overloading

### Your Homework (What you'll implement)
- 📝 Complete Merchant with multiple inheritance
- 📝 Virtual inheritance for Entity base
- 📝 Const overloading for all accessors
- 📝 Memory layout analysis (Side Quest 4)
- 📝 Ambiguity resolution examples (Side Quest 5)
- 📝 Mixin pattern implementation (Side Quest 6)
- 📝 Guard, abilities, final classes (Side Quests 1-3)

**Expected time:** 3-4 hours for core quest + 1 hour per side quest

**Key insight:** Virtual inheritance solves diamond problem but adds vptr overhead. Most derived class must initialize virtual base!

---

## 🎯 Achievement Unlocked

Complete this quest to earn:
- **"Ancient Wisdom"** badge (100 XP)
- **"Diamond Solver"** badge (+20 XP for virtual inheritance)
- Progress toward **Expert** rank

---

## 🔮 What's Next?

In **Session 10: Template Codex**, you'll discover the ultimate abstraction - templates that work with any type. Generic programming awaits! 📜

---

**Wield the ancient powers wisely!** 💎
