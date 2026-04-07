# Session 7: Bloodlines

## 🎯 Quest Overview

**Narrative:** *"Power flows through bloodlines. Learn to inherit abilities from your ancestors and build upon their legacy."*

**Learning Objectives:**
- Understand single inheritance
- Use access specifiers (public, protected, private)
- Implement constructor chaining
- Override base class methods
- Recognize and avoid object slicing
- Apply is-a relationships

**Estimated Time:** 3 hours

---

## 📖 Background Story

You've crafted individual classes, but now you notice patterns: Characters and Enemies share common traits (health, name, damage). Rather than duplicate code, you'll learn **inheritance** - the ability to create new classes based on existing ones.

Think of it as bloodlines: a Dragon inherits traits from Enemy, which inherits from Entity. Each generation adds new abilities while keeping ancestral powers.

---

## 🎓 Concepts Covered

### 1. Basic Inheritance

```cpp
class Entity {
protected:
    std::string name_;
    int health_;
    
public:
    Entity(const std::string& name, int health)
        : name_(name), health_(health) {}
    
    void takeDamage(int amount) {
        health_ -= amount;
    }
    
    bool isAlive() const {
        return health_ > 0;
    }
};

class Character : public Entity {
private:
    int mana_;
    
public:
    Character(const std::string& name, int health, int mana)
        : Entity(name, health), mana_(mana) {}  // Constructor chaining
    
    void castSpell(int cost) {
        if (mana_ >= cost) {
            mana_ -= cost;
        }
    }
};
```

**Key Points:**
- `Character` **is-a** `Entity`
- Inherits all members from `Entity`
- Adds new members (`mana_`)

### 2. Access Specifiers

```cpp
class Base {
private:
    int private_;      // Only Base can access
    
protected:
    int protected_;    // Base and derived classes can access
    
public:
    int public_;       // Everyone can access
};

class Derived : public Base {
    void foo() {
        // private_ = 1;    // Error: can't access private
        protected_ = 2;     // OK: can access protected
        public_ = 3;        // OK: can access public
    }
};
```

**Inheritance Access:**
```cpp
class Derived : public Base {};     // Most common
class Derived : protected Base {};  // Rare
class Derived : private Base {};    // Rare
```

### 3. Constructor Chaining

```cpp
class Entity {
protected:
    std::string name_;
    int health_;
    
public:
    Entity(const std::string& name, int health)
        : name_(name), health_(health) {
        std::cout << "Entity constructor\n";
    }
};

class Character : public Entity {
private:
    int mana_;
    
public:
    Character(const std::string& name, int health, int mana)
        : Entity(name, health),  // Call base constructor first
          mana_(mana) {
        std::cout << "Character constructor\n";
    }
};

// Output when creating Character:
// Entity constructor
// Character constructor
```

**Order:**
1. Base class constructor
2. Derived class members initialized
3. Derived class constructor body

### 4. Method Overriding

```cpp
class Entity {
public:
    void update() {
        std::cout << "Entity update\n";
    }
};

class Character : public Entity {
public:
    void update() {  // Overrides Entity::update
        std::cout << "Character update\n";
        Entity::update();  // Can call base version
    }
};

Character c;
c.update();  // Calls Character::update
```

### 5. Object Slicing

```cpp
class Entity {
    int health_;
public:
    Entity(int h) : health_(h) {}
};

class Character : public Entity {
    int mana_;
public:
    Character(int h, int m) : Entity(h), mana_(m) {}
};

void processEntity(Entity e) {  // Pass by value!
    // e is sliced - mana_ is lost
}

Character c(100, 50);
processEntity(c);  // Slicing occurs!

// ✅ Solution: Use references or pointers
void processEntity(Entity& e) {}  // No slicing
void processEntity(Entity* e) {}  // No slicing
```

---

## 🎮 Core Quest: Entity Hierarchy

### Requirements

Create a game entity hierarchy with three classes:

#### 1. `Entity` (Base Class)

**Protected Members:**
- `std::string name_`
- `int health_`
- `int maxHealth_`

