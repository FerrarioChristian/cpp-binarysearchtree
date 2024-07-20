/**
  @file BinarySearchTree.hpp

  @brief File di dichiarazioni/definizioni della classe BinarySearchTree templata
*/

#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ostream>

/**
  @brief classe BinarySearchTree

  La classe implementa un generico albero binario di ricerca di oggetti T.
  L'ordinamento è realizzato tramite il funtore Compare che prende
  due valori a e b, e ritorna vero se a viene prima di b.
  La valutazione di uguaglianza è realizzata tramite un secondo funtore Equal.
*/
template <typename T, typename Compare, typename Equal>
class BinarySearchTree {

private:
    /**
      @brief struttura Nodo

      Struttura dati nodo interna che viene usata per creare
      e popolare l'albero.
    */
    struct Node {
        const T value; ///< Valore del nodo
        Node *left;    ///< Puntatore al figlio sinistro
        Node *right;   ///< Puntatore al figlio destro

        /**
         * @brief Costruttore di default
         *
         * Inizializza un nodo con valore di default e puntatori a nullptr.
         *
         * @post left == nullptr
         * @post right == nullptr
         */
        Node() : left(nullptr), right(nullptr) {}

        /**
         * @brief Costruttore secondario
         *
         * Inizializza un nodo con il valore specificato e puntatori ai figli specificati.
         *
         * @param v Valore da memorizzare nel nodo.
         * @param l Puntatore al figlio sinistro.
         * @param r Puntatore al figlio destro.
         */
        Node(const T &v, Node *l, Node *r) : value(v), left(l), right(r) {}

        /**
         * @brief Copy constructor
         *
         * Costruisce un nuovo nodo come copia di un altro nodo.
         *
         * @param other Nodo da copiare
         */
        Node(const Node &other) : value(other.value), left(nullptr), right(nullptr) {}
    };

    Node *root;      ///< Puntatore alla radice dell'albero
    Compare compare; ///< Funtore di confronto
    Equal equals;    ///< Funtore di uguaglianza

    /**
     * @brief Visita ricorsivamente l'albero in ordine e stampa i valori.
     *
     * @param os Stream di output.
     * @param node Nodo radice del sottoalbero da visitare.
     */
    void toString(std::ostream &os, const Node *node) const {
        if (node != nullptr) {
            toString(os, node->left);
            os << node->value << " ";
            toString(os, node->right);
        }
    }

    /**
     * @brief Calcola ricorsivamente la dimensione del sottoalbero.
     *
     * @param node Nodo radice del sottoalbero.
     * @return La dimensione del sottoalbero.
     */
    int size(const Node *node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + size(node->left) + size(node->right);
    }

    /**
     * @brief Rimuove ricorsivamente il nodo con il valore specificato dall'albero.
     *
     * @param node Puntatore al nodo radice del sottoalbero corrente.
     * @param value Valore da rimuovere.
     */
    void deleteNode(Node *&node, const T &value) {
        if (node == nullptr) {
            return;
        }
        if (compare(value, node->value)) {
            deleteNode(node->left, value);
        } else if (compare(node->value, value)) {
            deleteNode(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node *temp = node->right;
                delete node;
                node = temp;
            } else if (node->right == nullptr) {
                Node *temp = node->left;
                delete node;
                node = temp;
            } else {
                Node *temp = node->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                Node *newNode = new Node(temp->value, node->left, node->right);
                delete node;
                node = newNode;
                deleteNode(node->right, temp->value);
            }
        }
    }

    /**
     * @brief Cancella ricorsivamente tutti i nodi dell'albero.
     *
     * @param node Nodo radice del sottoalbero da cancellare.
     */
    void deleteSubtree(Node *node) {
        if (node != nullptr) {
            deleteSubtree(node->left);
            deleteSubtree(node->right);
            delete node;
        }
    }

    /**
     * @brief Crea una copia ricorsiva del sottoalbero.
     *
     * @param node Nodo radice del sottoalbero da copiare.
     * @return Puntatore alla radice del sottoalbero copiato.
     */
    Node *copyNodes(Node *node) const {
        if (node == nullptr) {
            return nullptr;
        }
        Node *newNode = new Node(node->value, nullptr, nullptr);
        newNode->left = copyNodes(node->left);
        newNode->right = copyNodes(node->right);
        return newNode;
    }

    /**
     * @brief Trova ricorsivamente il nodo con il valore specificato.
     *
     * @param node Nodo radice del sottoalbero corrente.
     * @param value Valore da cercare.
     * @return Puntatore al nodo con il valore specificato, se presente; nullptr altrimenti.
     */
    Node *findNode(Node *node, const T &value) const {
        if (!node)
            return nullptr;
        if (equals(value, node->value))
            return node;
        if (compare(value, node->value))
            return findNode(node->left, value);
        return findNode(node->right, value);
    }

public:
    /**
      @brief Costruttore di default

      Inizializza un albero binario di ricerca vuoto.

      @post root == nullptr
     */
    BinarySearchTree() : root(nullptr) {}

