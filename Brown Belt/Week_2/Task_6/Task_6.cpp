/*
	Из лекций мы узнали, что this всегда указывает на текущий объект класса,
	а также, что он является неявным параметром всех его методов.
	Кроме того, мы только что познакомились с понятиями статического и динамического типов ссылки (или указателя).
	В этой задаче мы объединим эти знания, чтобы реализовать так называемую двойную диспетчеризацию — мы напишем функцию,
	которая ведёт себя по-разному в зависимости о динамических типов двух объектов, которые в неё переданы.
	
	Представим, что мы пишем движок для классической компьютерной стратегии:
	игроки строят города, формируют армию, а потом сражаются друг с другом.
	
	В нашей игре есть несколько объектов:	
	*	юниты — это солдаты, рабочие, кавалеристы и т.д.
	*	здания — фабрики, заводы, казармы и т.д.
	*	башни и стены — защитные сооружения для обороны своего города

	Мы работаем над функциональностью размещения новых объектов на игровой карте.
	Допустим, мы хотим построить новое здание.
	Мы начинаем искать на карте место, где его можно разместить,
	а графический интерфейс игры нам в этом помогает.
	Здание можно построить в том месте карты, где нет других объектов.
	Если в текущей позиции здание пересекается с каким-то из объектов,
	то интерфейс рисует наше здание красным цветом, сообщая, что здесь его построить нельзя.
	
	При этом юниты представляются точкой на плоскости, здания — прямоугольником, башни — кругом, а стены — отрезком.
	Кроме того, для каждого игрового объекта в нашем движке заведён отдельный класс,
	который наследуется от абстрактного класса GameObject.

	Наша задача — реализовать функцию bool Collide(const GameObject& first, const GameObject& second),
	которая проверяет пересекаются ли два игровых объекта, то есть имеют ли они хотя бы одну общую точку.
	
	Вам даны:	
	*	файл game_object.h, содержащий интерфейс GameObject и объявление функции Collide
	*	файлы geo2d.h/cpp, содержащие библиотеку для работы с геометрическими фигурами на плоскости;
		библиотека состоит из классов Point, Rectangle, Circle и Segment
		и набора функций Collide, которые умеют определять пересечение для каждой пары фигур
		(занимательный факт — все функции реализованы в целых числах, без применения вычислений в типе double)
	*	файл collide.cpp, содержащий заготовку решения, а также юнит-тест, эмулирующий размещение нового объекта на игровой карте
	
	Пришлите в тестирующую систему файл collide.cpp, который будет:	
	*	подключать game_object.h
	*	содержать реализации классов Unit, Building, Tower и Fence
		(все они должны наследоваться от GameObject и реализовывать его интерфейс)
	*	содержать реализацию функции bool Collide(const GameObject& first, const GameObject& second),
		которая возвращает true, если объекты first и second имеют на плоскости хотя бы одну общую точку,
		и false в противном случае.

	Замечание
	Один из способов реализовать функцию Collide — использовать dynamic_cast.
	Мы не освещали его в лекциях.
	Кроме того, этот способ приводит к появлению развесистого кода, подверженного возникновению ошибок.
	Мы хотим, чтобы в этой задаче вы хорошенько разобрались с понятиями статического и динамического типа,
	а также поработали с указателем this.
	Поэтому мы будем компилировать ваши решения с флагом -fno-rtti,
	который будет приводить к ошибкам компиляции в случае использования dynamic_cast.
*/
#include "geo2d.h"
#include "game_object.h"

#include "test_runner.h"

#include <vector>
#include <memory>

template <typename T>
struct Collider : public GameObject
{
	bool Collide(const GameObject& that) const final
	{
		return that.CollideWith(static_cast<const T&>(*this));
	}
};

// Определите классы Unit, Building, Tower и Fence так, чтобы они наследовались от
// GameObject и реализовывали его интерфейс.

class Unit : public Collider<Unit>
{
public:
	explicit Unit(geo2d::Point position)
		: position_(position)
	{
	}

	geo2d::Point GetPosition() const { return position_; }

	bool CollideWith(const Unit& that) const override;
	bool CollideWith(const Building& that) const override;
	bool CollideWith(const Tower& that) const override;
	bool CollideWith(const Fence& that) const override;

private:
	geo2d::Point position_;
};

class Building : public Collider<Building>
{
public:
	explicit Building(geo2d::Rectangle geometry)
		: geometry_(geometry)
	{
	}

	geo2d::Rectangle GetGeometry() const { return geometry_; }

	bool CollideWith(const Unit& that) const override;
	bool CollideWith(const Building& that) const override;
	bool CollideWith(const Tower& that) const override;
	bool CollideWith(const Fence& that) const override;

private:
	geo2d::Rectangle geometry_;
};

class Tower : public Collider<Tower>
{
public:
	explicit Tower(geo2d::Circle geometry)
		: geometry_(geometry)
	{
	}

	geo2d::Circle GetGeometry() const { return geometry_; }

	bool CollideWith(const Unit& that) const override;
	bool CollideWith(const Building& that) const override;
	bool CollideWith(const Tower& that) const override;
	bool CollideWith(const Fence& that) const override;	

private:
	geo2d::Circle geometry_;
};

