// test publish/subscribe, mostly from Jason's template 10/17, tentative syntax may be wrong
// Kyle Lam
// Updated: 10/23

#include <map>
#include <string>
#include <iostream>
#include <list>
#include <cstdlib>

static std::map<std::string&, std::list</*not entirely sure what goes in here yet*/>> subs;

void Subscribe(const std::string& key, /*function call?*/) {
	// TODO parse key into map, find matching and add function call to return requested data type (?)
}

template<T>
void Subscribe(const std::string& key, T data); //declare template

void Publish(const std::string& key, void* ptr, std::size_t size) {
	// TODO give key/function call to push data (?) and add to list
}

void Iterate();

// TODO define keys (enum?)

void main() {
	// TODO list iterators to feed data to subscribers (?)
}