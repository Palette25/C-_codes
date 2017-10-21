#include "Bulider.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
Bulider* Bulider::_instance = NULL;
Bulider* Bulider::getInstance(){
	if(_instance!=NULL) return _instance;
	else {
		_instance = new Bulider;
		return _instance;
	}
}
void Bulider::destroyInstance(){
	if(_instance!=NULL) {
		delete _instance;
		_instance = NULL;
	}
}
void Bulider::handleOneToken(Token token) {
	
	if (token.content[0] != '/') {
		if (_stack.size() > 0) {
			token.depth = _stack.top().depth + 2;
			if (_stack.top().content.size() == 0) token.depth = 0;
		}
		_tokens.push_back(token);
	}
	if (token.type == "TAGNAME") {
		if (_stack.size() > 0 && token.content[0] == '/') {
			string str1;
			str1 += '/';
			str1 += (_stack.top()).content;
			if (str1 == token.content) {
				_stack.pop();
			}
			else _error = 1;
		}
		else {
			if (_stack.size() == 0) token.depth = 0;
			else token.depth = _stack.top().depth + 2;
			_stack.push(token);
		}
	}
}
void Bulider::display(){
	if (_error == 1||_stack.size()!=0) cout << "INVALID INPUT" << endl;
	else {
		for (int i = 0; i < _tokens.size(); i++) {
			for (int j = 0; j < _tokens[i].depth; j++)
				       cout << " ";
			if (_tokens[i].type == "DATA") cout << _tokens[i].content << endl;
			else  if(_tokens[i].content.size()>0) cout << _tokens[i].content << ":" << endl;
		}
	}
}