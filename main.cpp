#include "BinarySearchTree.hpp"
#include <cassert>
#include <vector>

/**
 * @brief Funtore di confronto per il tipo int
 */
struct compare_int {
    /**
     * @brief Confronta due interi.
     *
     * @param a Primo intero da confrontare.
     * @param b Secondo intero da confrontare.
     * @return true se il primo intero è minore del secondo, false altrimenti.
     */
    bool operator()(int a, int b) const {
        return a < b;
    }
};

/**
 * @brief Funtore per determinare l'uguaglianza tra due interi.
 */
struct equal_int {
    /**
     * @brief Determina se due interi sono uguali.
     *
     * @param a Primo intero da confrontare.
     * @param b Secondo intero da confrontare.
     * @return true se i due interi sono uguali, false altrimenti.
     */
    bool operator()(int a, int b) const {
        return a == b;
    }
};

/**
 * @brief Classe rappresentante una persona con ID e nome.
 *
 * Tipo custom usato per i test del BinarySearchTree
 */
class Person {
public:
    int id;           ///< ID della persona.
    std::string name; ///< Nome della persona.

    /**
     * @brief Costruttore della classe Person.
     *
     * @param id ID della persona.
     * @param name Nome della persona.
     */
    Person(int id, const std::string &name) : id(id), name(name) {}

    /**
     * @brief Operatore di output per stampare una persona.
     *
     * @param os Stream di output.
     * @param p Persona da stampare.
     * @return Stream di output modificato con la persona stampata.
     */
    friend std::ostream &operator<<(std::ostream &os, const Person &p) {
        os << p.name << " (" << p.id << ")";
        return os;
    }
};

/**
 * @brief Funtore per confrontare due oggetti di tipo Person.
 */
struct compare_person {
    /**
     * @brief Confronta due oggetti di tipo Person in base all'ID.
     *
     * @param a Primo oggetto di tipo Person da confrontare.
     * @param b Secondo oggetto di tipo Person da confrontare.
     * @return true se l'ID del primo oggetto è minore dell'ID del secondo, false altrimenti.
     */
    bool operator()(const Person &a, const Person &b) const {
        return a.id < b.id;
    }
};

/**
 * @brief Funtore per determinare l'uguaglianza tra due oggetti di tipo Person.
 */
struct equal_person {
    /**
     * @brief Determina se due oggetti di tipo Person sono uguali in base all'ID.
     *
     * @param a Primo oggetto di tipo Person da confrontare.
     * @param b Secondo oggetto di tipo Person da confrontare.
     * @return true se l'ID del primo oggetto è uguale all'ID del secondo, false altrimenti.
     */
    bool operator()(const Person &a, const Person &b) const {
        return a.id == b.id;
    }
};

/**
 * @brief Functore per determinare se un intero è pari.
 */
struct is_even {
    /**
     * @brief Verifica se un intero è pari.
     *
     * @param a L'intero da verificare.
     * @return true se l'intero è pari, false altrimenti.
     */
    bool operator()(int a) const {
        return (a % 2 == 0);
    }
};

/**
 * @brief Funtore per determinare se il nome di una persona inizia con 'A'.
 */
struct starts_with_a {
    /**
     * @brief Verifica se il nome di una persona inizia con 'A'.
     *
     * @param p Persona da verificare.
     * @return true se il nome della persona inizia con 'A', false altrimenti.
     */
    bool operator()(const Person &p) const {
        return p.name[0] == 'A';
    }
};

void testDuplicateInsertAsRoot() {
    BinarySearchTree<int, compare_int, equal_int> bst;
    bst.insert(10);
    bst.insert(10);
    int size = bst.size();

    assert(size == 1);
    std::cout << bst << std::endl;
    std::cout << "Test testDuplicateInsertAsRoot(): passed" << std::endl
              << std::endl;
    ;
}

void testDuplicateInsertInsideTree() {
    BinarySearchTree<int, compare_int, equal_int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(5);
    int size = bst.size();

    assert(size == 3);
    std::cout << bst << std::endl;
    std::cout << "Test testDuplicateInsertInsideTree(): passed" << std::endl
              << std::endl;
    ;
}

void testDuplicateInsertAsLeaf() {
    BinarySearchTree<int, compare_int, equal_int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(7);
    bst.insert(7);
    int size = bst.size();

    assert(size == 4);
    std::cout << bst << std::endl;
    std::cout << "Test testDuplicateInsertAsLeaf(): passed" << std::endl
              << std::endl;
    ;
}

void testDuplicateInsertAsRootPerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst;
    Person p1(1, "Alice");
    bst.insert(p1);
    bst.insert(p1);
    int size = bst.size();

    assert(size == 1);
    std::cout << bst << std::endl;
    std::cout << "Test testDuplicateInsertAsRootPerson(): passed" << std::endl
              << std::endl;
    ;
}

void testDuplicateInsertInsideTreePerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst;
    Person p1(1, "Alice");
    Person p2(2, "Bob");
    Person p3(3, "Charlie");
    bst.insert(p1);
    bst.insert(p2);
    bst.insert(p3);
    bst.insert(p2); // Duplicate insert
    int size = bst.size();

    assert(size == 3);
    std::cout << bst << std::endl;
    std::cout << "Test testDuplicateInsertInsideTreePerson(): passed" << std::endl
              << std::endl;
    ;
}

void testDuplicateInsertAsLeafPerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst;
    Person p1(1, "Alice");
    Person p2(2, "Bob");
    Person p3(3, "Charlie");
    Person p4(4, "Diana");
    bst.insert(p1);
    bst.insert(p2);
    bst.insert(p3);
    bst.insert(p4);
    bst.insert(p4); // Duplicate insert
    int size = bst.size();

    assert(size == 4);
    std::cout << bst << std::endl;
    std::cout << "Test testDuplicateInsertAsLeafPerson(): passed" << std::endl
              << std::endl;
    ;
}

void testDuplicatePersonIdInsert() {
    BinarySearchTree<Person, compare_person, equal_person> bst;

    Person p1(1, "Alice");
    Person p2(1, "Bob");
    bst.insert(p1);
    bst.insert(p2);
    int size = bst.size();
    assert(size == 1);
    bool containsP1 = bst.contains(p1);
    assert(containsP1);

    std::cout << bst << std::endl;
    std::cout << "Test testDuplicatePersonIdInsert(): passed" << std::endl
              << std::endl;
}

void testContainsPerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst;
    bst.insert(Person(1, "Alice"));
    bst.insert(Person(2, "Bob"));
    bst.insert(Person(3, "Charlie"));
    bst.insert(Person(4, "David"));

    assert(bst.contains(Person(1, "Alice")) == true);
    assert(bst.contains(Person(2, "Bob")) == true);
    assert(bst.contains(Person(3, "Charlie")) == true);
    assert(bst.contains(Person(4, "David")) == true);

    assert(bst.contains(Person(5, "Emma")) == false);

    std::cout << "Test testContainsMethod(): passed" << std::endl
              << std::endl;
}

void testSizePerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst;

    bst.insert(Person(1, "Alice"));
    bst.insert(Person(2, "Bob"));
    bst.insert(Person(3, "Charlie"));
    bst.insert(Person(4, "David"));

    assert(bst.size() == 4);

    bst.insert(Person(1, "Alice"));

    assert(bst.size() == 4);

    bst.remove(Person(2, "Bob"));

    assert(bst.size() == 3);

    std::cout << bst << std::endl;
    std::cout << "Size: " << bst.size() << std::endl;
    std::cout << "Test testSizeMethod(): passed" << std::endl
              << std::endl;
}

void testRemoveRootPerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst;
    Person p1(1, "Alice");
    Person p2(2, "Bob");
    Person p3(3, "Charlie");

    bst.insert(p1);
    bst.insert(p2);
    bst.insert(p3);

    // Remove the root node (Alice)
    bst.remove(p1);
    int size = bst.size();
    bool contains_p1 = bst.contains(p1);

    assert(size == 2);
    assert(!contains_p1);

    std::cout << bst << std::endl;
    std::cout << "Test testRemoveRootPerson(): passed" << std::endl
              << std::endl;
    ;
}

void testRemoveInsideTreePerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst;
    Person p1(1, "Alice");
    Person p2(2, "Bob");
    Person p3(3, "Charlie");
    Person p4(4, "Diana");

    bst.insert(p1);
    bst.insert(p2);
    bst.insert(p3);
    bst.insert(p4);

    // Remove an internal node (Bob)
    bst.remove(p2);
    int size = bst.size();
    bool contains_p2 = bst.contains(p2);

    assert(size == 3);
    assert(!contains_p2);

    std::cout << bst << std::endl;
    std::cout << "Test testRemoveInsideTreePerson(): passed" << std::endl
              << std::endl;
    ;
}

void testRemoveLeafPerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst;
    Person p1(1, "Alice");
    Person p2(2, "Bob");
    Person p3(3, "Charlie");

    bst.insert(p1);
    bst.insert(p2);
    bst.insert(p3);

    // Remove a leaf node (Charlie)
    bst.remove(p3);
    int size = bst.size();
    bool contains_p3 = bst.contains(p3);

    assert(size == 2);
    assert(!contains_p3);

    std::cout << bst << std::endl;
    std::cout << "Test testRemoveLeaf(): passed" << std::endl
              << std::endl;
}

