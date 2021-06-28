**DOCUMENTATION**
=================
This is a program that calculates derived expressionы.

**DESCRIPTION**
---------------
Work of differentiator is based on unbalanced binary tree. It contains operation signs in tree nodes and objects like numbers or one letter variables in leaves.
The tree itself is stored in an array working like [My-List](https://github.com/s-a-v-a-n-n-a/My-List). Every node has access to its left and right sons and parent. There is recursion in some places: for instance, to read the expression.

**PROCESS OF WORK**
-------------------
Expression is needed to be written in [special file](https://github.com/s-a-v-a-n-n-a/Differentiator/blob/main/differentiator_file.txt). Program calculates the derivatives and then makes simplifications to avoid numbers expressions and obvious work with 0 and 1. Then program prints the result in the console and makes a LaTeX file with calculations and graphs: [The example of LaTeX file](https://github.com/s-a-v-a-n-n-a/Differentiator/blob/main/Work%20with%20LaTeX/LaTeX_file.pdf).
  
**NOTES**
---------
This program is educational. I wrote it in the first semester to learn binary trees applications.

**TREE APPEARANCE**
-------------------
![Tree apperance](https://github.com/s-a-v-a-n-n-a/Differentiator/blob/main/diff_tree_picture102.txt.png)
