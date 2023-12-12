#ifndef pokedex_h
#define pokedex_h

#include <cstdio>
#include <string>

class Key
{
public:
    int keyValue;
    std::string down;
    std::string up;
    
    Key(){
        this->keyValue = 0;
        this->down = std::string("");
        this->up = std::string("");
    };

    Key(int keyValue, char name){
        this->keyValue = keyValue;
        this->down = name + std::string("_D");
        this->up = name + std::string("_U");

        // iprintf("DOWN -> %s\n", this->down.c_str());
        // iprintf("UP -> %s\n", this->up.c_str());
    };
};

Key* init_keys();

#endif