    /**
     * @brief Copy constructor
     *
     * Costruisce un nuovo albero binario di ricerca come copia di un altro albero.
     *
     * @param bst BinarySearchTree da copiare
     *
     * @throw std::bad_alloc possibile eccezione di allocazione
     */
    BinarySearchTree(const BinarySearchTree &bst) : root(nullptr), compare(bst.compare), equals(bst.equals) {
        try {
            if (bst.root) {
                root = copyNodes(bst.root);
            }
        } catch (...) {
            clear();
            throw;
        }
    }

    /**
     * @brief Distruttore
     *
     * Dealloca tutta la memoria occupata dall'albero binario di ricerca.
     *
     * @post tutti i nodi dell'albero sono stati deallocati, root = nullptr
     */
    ~BinarySearchTree() {
        clear();
    }

    /**
     *
     * @brief Costruttore tramite iteratori.
     *
     * Costruttore che crea un binary search tree riempito con dati
     * presi da una sequenza identificata da un iteratore generico di inizio e uno di fine.
     *
     * @tparam Iter tipo dell'iteratore
     * @param begin iteratore di inizio sequenza
     * @param end iteratore di fine sequenza
     *
     * @throw std::bad_alloc possibile eccezione di allocazione
     */
    template <typename Iter>
    BinarySearchTree(Iter begin, Iter end) : root(nullptr) {
        try {
            for (Iter it = begin; it != end; ++it) {
                insert(*it);
            }
        } catch (...) {
            clear();
            throw;
        }
    }

    /**
     * @brief Operatore di assegnamento
     *
     * Assegna un albero binario di ricerca a un altro.
     *
     * @param bst BinarySearchTree da copiare
     * @return reference all'albero this
     * @throw std::bad_alloc possibile eccezione di allocazione
     */
    BinarySearchTree &operator=(const BinarySearchTree &bst) {
        try {
            if (this != &bst) {
                BinarySearchTree tmp(bst);
                std::swap(root, tmp.root);
                std::swap(compare, tmp.compare);
                std::swap(equals, tmp.equals);
            }
        } catch (...) {
            clear();
            throw;
        }
        return *this;
    }

    /**
     * @brief Inserisce un valore nell'albero binario di ricerca.
     *
     * Aggiunge un nuovo nodo con il valore specificato nell'albero.
     *
     * @param value Il valore da inserire.
     */
    void insert(const T &value) {
        Node *node = new Node(value, nullptr, nullptr);
        if (!root) {
            root = node;
            return;
        }

        Node *current = root;
        Node *parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (compare(value, current->value)) {
                current = current->left;
            } else if (compare(current->value, value)) {
                current = current->right;
            } else {
                delete node;
                return;
            }
        }

