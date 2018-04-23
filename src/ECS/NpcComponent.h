#ifndef _NPCCOMPONENT_H_
#define _NPCCOMPONENT_H_

#include <string>
#include <iostream>
#include <LuaBridge/LuaBridge.h>

#include "ECS.h"

class NpcComponent : public Component{
public:
	NpcComponent(luabridge::LuaRef& NpcTable) {
		using namespace luabridge;
		auto phraseRef = NpcTable["phrase"];
		if (phraseRef.isString()) {
			phrase = phraseRef.cast<std::string>();
		}
		else {
			std::cout << "Error, NpcComponent.phrase is not a string!" << std::endl;
		}
	}

	~NpcComponent() {}
	
	void update() override {
		//std::cout << phrase << std::endl;
	}

	void getPhrase(const std::string& phrase){
		this->phrase = phrase;
	}
	
	std::string getPhrase() const {
		return phrase;
	}
	
	private:
		std::string phrase;
};

#endif