void testCopyConstructorEmptyTree() {
    BinarySearchTree<int, compare_int, equal_int> bst1;
    BinarySearchTree<int, compare_int, equal_int> bst2(bst1);

    assert(bst2.size() == 0);

    std::cout << "Test testCopyConstructorEmptyTree(): passed" << std::endl
              << std::endl;
}

void testCopyConstructorNonEmptyTree() {
    BinarySearchTree<int, compare_int, equal_int> bst1;
    bst1.insert(10);
    bst1.insert(5);
    bst1.insert(15);
    bst1.insert(7);

    BinarySearchTree<int, compare_int, equal_int> bst2(bst1);

    assert(bst2.size() == 4);
    assert(bst2.contains(10) == true);
    assert(bst2.contains(5) == true);
    assert(bst2.contains(15) == true);
    assert(bst2.contains(7) == true);

    std::cout << bst1 << std::endl;
    std::cout << bst2 << std::endl;
    std::cout << "Test testCopyConstructorNonEmptyTree(): passed" << std::endl
              << std::endl;
}

void testCopyConstructorNonEmptyTreePerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst1;
    bst1.insert(Person(1, "Alice"));
    bst1.insert(Person(2, "Bob"));
    bst1.insert(Person(3, "Charlie"));

    BinarySearchTree<Person, compare_person, equal_person> bst2(bst1);

    assert(bst2.size() == 3);
    assert(bst2.contains(Person(1, "Alice")));
    assert(bst2.contains(Person(2, "Bob")));
    assert(bst2.contains(Person(3, "Charlie")));

    std::cout << "Original tree (bst1): " << std::endl;
    std::cout << bst1 << std::endl;

    std::cout << "Copied tree (bst2): " << std::endl;
    std::cout << bst2 << std::endl;

    std::cout << "Test testCopyConstructorNonEmptyTree(): passed" << std::endl
              << std::endl;
}

void testAssignmentEmptyToPopulatedPerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst1;
    bst1.insert(Person(1, "Alice"));
    bst1.insert(Person(2, "Bob"));
    bst1.insert(Person(3, "Charlie"));

    BinarySearchTree<Person, compare_person, equal_person> bst2;

    bst2 = bst1;

    assert(bst2.size() == bst1.size());
    assert(bst2.contains(Person(1, "Alice")));
    assert(bst2.contains(Person(2, "Bob")));
    assert(bst2.contains(Person(3, "Charlie")));

    std::cout << "Original tree (bst1): " << std::endl;
    std::cout << bst1 << std::endl;

    std::cout << "New tree (bst2): " << std::endl;
    std::cout << bst2 << std::endl;
}

void testAssignmentPopulatedToEmptyPerson() {
    BinarySearchTree<Person, compare_person, equal_person> bst1;
    bst1.insert(Person(1, "Alice"));
    bst1.insert(Person(2, "Bob"));
    bst1.insert(Person(3, "Charlie"));

    BinarySearchTree<Person, compare_person, equal_person> bst2;

    bst2 = bst1;
    bst1 = BinarySearchTree<Person, compare_person, equal_person>();

    assert(bst1.size() == 0);
    assert(!bst1.contains(Person(1, "Alice")));
    assert(!bst1.contains(Person(2, "Bob")));
    assert(!bst1.contains(Person(3, "Charlie")));

    std::cout << "Original tree (bst2): " << std::endl;
    std::cout << bst2 << std::endl;

    std::cout << "New tree (bst1): " << std::endl;
    std::cout << bst1 << std::endl;

    std::cout << "Test testAssignmentPopulatedToEmpty(): passed" << std::endl
              << std::endl;
}

void testEmptyTreeIterator() {
    BinarySearchTree<Person, compare_person, equal_person> bst;

    BinarySearchTree<Person, compare_person, equal_person>::const_iterator it = bst.begin();
    BinarySearchTree<Person, compare_person, equal_person>::const_iterator end = bst.end();

    assert(it == end);

    std::cout << "Test testEmptyTreeIterator: passed" << std::endl
              << std::endl;
}

void testSingleElementTreeIterator() {
    BinarySearchTree<Person, compare_person, equal_person> bst;
    bst.insert(Person(1, "Alice"));

    BinarySearchTree<Person, compare_person, equal_person>::const_iterator it = bst.begin();
    BinarySearchTree<Person, compare_person, equal_person>::const_iterator end = bst.end();

    assert(it != end);
    assert(it->id == 1);
    assert(it->name == "Alice");

    ++it;
    assert(it == end);
    std::cout << "Test testSingleElementTreeIterator: passed" << std::endl;
}

