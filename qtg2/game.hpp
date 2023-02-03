#ifndef __QTG_GAME_HPP__

#define __QTG_GAME_HPP__

#include "block.hpp"
#include "entity_list.hpp"
#include <vector>

namespace qtg {

class Game {
	public:
	 	Game(map_size_t x, map_size_t y);
		
	private:
		map_size_t __x, __y;
		Block** __blocks;
		EntityList __entities;
		
};

};

#endif /* end of include guard: __QTG_GAME_HPP__ */
