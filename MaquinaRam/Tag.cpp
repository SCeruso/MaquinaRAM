#include "Tag.h"

Tag::Tag(string tag, int ln) : tag_(tag), line_(ln)
{
}
Tag::Tag(string s) : tag_(s){}

Tag::~Tag()
{
}


string Tag::get_tag()
{
	return tag_;
}


int Tag::get_line()
{
	return line_;
}
bool Tag::operator == (Tag& other) {
	return ((this->get_tag() == other.get_tag()) /*&& (this->get_line == other.get_line)*/);	//Solo comparando los nombres ya deberiamos saber que son iguales.
}