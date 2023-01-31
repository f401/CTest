#include "entity_list.hpp"

using namespace qtg;

class SubEntity : public Entity {
public:
  SubEntity(): Entity(Vector2i(1, 1)) {}
  virtual void on_start_move() override {}
  virtual void on_end_move() override {}
  virtual Entity *copy() const override { return new SubEntity(); } 
};

int main(int argc, char *argv[])
{
	EntityList list = EntityList();
	list.add(SubEntity());
	return 0;
}
