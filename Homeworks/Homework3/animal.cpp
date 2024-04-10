//
//  main.cpp
//  Homework3P1V2
//
//  Created by Devansh Mishra on 09/02/24.
//

class Animal {
  public:
    virtual string name() const = 0;
    virtual void speak() const = 0;
    virtual string moveAction() const { return "walk"; };
    virtual ~Animal() {}
};

class Cat : public Animal {
  public:
    Cat(string name) : m_name(name), m_sound("Meow") {}
    virtual ~Cat() {
        cout << "Destroying " << m_name << " the cat" << endl;
    }
    
    virtual string name() const { return m_name; }
    virtual void speak() const { cout << m_sound; }
  private:
    string m_name;
    string m_sound;
};

class Pig : public Animal {
  public:
    Pig(string name, int weight) : m_name(name), m_weight(weight) {}
    virtual ~Pig() { cout << "Destroying " << m_name << " the pig" << endl; }
    virtual string name() const { return m_name; }
    virtual void speak() const {
        if (m_weight < 180) cout << "Oink";
        else cout << "Grunt";
    }
  private:
    string m_name;
    int m_weight;
};

class Duck : public Animal {
  public:
    Duck(string name) : m_name(name) {}
    virtual ~Duck() { cout << "Destroying " << m_name << " the duck" << endl; }
    virtual string name() const { return m_name; }
    virtual void speak() const { cout << "Quack"; }
    virtual string moveAction() const { return "swim"; }
  private:
    string m_name;
};
