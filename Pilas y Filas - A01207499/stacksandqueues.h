/*
 * saq.h
 *
 *  Created on: 10/08/2015
 *      Author: pperezm
 *
 *	Actividad de Programación: Listas Encadenadas
 *		Modifided on: 27/06/2017
 *			Author: César Buenfil Vázquez A01207499
 *
 */

#ifndef STACKSANDQUEUES_H_
#define STACKSANDQUEUES_H_

#include <iostream>
#include <string>
#include <cctype>
#include <queue>
#include <stack>

using namespace std;

class StacksAndQueues {
private:
	queue<string> tokenize(string);
	bool hasHigherPrecedence(const string&, const string&);

public:
	bool balancedBrackets(const string&);
	queue<int> merge(const queue<int>&, const queue<int>&);
	string convertInfixToPostfix(const string&);
};

queue<string> StacksAndQueues::tokenize(string str) {
	int i = 0;
	int length = str.size();
	string aux;
	queue<string> result;

	while (i < length) {
		if (isdigit(str[i])) {
			aux.clear();
			do {
				aux += str[i];
				i++;
			} while(isdigit(str[i]));
			result.push(aux);
		} else if (isspace(str[i])) {
			i++;
		} else {
			aux.clear();
			aux += str[i];
			result.push(aux);
			i++;
		}
	}
	return result;
}

bool StacksAndQueues::hasHigherPrecedence(const string &stackTop, const string &op) {
	return !((stackTop == string("+") || stackTop == string("-")) &&
			 (op == string("*")       || op == string("/")));
}

bool StacksAndQueues::balancedBrackets(const string &expr) {

	stack<char> stack;

	for(int i = 0; i<expr.size(); i++){
		switch(expr[i]){
			case '(':
			case '{':
			case '[':
				stack.push(expr[i]);
				break;
			case ')':
				if(stack.empty() || stack.top() != '('){
					return false;
				}
				else{
					stack.pop();
				}
				break;
			case '}':
				if(stack.empty() || stack.top() != '{'){
					return false;
				}
				else{
					stack.pop();
				}
				break;
			case ']':
				if(stack.empty() || stack.top() != '['){
					return false;
				}
				else{
					stack.pop();
				}
				break;
			default:
				break;
		}
	}
	if(!stack.empty()){
		return false;
	}
	return true;
}

queue<int> StacksAndQueues::merge(const queue<int> &queue1, const queue<int> &queue2) {

	queue<int> result;
	queue<int> q1(queue1);
	queue<int> q2(queue2);

	while(!q1.empty() && !q2.empty()){
		if(q1.front()<q2.front()){
			result.push(q1.front());
			q1.pop();
		}
		else if(q1.front()>q2.front()){
			result.push(q2.front());
			q2.pop();
		}
	}
	while(!q1.empty()){
		result.push(q1.front());
		q1.pop();
	}
	while(!q2.empty()){
		result.push(q2.front());
		q2.pop();
	}
	return result;
}

string StacksAndQueues::convertInfixToPostfix(const string &expr) {
	queue<string> fila;
	queue<string> token = tokenize(expr);
	stack<string> pila;
	string aux;

	while(!token.empty()){
		aux = token.front();
		token.pop();

		if(aux == "("){
			pila.push(aux);
		}
		else if(aux == "+"||aux == "-"||aux == "*"||aux == "/"){
			while(!pila.empty()&&pila.top()!="("){
				if(hasHigherPrecedence(pila.top(),aux)){
					fila.push(pila.top());
					pila.pop();
				}
				else break;
			}
			pila.push(aux);
		}
		else if(aux[0] == ')'){
			while(!pila.empty()&&pila.top()!="("){
				fila.push(pila.top());
				pila.pop();
			}
			if(!pila.empty()&&pila.top()=="("){
				pila.pop();
			}
		}
		else{
			fila.push(aux);
		}
	}
	while(!pila.empty()){
		fila.push(pila.top());
		pila.pop();
	}

	aux = "";

	while(!fila.empty()){
		aux += fila.front();
		if(fila.size()>1){
			aux += " ";
		}
		fila.pop();
	}
	return aux;
}

#endif /* STACKSANDQUEUES_H_ */