        if (compare(value, parent->value)) {
            parent->left = node;
        } else {
            parent->right = node;
        }
    }

    /**
     * @brief Verifica se un valore è presente nell'albero.
     *
     * Cerca il valore specificato nell'albero.
     *
     * @param value Il valore da cercare.
     * @return true se il valore è presente, false altrimenti.
     */
    bool contains(const T &value) const {
        Node *current = root;
        while (current != nullptr) {
            if (equals(value, current->value)) {
                return true;
            } else if (compare(value, current->value)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    /**
     * @brief Restituisce la dimensione dell'albero.
     *
     * Calcola il numero di nodi presenti nell'albero.
     *
     * @return Il numero di nodi presenti nell'albero.
     */
    int size() const {
        return size(root);
    }

    /**
     * @brief Rimuove un valore dall'albero.
     *
     * Elimina il nodo con il valore specificato dall'albero, se presente.
     *
     * @param value Il valore da rimuovere.
     */
    void remove(const T &value) {
        if (root == nullptr) {
            return;
        }
        deleteNode(root, value);
    }

    /**
     * @brief Cancella tutti i nodi dell'albero.
     *
     * Dealloca tutti i nodi dell'albero, rendendolo vuoto.
     */
    void clear() {
        deleteSubtree(root);
        root = nullptr;
    }

    /**
     * @brief Restituisce il sottoalbero cha ha come radice il nodo con il valore specificato.
     *
     * Questo metodo cerca il nodo con il valore specificato e restituisce un nuovo albero binario di ricerca
     * che rappresenta il sottoalbero cha ha come radice il nodo trovato.
     *
     * @param value Il valore del nodo radice del sottoalbero da restituire.
     * @return Un nuovo albero binario di ricerca che rappresenta il sottoalbero radicato nel nodo con il valore specificato.
     *         Se il valore non è presente nell'albero, viene restituito un albero vuoto.
     */
    BinarySearchTree<T, Compare, Equal> subtree(const T &value) const {
        Node *subRoot = findNode(root, value);
        BinarySearchTree<T, Compare, Equal> newTree;
        if (subRoot != nullptr) {
            newTree.root = copyNodes(subRoot);
        }
        return newTree;
    }

    /**
     * @brief Funzione amica per la stampa dell'albero.
     *
     * Sovraccarica l'operatore di stream per permettere la stampa dell'albero.
     *
     * @param os Stream di output.
     * @param bst Albero binario di ricerca da stampare.
     * @return Lo stream di output.
     */
    friend std::ostream &operator<<(std::ostream &os, const BinarySearchTree &bst) {
        bst.toString(os, bst.root);
        return os;
    }

    /**
     * @brief Iteratore costante per l'albero binario di ricerca.
     */
    class const_iterator {
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;

        /**
         * @brief Costruttore di default.
         *
         * Inizializza un iteratore costante.
         */
        const_iterator() : n(nullptr), root(nullptr) {}

        /**
         * @brief Costruttore di copia.
         *
         * Inizializza un iteratore costante copiandone un altro.
         *
         * @param other L'iteratore da copiare.
         */
        const_iterator(const const_iterator &other) : n(other.n), root(other.root) {}

        /**
         * @brief Operatore di assegnamento.
         *
         * Assegna un iteratore costante a un altro.
         *
         * @param other L'iteratore da copiare.
         * @return Un riferimento all'iteratore assegnato.
         */
        const_iterator &operator=(const const_iterator &other) {
            n = other.n;
            root = other.root;
            return *this;
        }

        /**
         * @brief Distruttore.
         */
        ~const_iterator() {}

        /**
         * @brief Dereferenzia l'iteratore.
         *
         * @return Il riferimento al valore puntato dall'iteratore.
         */
        reference operator*() const {
            return n->value;
        }

        /**
         * @brief Accede al membro puntato dall'iteratore.
         *
         * @return Un puntatore al valore puntato dall'iteratore.
         */
        pointer operator->() const {
            return &(n->value);
        }

        /**
         * @brief Operatore di post-incremento.
         *
         * Avanza l'iteratore alla posizione successiva.
         *
         * @return L'iteratore alla posizione precedente.
         */
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        /**
         * @brief Operatore di pre-incremento.
         *
         * Avanza l'iteratore alla posizione successiva.
         *
         * @return Un riferimento all'iteratore avanzato.
         */
        const_iterator &operator++() {
            if (n == nullptr) {
                return *this;
            }

            if (n->right != nullptr) {
                n = n->right;
                while (n->left != nullptr) {
                    n = n->left;
                }
            } else {
                const Node *parent = nullptr;
                const Node *current = root;
                while (current != n) {
                    if (compare(n->value, current->value)) {
                        parent = current;
                        current = current->left;
                    } else {
                        current = current->right;
                    }
                }
                n = parent;
            }
            return *this;
        }

        /**
         * @brief Operatore di uguaglianza.
         *
         * Confronta due iteratori per uguaglianza.
         *
         * @param other L'iteratore da confrontare.
         * @return true se gli iteratori sono uguali, false altrimenti.
         */
        bool operator==(const const_iterator &other) const {
            return n == other.n;
        }

        /**
         * @brief Operatore di disuguaglianza.
         *
         * Confronta due iteratori per disuguaglianza.
         *
         * @param other L'iteratore da confrontare.
         * @return true se gli iteratori sono diversi, false altrimenti.
         */
        bool operator!=(const const_iterator &other) const {
            return n != other.n;
        }

    private:
        const Node *n;
        const Node *root;
        Compare compare;

        /**
         * @brief Costruttore privato per inizializzare un iteratore con un nodo specifico.
         *
         * @param node Il nodo da cui iniziare l'iterazione.
         * @param root La radice dell'albero.
         * @param comp Il funtore di confronto.
         */
        const_iterator(const Node *node, const Node *root, Compare comp) : n(node), root(root), compare(comp) {}

        friend class BinarySearchTree;
    };

    /**
     * @brief Restituisce un iteratore costante all'inizio dell'albero.
     *
     * @return Un iteratore costante al primo elemento dell'albero.
     */
    const_iterator begin() const {
        const Node *n = root;
        if (n != nullptr) {
            while (n->left != nullptr) {
                n = n->left;
            }
        }
        return const_iterator(n, root, compare);
    }

    /**
     * @brief Restituisce un iteratore costante alla fine dell'albero.
     *
     * @return Un iteratore costante alla posizione successiva all'ultimo elemento dell'albero.
     */
    const_iterator end() const {
        return const_iterator(nullptr, root, compare);
    }
};

/**
 * @brief Funzione globale che stampa i valori dell'albero che soddisfano un predicato.
 *
 * @param bst Albero binario di ricerca sorgente.
 * @param pred Predicato da soddisfare.
 */
template <typename T, typename Comp, typename Equal, typename P>
void printIF(const BinarySearchTree<T, Comp, Equal> &bst, P pred) {
    typename BinarySearchTree<T, Comp, Equal>::const_iterator i, ie;

    for (i = bst.begin(), ie = bst.end(); i != ie; ++i) {
        if (pred(*i))
            std::cout << *i << " ";
    }
}

#endif // BINARYSEARCHTREE_HPP