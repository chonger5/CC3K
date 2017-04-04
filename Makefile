CXX = g++-5
CXXFLAGS = -std=c++14 -MMD -g -Werror=vla
OBJECT = main.o controller.o square.o character.o hero.o enemy.o item.o cell.o gold.o potion.o window.o floor.o tile.o path.o stairway.o door.o wall.o orc.o human.o dwarf.o elf.o merchant.o dragon.o halfling.o shade.o drow.o vampire.o troll.o goblin.o coordinate.o
DEPENDS = ${OBJECT:.o=.d}

cc3k: ${OBJECT}
	${CXX} ${CXXFLAGS} ${OBJECT} -o cc3k -lX11

-include ${DEPENDS}

.PHONY: clean
clean:
	rm *.o *.d cc3k