**Public Interface:**
```cpp
Entity(const std::string& name, int maxHealth);
virtual ~Entity() = default;

const std::string& getName() const;
int getHealth() const;
int getMaxHealth() const;

void takeDamage(int amount);
void heal(int amount);
bool isAlive() const;
virtual void display() const;
```

#### 2. `Character` (Derived from Entity)

**Private Members:**
- `int mana_`
- `int maxMana_`

**Public Interface:**
```cpp
Character(const std::string& name, int maxHealth, int maxMana);

int getMana() const;
int getMaxMana() const;

void useMana(int amount);
void restoreMana(int amount);
void display() const override;
```

#### 3. `Enemy` (Derived from Entity)

**Private Members:**
- `int experienceValue_`
- `int goldDrop_`

**Public Interface:**
```cpp
Enemy(const std::string& name, int maxHealth, int xp, int gold);

int getExperienceValue() const;
int getGoldDrop() const;

void display() const override;
```

### Success Criteria

✅ Proper inheritance hierarchy (Entity → Character/Enemy)  
✅ Constructor chaining implemented  
✅ Protected members accessible in derived classes  
✅ Method overriding works correctly  
✅ Virtual destructor in base class  
✅ All tests pass  
✅ Code compiles with `-Wall -Wextra -Werror`  

---

## 🧪 Testing Your Implementation

```bash
# Build and run tests
cd cpp-quest
cmake -B build
cmake --build build
./build/sessions/07_bloodlines/test_session07

# Run demo
./build/sessions/07_bloodlines/entity_demo
```

**Expected Output:**
```
================================
  BLOODLINES (INHERITANCE)
================================

Creating entities...
✓ Created Entity: Rock
✓ Created Character: Hero
✓ Created Enemy: Goblin

Entity details:
Entity: Rock
  Health: 100/100

Character: Hero
  Health: 100/100
  Mana: 50/50

Enemy: Goblin
  Health: 50/50
  XP: 25, Gold: 10

Testing damage...
✓ Rock took 30 damage
✓ Hero took 20 damage
✓ Goblin took 40 damage

After damage:
Entity: Rock
  Health: 70/100

Character: Hero
  Health: 80/100
  Mana: 50/50

Enemy: Goblin
  Health: 10/50
  XP: 25, Gold: 10
```

---

## 🌟 Side Quests (Optional)

### Side Quest 1: Enemy Types
**XP:** +50

Create 3 specialized enemy types:
```cpp
class Goblin : public Enemy {
    int agility_;
public:
    void quickAttack();
};

class Dragon : public Enemy {
    int firepower_;
public:
    void breatheFire();
};

class Undead : public Enemy {
    bool canReanimate_;
public:
    void reanimate();
};
```

### Side Quest 2: Status Effects
**XP:** +50

Add status effect system:
```cpp
class Entity {
protected:
    std::vector<std::string> statusEffects_;
public:
    void addStatus(const std::string& effect);
    void removeStatus(const std::string& effect);
    bool hasStatus(const std::string& effect) const;
};
```

### Side Quest 3: NPC Class
**XP:** +50

Create NPC (Non-Player Character):
```cpp
class NPC : public Entity {
    std::vector<std::string> dialogue_;
public:
    void speak() const;
    void addDialogue(const std::string& line);
};
```

### Side Quest 4: Constructor/Destructor Chaining Visualization
**XP:** +50

Trace constructor and destructor call order:
```cpp
class Entity {
public:
    Entity(const std::string& name) {
        std::cout << "Entity(" << name << ") constructed\n";
    }
    ~Entity() {
        std::cout << "Entity destroyed\n";
    }
};

class Character : public Entity {
public:
    Character(const std::string& name) : Entity(name) {
        std::cout << "Character constructed\n";
    }
    ~Character() {
        std::cout << "Character destroyed\n";
    }
};

class Warrior : public Character {
public:
    Warrior(const std::string& name) : Character(name) {
        std::cout << "Warrior constructed\n";
    }
    ~Warrior() {
        std::cout << "Warrior destroyed\n";
    }
};

// Create Warrior and observe output:
// Entity(Aldric) constructed
// Character constructed
// Warrior constructed
// Warrior destroyed
// Character destroyed
// Entity destroyed
```

