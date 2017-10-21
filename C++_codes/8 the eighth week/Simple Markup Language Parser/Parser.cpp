#include "Parser.hpp"
Parser* Parser::_instance = NULL;
Parser* Parser::getInstance() {
	if(_instance!=NULL) return _instance;
	else {
		_instance = new Parser;
		return _instance;
	}
}
void Parser::destroyInstance() {
	if(_instance!=NULL) {
		delete _instance;
		_instance = NULL;
	}
}
void Parser::consumeOneChar(char ch) {
		_state->handleOneChar(_instance, ch);
		if (ch == '<') setState(TagNameState::getInstance());
		if (ch == '>') setState(DataState::getInstance());
}