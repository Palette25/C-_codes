#include "State.hpp"
#include "Parser.hpp"
State* DataState::_instance = NULL;
State* TagNameState::_instance = NULL;
State* DataState::getInstance() {
	if (_instance != NULL) return _instance;
	else {
		_instance = new DataState;
		return _instance;
	}
}
void DataState::destroyInstance() {
	if (_instance != NULL) {
		delete _instance;
		_instance = NULL;
	}
}
void DataState::handleOneChar(Parser* parser, char ch) {
	if (ch == '<'&&_cache.size() > 0) {
		bool flag = 0;
		for (int i = 0; i < _cache.size(); i++)
			if (_cache[i] != ' ') flag = 1;
		if (flag == 1) emit(parser->getBulider());
		_cache.clear();
	}
	else  if (ch != '<') _cache += ch;
}
void DataState::emit(Bulider* dest) {
	Token t1;
	while (1) {
		if (_cache[0] == ' ') {
			if (_cache.size() == 1) _cache.clear();
			else _cache = _cache.substr(1);
		}
		else break;
	}
	for (int i = _cache.size() - 1; i > 0 && _cache.size() > 0; i--){
		if (_cache[i] == ' ') _cache= _cache.substr(0, i);
		else break;
    }
	t1.content = _cache;
	t1.type = "DATA";
	t1.depth = 0;
	dest->handleOneToken(t1);
}
State* TagNameState::getInstance(){
	if(_instance!=NULL) return _instance;
	else {
		_instance = new TagNameState;
		return _instance;
	}
}
void TagNameState::destroyInstance(){
	if(_instance!=NULL) {
		delete _instance;
		_instance = NULL;
	}
}
void TagNameState::handleOneChar(Parser* parser, char ch) {
	if (ch == '>') {
		emit(parser->getBulider());
		_cache.clear();
	}
	else _cache += ch;
}
void TagNameState::emit(Bulider* dest) {
	Token t1;
	t1.content = _cache;
	t1.type = "TAGNAME";
	t1.depth = 0;
	dest->handleOneToken(t1);
}