class Fence : public Collider<Fence>
{
public:
	explicit Fence(geo2d::Segment geometry)
		:geometry_(geometry)
	{
	}

	geo2d::Segment GetGeometry() const { return geometry_; }

	bool CollideWith(const Unit& that) const override;
	bool CollideWith(const Building& that) const override;
	bool CollideWith(const Tower& that) const override;
	bool CollideWith(const Fence& that) const override;

private:
	geo2d::Segment geometry_;
};

// Реализуйте функцию Collide из файла GameObject.h

bool Collide(const GameObject& first, const GameObject& second)
{
	return first.Collide(second);
}

// UNIT METHODS
bool Unit::CollideWith(const Unit& that) const
{
	return geo2d::Collide(position_, that.GetPosition());
}
bool Unit::CollideWith(const Building& that) const
{
	return geo2d::Collide(position_, that.GetGeometry());
}
bool Unit::CollideWith(const Tower& that) const
{
	return geo2d::Collide(position_, that.GetGeometry());
}
bool Unit::CollideWith(const Fence& that) const
{
	return geo2d::Collide(position_, that.GetGeometry());
}

#define MACROS_COLLIDER_WITH_GEOMETRY(lhs, rhs)				\
bool lhs::CollideWith(const rhs& that) const				\
{															\
	return geo2d::Collide(geometry_, that.GetGeometry());	\
}

// BUILDING METHODS
bool Building::CollideWith(const Unit& that) const
{
	return geo2d::Collide(geometry_, that.GetPosition());
}
MACROS_COLLIDER_WITH_GEOMETRY(Building, Building)
MACROS_COLLIDER_WITH_GEOMETRY(Building, Tower)
MACROS_COLLIDER_WITH_GEOMETRY(Building, Fence)

// TOWER METHODS
bool Tower::CollideWith(const Unit& that) const
{
	return geo2d::Collide(geometry_, that.GetPosition());
}
MACROS_COLLIDER_WITH_GEOMETRY(Tower, Building)
MACROS_COLLIDER_WITH_GEOMETRY(Tower, Tower)
MACROS_COLLIDER_WITH_GEOMETRY(Tower, Fence)

// FENCE METHODS
bool Fence::CollideWith(const Unit& that) const
{
	return geo2d::Collide(geometry_, that.GetPosition());
}
MACROS_COLLIDER_WITH_GEOMETRY(Fence, Building)
MACROS_COLLIDER_WITH_GEOMETRY(Fence, Tower)
MACROS_COLLIDER_WITH_GEOMETRY(Fence, Fence)

void TestAddingNewObjectOnMap()
{
	// Юнит-тест моделирует ситуацию, когда на игровой карте уже есть какие-то объекты,
	// и мы хотим добавить на неё новый, например, построить новое здание или башню.
	// Мы можем его добавить, только если он не пересекается ни с одним из существующих.
	using namespace geo2d;

	const std::vector<std::shared_ptr<GameObject>> game_map =
	{
	  std::make_shared<Unit>(Point{3, 3}),
	  std::make_shared<Unit>(Point{5, 5}),
	  std::make_shared<Unit>(Point{3, 7}),
	  std::make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
	  std::make_shared<Tower>(Circle{Point{9, 4}, 1}),
	  std::make_shared<Tower>(Circle{Point{10, 7}, 1}),
	  std::make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
	};

	for (size_t i = 0; i < game_map.size(); ++i)
	{
		Assert(
			Collide(*game_map[i], *game_map[i]),
			"An object doesn't collide with itself: " + std::to_string(i)
		);

		for (size_t j = 0; j < i; ++j)
		{
			Assert(
				!Collide(*game_map[i], *game_map[j]),
				"Unexpected collision found " + std::to_string(i) + ' ' + std::to_string(j)
			);
		}
	}

	auto new_warehouse = std::make_shared<Building>(Rectangle{ {4, 3}, {9, 6} });
	ASSERT(!Collide(*new_warehouse, *game_map[0]));
	ASSERT(Collide(*new_warehouse, *game_map[1]));
	ASSERT(!Collide(*new_warehouse, *game_map[2]));
	ASSERT(Collide(*new_warehouse, *game_map[3]));
	ASSERT(Collide(*new_warehouse, *game_map[4]));
	ASSERT(!Collide(*new_warehouse, *game_map[5]));
	ASSERT(!Collide(*new_warehouse, *game_map[6]));

	auto new_defense_tower = std::make_shared<Tower>(Circle{ {8, 2}, 2 });
	ASSERT(!Collide(*new_defense_tower, *game_map[0]));
	ASSERT(!Collide(*new_defense_tower, *game_map[1]));
	ASSERT(!Collide(*new_defense_tower, *game_map[2]));
	ASSERT(Collide(*new_defense_tower, *game_map[3]));
	ASSERT(Collide(*new_defense_tower, *game_map[4]));
	ASSERT(!Collide(*new_defense_tower, *game_map[5]));
	ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestAddingNewObjectOnMap);
	return 0;
}