void testMultiElementTreeIterator() {
    BinarySearchTree<Person, compare_person, equal_person> bst;
    bst.insert(Person(2, "Bob"));
    bst.insert(Person(1, "Alice"));
    bst.insert(Person(3, "Charlie"));

    std::vector<Person> expected = {Person(1, "Alice"), Person(2, "Bob"), Person(3, "Charlie")};

    BinarySearchTree<Person, compare_person, equal_person>::const_iterator it = bst.begin();
    BinarySearchTree<Person, compare_person, equal_person>::const_iterator end = bst.end();

    for (const Person &expected_person : expected) {
        assert(it != end);
        assert(it->id == expected_person.id);
        assert(it->name == expected_person.name);
        ++it;
    }

    assert(it == end);

    std::cout << "Test testMultiElementTreeIterator: passed" << std::endl
              << std::endl;
}

void testConstructorWithIterators() {
    std::vector<Person> persons = {Person(2, "Bob"), Person(1, "Alice"), Person(3, "Charlie")};
    BinarySearchTree<Person, compare_person, equal_person> bst(persons.begin(), persons.end());

    assert(bst.size() == 3);
    assert(bst.contains(Person(1, "Alice")));
    assert(bst.contains(Person(2, "Bob")));
    assert(bst.contains(Person(3, "Charlie")));

    std::cout << bst << std::endl;
    std::cout << "Test testConstructorWithIterators: passed" << std::endl
              << std::endl;
}

void testPrintIF() {
    int dati[6] = {1, 2, 4, 8, 3, 17};

    BinarySearchTree<int, compare_int, equal_int> bst(dati, dati + 6);

    std::cout << "Tree: ";
    std::cout << bst << std::endl;
    is_even ie;

    std::cout << "Even numbers:" << std::endl;
    printIF(bst, ie);
}

void testPrintIFPerson() {
    std::vector<Person> persons = {Person(2, "Bob"), Person(1, "Alice"), Person(3, "Charlie")};
    BinarySearchTree<Person, compare_person, equal_person> bst(persons.begin(), persons.end());

    std::cout << "Tree: ";
    std::cout << bst << std::endl;
    starts_with_a ie;

    std::cout << "Start with A:" << std::endl;
    printIF(bst, ie);
}

void testSubtreeEmptyTree() {
    BinarySearchTree<int, compare_int, equal_int> bst;
    BinarySearchTree<int, compare_int, equal_int> subtree = bst.subtree(10);

    assert(subtree.size() == 0);
    assert(!subtree.contains(10));
    std::cout << "Test testSubtreeEmptyTree: passed" << std::endl
              << std::endl;
}

void testSubtreeRootNode() {
    BinarySearchTree<int, compare_int, equal_int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(9);

    BinarySearchTree<int, compare_int, equal_int> subtree = bst.subtree(5);

    std::cout << "Original tree: " << std::endl;
    std::cout << bst << std::endl;

    std::cout << "Subtree rooted at 10: " << std::endl;
    std::cout << subtree << std::endl;

    assert(subtree.size() == 5);
    assert(subtree.contains(5));
    std::cout << "Test testSubtreeRootNode: passed" << std::endl
              << std::endl;
}

void testSubtreeNotFound() {
    BinarySearchTree<int, compare_int, equal_int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);

    BinarySearchTree<int, compare_int, equal_int> subTree = bst.subtree(15);
    assert(subTree.size() == 0);

    std::cout << "Test testSubtreeNotFound: passed" << std::endl
              << std::endl;
}

void testSubtreeLeaf() {
    BinarySearchTree<int, compare_int, equal_int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(3);

    BinarySearchTree<int, compare_int, equal_int> subTree = bst.subtree(3);
    assert(subTree.size() == 1);

    std::cout << "Original tree: " << std::endl;
    std::cout << bst << std::endl;
    std::cout << "Subtree rooted at 3: " << std::endl;
    std::cout << subTree << std::endl;

    std::cout << "Test testSubtreeLeaf: passed" << std::endl
              << std::endl;
}

int main() {
    testDuplicateInsertAsRoot();
    testDuplicateInsertInsideTree();
    testDuplicateInsertAsLeaf();
    testDuplicateInsertAsRootPerson();
    testDuplicateInsertInsideTreePerson();
    testDuplicateInsertAsLeafPerson();
    testDuplicatePersonIdInsert();

    testContainsPerson();
    testSizePerson();

    testRemoveRootPerson();
    testRemoveInsideTreePerson();
    testRemoveLeafPerson();

    testCopyConstructorEmptyTree();
    testCopyConstructorNonEmptyTree();
    testCopyConstructorNonEmptyTreePerson();

    testAssignmentEmptyToPopulatedPerson();
    testAssignmentPopulatedToEmptyPerson();

    testEmptyTreeIterator();
    testSingleElementTreeIterator();
    testMultiElementTreeIterator();
    testConstructorWithIterators();

    testPrintIF();
    testPrintIFPerson();

    testSubtreeEmptyTree();
    testSubtreeRootNode();
    testSubtreeLeaf();
    testSubtreeNotFound();

    return 0;
}