# Flex and Bison Compiler

This project was made as a requirement for the Compilers Exam by [Daniela Musotto](https://github.com/dandan357) and [Pierfrancesco Martinello](https://github.com/pierfrancescomartinello)

---
Index
- [The Idea](https://github.com/pierfrancescomartinello/Flex-Bison-Compiler/README.md#the-idea)
- [The Input](https://github.com/pierfrancescomartinello/Flex-Bison-Compiler/README.md#the-input)
- [The Lexical Analyzer](https://github.com/pierfrancescomartinello/Flex-Bison-Compiler/README.md#the-lexical-analyzer)
- [The Symbol Table](https://github.com/pierfrancescomartinello/Flex-Bison-Compiler/README.md#the-symbol-table)
- [Examples](https://github.com/pierfrancescomartinello/Flex-Bison-Compiler/README.md#example)

---
## The Idea

---
## The Input

---
## The Lexical Analyzer

---
## The Symbol Table

To store the stages and all their details it has been chosen to use a set of linekd lists since the valies of the stages are read simultaneously by the program and it is allowed to have an arbitrary number of stages.

In order to store the information of about costs and discounts, two different hashtables, $scontoHash$ and $prezzoHash$, are used; since it's not necessarily true that discounts and costs appear on the same order they are defined in the first part of the input. Ancillary functions to calculate the hash, insertion and lookup are developed.


### Functions defined for the semantic actions

- $setTappa(\mathit{$}2, \mathit{$}5)$ <br> Creation of a new stage that has as its city the first parameter and as location the second one; insertion in its linked list.

- $detBind()$ <br> Creation of a binding between the last stake read (which is not yet filled) and the list of details referred to that sepcific stage.


- $detInit(\mathit{$}2)$ <br> Creation of a new stage detail that has as its parameter the name of the type of tickets; insertion  on the adapt linked list.

- $catInit(\mathit{$}1, \mathit{$}3)$ <br> Creation of a new detail that has as its first parameter the name of the type of category and as its second the number of ticket sold of that category;  insertion into the proper linked list. 

- $catBind()$ <br> Creation of pointers binding between the stage's last detail (which is yet to be filled) and the list of details that refers to that particular stage detail.


- $setPrezzo(\mathit{$}2, \mathit{$}4)$ <br> It is called when a cost is read and it's inserted in the corresponding hashtable

- $setSconto(\mathit{$}1, \mathit{$}3)$ <br> It is called when a discount is read and it's inserted in the corresponding hashtable
---
## Example

Those are the examples on the repository:

- [input.txt](https://github.com/pierfrancescomartinello/Flex-Bison-Compiler/input.txt): <br> this is the idea of thex given with the assignment. The code will produce a correct output.

- [input2.txt](https://github.com/pierfrancescomartinello/Flex-Bison-Compiler/input2.txt)<br> The code will produce a correct output, showing that is capable of analysing a variable number of $\<category name\>$ , $\<number of ticket printed\>$ and $\<type of ticket\>$, as long as they are compatible with the number and the identificators of the second and third part of the input, respectively.


- [input3.txt](https://github.com/pierfrancescomartinello/Flex-Bison-Compiler/input3.txt) <br> The execution will fail since the parser recognise an incorrect input.


- [input4.txt](https://github.com/pierfrancescomartinello/Flex-Bison-Compiler/input4.txt) <br> The execution will fail since the parser recognise an incorrect input.
