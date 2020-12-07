#pragma once

const size_t MAX_OP_LEN = 255;
const size_t DEF_SIZE = 4;

const char DEFAULT_FILE_NAME[] = "differentiator_file.txt";
const char DEFAULT_TEX_FILE_NAME[] = "LaTeX_file.tex";

const int PHRASES_AMOUNT = 4;

const char *phrase_bank[] = 
{
	"Делаем вид, что умеем считать производные:\n",
	"Матан - это моя жизнь!\n",
	"С этой программой не нужно быть гением, чтобы вычислять скорость съезжающей крыши\n",
	"Меня зовут Аня Савчук, но друзья зовут меня вычислять производные\n"
}

const int  MAX_MESSAGE_LEN = 255;
const int  MAX_PICTURE_NAME = 255;

const int MAX_ANSWER_LEN = 4;

const char PICTURE_NAME[] = "diff_tree_picture";
const char PICTURE_EXPANSION[] = "png";
const char PICTURE_CODE_EXPANSION[] = "txt";

const char COLOR[] = "#FEC9E3";
const char COLOR_OTHER[] = "HotPink";

const char NUMBER    = 0;
const char VARIABLE  = 1;
const char OPERATION = 2;
const char NOTHING   = 3;
