#pragma once

#include <stdio.h>
#include <stdlib.h>

const size_t MAX_OP_LEN = 255;
const size_t DEF_SIZE   = 4;
const int    LETTERS    = 26;
const size_t MAX_EXPR_AMOUNT_TO_PRINT = 18;
const size_t MIN_EXPR_AMOUNT_TO_PRINT = 13;

const char DEFAULT_FILE_NAME[]     = "differentiator_file.txt";
const char DEFAULT_TEX_FILE_NAME[] = "LaTeX_file.tex";
const char DEFAULT_PDF_FILE_NAME[] = "LaTeX_file.pdf";

const int PHRASES_AMOUNT = 13;
const int PROHIBITED_FOR_RANDOM_PHRASES_AMOUNT = 6;

const int IT_WAS_THAT    = 0;
const int FIRST_GRAPHICS = 1;
const int FIRST_DEPR     = 2;
const int SIMPLIFIER     = 3;
const int FINAL_ANSWER   = 4;
const int GRAPHICS       = 5;

const int FORMULA = 0;
const int GRAPH   = 1;

const int NOT_END = 0;
const int END     = 1;

const char INTRODUCTION[] = "{\\bf Introduction}\n\n"
							"My name is Anna Savchuk and in this paper I will present to caring reader the process of artificial intelligence training to calculate deprivatives. "
							"The problems of calculating difficult expression is widely spread specially among \\sout{us} first year students, "
							"so as their representative I decided to make a program that will be able to differentiate and easily simplify mathematical expressions.\n\n";

const char PLAN[] = "Differentiating complex expressions I reffer to MIPT lections and textbooks but nothing can save me from making mistakes "
					"so I must apologize for making some simple calculations. In my defense I can say that they train attention and write derivatives of simple functions into the subconscious. "
					"In my work I'll break down a big expression, simplify it, take a derivative and look at it. This process can go on endlessly, but even this is a great success for me.\n\n";


const char REFERENCES[] = "{\\bf My references:}\n"
						  "\\begin{itemize}\n\n"
	                      "\\item Field for experiments\n\n https://github.com/s-a-v-a-n-n-a/Differentiator\n\n"
						  "\\item Lections by Redkozubov V.V. \n\n https://www.youtube.com/playlist?list=PLthfp5exSWEoItZUXCG3Bhrn3AFzw8AKK\n\n"
						  "\\end{itemize}\n\n";

const char DIFF_VARIABLE = 'x';

const int  MAX_MESSAGE_LEN  = 255;
const int  MAX_PICTURE_NAME = 255;

const int MAX_ANSWER_LEN = 4;

const char PICTURE_NAME[]           = "diff_tree_picture";
const char PICTURE_EXPANSION[]      = "png";
const char PICTURE_CODE_EXPANSION[] = "txt";

const char COLOR[]       = "#FEC9E3";
const char COLOR_OTHER[] = "HotPink";

const char NUMBER    = 0;
const char VARIABLE  = 1;
const char OPERATION = 2;
const char NOTHING   = 3;

const long long ONE_STEP    = 1;
const long long TWO_STEPS   = 2;
const long long THREE_STEPS = 3;

const double    delta = 0.1;
const long long MAX_X = 10;
const long long MIN_X = 1;

