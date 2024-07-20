# C++ implementation of a Binary Search Tree

## Description

Il progetto consiste nell'implementazione di una classe templata `BinarySearchTree` in C++, che rappresenta un
albero binario di ricerca. Un albero binario di ricerca è una struttura dati organizzata in modo gerarchico, in cui ogni
nodo può avere al massimo due figli, con la proprietà che il sottoalbero sinistro di un nodo contiene solo valori minori
di quello del nodo stesso, mentre il sottoalbero destro contiene solo valori maggiori.

## Features

- Inserimento e Rimozione: La classe supporta l'inserimento di nuovi nodi, la rimozione di nodi esistenti, e la verifica dell’esistenza di un nodo con un determinato valore.
- Iterazione: Fornisce iteratori per iterare attraverso gli elementi dell'albero in ordine.
- Copie e Assegnamenti: Implementa costruttori di copia e operatore di assegnamento per gestire la creazione e la
  copia di alberi.
- Sottoalberi: Fornisce un metodo per ottenere il sottoalbero a partire da un nodo con un valore specifico.
- Stampa: Fornisce un metodo per stampare i valori dell’albero che soddisfano un determinato predicato.

## Design and implementation

### Generic implementation

La classe `BinarySearchTree` è implementata in modo generico, permettendo l'utilizzo con diversi tipi di dati e funtori per la personalizzazione delle operazioni di confronto e uguaglianza.
Questo la rende flessibile e riutilizzabile
senza modifiche significative in contesti diversi, garantendo un codice mantenibile e scalabile.
I funtori `Compare` e `Equal` determinano il comportamento di ordinamento e di uguaglianza degli elementi,
garantendo che l'albero mantenga la sua struttura ordinata in base a criteri specifici definiti in base alle necessità.

### Node structure

Internamente, la classe `BinarySearchTree` gestisce i suoi dati tramite una struttura a nodi, ognuno dei quali contiene un valore di tipo T e puntatori ai figli sinistro e destro. La radice dell'albero è rappresentata da un puntatore privato root, che consente l'accesso e la manipolazione dell'intera struttura dell'albero.

### Immutability

Gli elementi all'interno della classe `BinarySearchTree` sono immutabili una volta inseriti nell'albero. Ciò significa che il valore di ogni nodo non può essere modificato direttamente dopo l'inserimento. Questo vincolo di immutabilità è garantito dalla progettazione della classe e dai meccanismi di accesso ai dati, che permettono solo operazioni di
lettura e di confronto.

### Memory management

La classe BinarySearchTree gestisce la memoria in modo responsabile utilizzando operazioni di allocazione e
deallocazione controllate. Ogni nodo creato dinamicamente viene deallocato correttamente durante le operazioni di rimozione e distruttore dell'albero, prevenendo così perdite di memoria e consentendo un utilizzo efficiente delle risorse del sistema.\
Il copy constructor, l'operatore di assegnazione e il distruttore sono stati implementati per garantire la gestione corretta della memoria. Il metodo `clear`, invocato dal distruttore, dealloca tutta la memoria associata ai nodi dell’albero.

### Iterators

La classe `BinarySearchTree` fornisce iteratori per consentire l'iterazione attraverso gli elementi dell'albero in ordine. Gli iterator sono implementati come classi interne private, che forniscono un'interfaccia per l'accesso ai nodi dell'albero in modo controllato e sicuro. Gli iteratori supportano le operazioni di incremento, decremento, confronto e dereferenziazione, consentendo l'iterazione in modo simile a quello di altre strutture dati standard in C++.\
Gli iteratori sono progettati per garantire la sicurezza e la consistenza durante l'iterazione, evitando accessi non autorizzati o comportamenti indefiniti.

## Usage

To compile the sample project, run the following command:

```bash
makefile && ./main.exe
```

To generate the documentation, run the following command and open the `index.html` file in the `html` directory:

```bash
doxygen
```

To clean the compiled files, run:

```bash
make clean
```