**Task:** Create multi-level hierarchy and document call order.

### Side Quest 5: Access Control Variations
**XP:** +50

Explore all inheritance access specifiers:
```cpp
class Base {
public:
    int pub;
protected:
    int prot;
private:
    int priv;
};

// Public inheritance (most common)
class PublicDerived : public Base {
    // pub remains public
    // prot remains protected
    // priv inaccessible
};

// Protected inheritance (rare)
class ProtectedDerived : protected Base {
    // pub becomes protected
    // prot remains protected
    // priv inaccessible
};

// Private inheritance (rare)
class PrivateDerived : private Base {
    // pub becomes private
    // prot becomes private
    // priv inaccessible
};
```

**Task:** Implement all three, document use cases for each.

### Side Quest 6: Is-a vs Has-a Analysis
**XP:** +50

Compare inheritance vs composition:
```cpp
// Is-a relationship (inheritance)
class Warrior : public Character {
    // Warrior IS-A Character
};

// Has-a relationship (composition)
class Character {
    Inventory inventory_;  // Character HAS-AN Inventory
    Weapon weapon_;        // Character HAS-A Weapon
};

// When to use which?
// Inheritance: "is-a" relationship, shared interface
// Composition: "has-a" relationship, delegation
```

**Task:** Refactor a design from inheritance to composition and vice versa. Document when each is appropriate.

---

## 💡 Key Takeaways

1. **Inheritance** = Code reuse through is-a relationships
2. **Protected** = Accessible to derived classes
3. **Constructor chaining** = Base constructed before derived
4. **Virtual destructor** = Required for polymorphism (next session!)
5. **Object slicing** = Avoid by using references/pointers

---

## 🔍 Common Pitfalls

### ❌ Forgetting to call base constructor
```cpp
Character(const std::string& name, int health, int mana)
    : mana_(mana) {  // Error: Entity not initialized!
}
```

### ❌ Using private instead of protected
```cpp
class Entity {
private:
    int health_;  // Derived classes can't access!
};
```

### ❌ Object slicing with pass-by-value
```cpp
void process(Entity e) {}  // Slices derived classes!
Character c;
process(c);  // Loses Character-specific data
```

### ❌ Missing virtual destructor
```cpp
class Entity {
    ~Entity() {}  // Should be virtual!
};
```

---

## 📚 Resources

- [C++ Core Guidelines: C.120-129](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c120-use-class-hierarchies-to-represent-concepts-with-inherent-hierarchical-structure) (Inheritance)
- [Inheritance](https://en.cppreference.com/w/cpp/language/derived_class)
- [Object Slicing](https://en.cppreference.com/w/cpp/language/object#Object_slicing)
- [Access Specifiers](https://en.cppreference.com/w/cpp/language/access)

---

## 📝 Homework Expectations

### In-Session Demo (What we'll build together)
- ✅ Basic Entity base class
- ✅ Character derived class with public inheritance
- ✅ Constructor chaining example
- ✅ Protected member access

### Your Homework (What you'll implement)
- 📝 Complete Entity/Character/Enemy hierarchy
- 📝 All three enemy types (Side Quest 1)
- 📝 Constructor/destructor tracing (Side Quest 4)
- 📝 Access control variations (Side Quest 5)
- 📝 Is-a vs has-a analysis (Side Quest 6)
- 📝 Status effects and NPC (Side Quests 2-3)

**Expected time:** 3-4 hours for core quest + 1 hour per side quest

**Key insight:** Constructor order is base→derived, destructor order is derived→base (reverse!).

---

## 🎯 Achievement Unlocked

Complete this quest to earn:
- **"Bloodline Master"** badge (100 XP)
- **"Hierarchy Architect"** badge (+20 XP for clean design)
- Progress toward **Adept** rank

---

## 🔮 What's Next?

In **Session 8: Shapeshifting**, you'll learn polymorphism - the ability to treat derived classes through base class interfaces using virtual functions. One interface, many implementations! 🦎

---

**Inherit wisely, extend powerfully!** 🧬
