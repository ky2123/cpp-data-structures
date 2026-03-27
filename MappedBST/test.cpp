#include "catch.hpp"
#include "map.hpp"

// try move-only types

TEST_CASE("default constructor") {
  cside::Map<int, int> map;

  REQUIRE(map.empty());
}
TEST_CASE("1 insert") { 
  cside::Map<int, int> map;

  map.insert(std::make_pair(10, 25));
  
  REQUIRE(map[10] == 25);
} 
TEST_CASE("3 insert") { 
  cside::Map<int, int> map;
  map.insert(std::make_pair(10, 25));
  map.insert(std::make_pair(12, 20));
  map.insert(std::make_pair(5, 100));

  REQUIRE(map[10] == 25);
  REQUIRE(map[12] == 20);
  REQUIRE(map[5] == 100);
  REQUIRE(!map.empty());
  REQUIRE(map.size() == 3);
} 
TEST_CASE("overwrite value with insert") { 
  cside::Map<int, int> map;
  map.insert(std::make_pair(10, 25));
  map.insert(std::make_pair(12, 20));
  map.insert(std::make_pair(5, 100));
  map.insert(std::make_pair(10, 5));

  REQUIRE(map[10] == 5);
  REQUIRE(map[12] == 20);
  REQUIRE(map[5] == 100);
  REQUIRE(!map.empty());
  REQUIRE(map.size() == 3);
}
TEST_CASE("operator[] inserts default value if key missing") {
  cside::Map<int, std::string> map;

  map[10] = "x"; 
  REQUIRE(map[10] == "x");
  REQUIRE(map.size() == 1);
}
TEST_CASE("operator[] overwrites existing key") {
    cside::Map<int,int> map;
    map.insert({1,10});

    map[1] = 99;
    REQUIRE(map[1] == 99);
}


TEST_CASE("at()") { 
  cside::Map<int,int> map;
  map.insert(std::make_pair(10, 25));
  map.insert(std::make_pair(12, 20));
  map.insert(std::make_pair(5, 100));

  REQUIRE(map.at(5) == 100);
  REQUIRE(map.at(12) == 20);
  REQUIRE(map.at(10) == 25);

  REQUIRE(map.at(5) != 20);
  REQUIRE(map.at(12) != 100);
  REQUIRE(map.at(10) != 20);
  REQUIRE(!map.empty());
  REQUIRE(map.size() == 3);
} 
TEST_CASE("at() throws on missing key") {
  cside::Map<int,int> map;
  map.insert({1, 10});

  REQUIRE_THROWS_AS(map.at(999), std::out_of_range);
}

TEST_CASE("erase()") { 
  cside::Map<int,int> map;
  map.insert(std::make_pair(10, 25));
  map.insert(std::make_pair(12, 20));
  map.insert(std::make_pair(5, 100));

  map.erase(12);

  REQUIRE(map[12] != 20);
  REQUIRE(map.at(5) == 100);
  REQUIRE(map.at(10) == 25);
  REQUIRE(map.size() == 3);
}
TEST_CASE("erase root when single element") {
  cside::Map<int,int> map;
  map.insert({5,10});

  map.erase(5);

  REQUIRE(map[5] != 10);
}
TEST_CASE("erase root with two children") {
  cside::Map<int,int> map;
  map.insert({5,10});
  map.insert({3,20});
  map.insert({7,30});

  map.erase(5);

  REQUIRE(map.size() == 3);
  REQUIRE(map.at(3) == 20);
  REQUIRE(map.at(7) == 30);
}

TEST_CASE("erase leaf node") {
  cside::Map<int,int> map;
  map.insert({5,10});
  map.insert({3,20}); 
  map.insert({7,30});

  map.erase(3);

  REQUIRE(map.size() == 3);  
  REQUIRE(map.at(5) == 10);
  REQUIRE(map.at(7) == 30);
}


TEST_CASE("initializaer_list") {

  cside::Map<int, std::string> map = { {1, "alfred"}, {2, "batman"}, {3, "robin"} };
  
  REQUIRE(map[1] == "alfred");
  REQUIRE(map[2] == "batman");
  REQUIRE(map[3] == "robin");
}
TEST_CASE("initializer_list empty") {
  cside::Map<int,int> map = {};
  REQUIRE(map.empty());
  REQUIRE(map.size() == 0);
}

TEST_CASE("copy ctor with 3 elements") {

  cside::Map<int, std::string> map = { {1, "alfred"}, {2, "batman"}, {3, "robin"} };

  cside::Map<int, std::string> map2(map);

  REQUIRE(map2[1] == "alfred");
  REQUIRE(map2[2] == "batman");
  REQUIRE(map2[3] == "robin");
}
TEST_CASE("copy ctor deep copy independence") {
  cside::Map<int,int> map;
  map.insert({1, 10});
  cside::Map<int,int> map2(map);

  map[1] = 99;

  REQUIRE(map2[1] == 10);
  REQUIRE(map[1] == 99);
}

TEST_CASE("move ctor with 3 elements") {

  cside::Map<int, std::string> map = { {1, "alfred"}, {2, "batman"}, {3, "robin"} };

  cside::Map<int, std::string> map2 = std::move(map);

  REQUIRE(map2[1] == "alfred");
  REQUIRE(map2[2] == "batman");
  REQUIRE(map2[3] == "robin");
  REQUIRE(map.empty());
  REQUIRE(map2.size() == 3);
}
TEST_CASE("move assignment with 3 elements") {
  cside::Map<int, std::string> map = { {1, "alfred"}, {2, "batman"}, {3, "robin"} };
  cside::Map<int, std::string> map2 = { {1, "jj"}, {2, "spiderman"}, {3, "peter"} };

  map2 = std::move(map);

  REQUIRE(map2[1] == "alfred");
  REQUIRE(map2[2] == "batman");
  REQUIRE(map2[3] == "robin");
  REQUIRE(map.empty());
}
TEST_CASE("copy assignment with 3 elements") {
  cside::Map<int, std::string> map = { {1, "alfred"}, {2, "batman"}, {3, "robin"} };
  cside::Map<int, std::string> map2 = { {1, "jj"}, {2, "spiderman"}, {3, "peter"} };

  map2 = map;

  REQUIRE(map2[1] == "alfred");
  REQUIRE(map2[2] == "batman");
  REQUIRE(map2[3] == "robin");
  REQUIRE(map[1] == "alfred");
  REQUIRE(map[2] == "batman");
  REQUIRE(map[3] == "robin");
  REQUIRE(map.size() == 3);
  REQUIRE(map2.size() == 3);

  REQUIRE(!map.empty());
}

TEST_CASE("emplace()" ) {
  cside::Map<int, std::string> map = { {1, "alfred"}, {2, "batman"}, {3, "robin"} };

  map.emplace(4, "gordon");

  REQUIRE(map[4] == "gordon");
}

TEST_CASE("BST iterator") {
  cside::Map<int, std::string> map = { {1, "alfred"}, {2, "batman"}, {3, "robin"} };
  
  SECTION("Iterator in-order with ++") {
    std::vector<int> keys;
    std::vector<std::string> values;
    for (auto it = map.begin(); it != map.end(); ++it) {
      keys.push_back(it->first);
      values.push_back(it->second);
    }
    REQUIRE(keys == std::vector<int>{1,2,3});
    REQUIRE(values == std::vector<std::string>{"alfred", "batman", "robin"});
  }
}
TEST_CASE("iterator on empty map") {
  cside::Map<int,int> map;

  auto it = map.begin();
  auto end = map.end();

  REQUIRE(it == end);
}
TEST_CASE("iterator in-order with --") {
    cside::Map<int,int> map;
    map.insert({1,10});
    map.insert({2,20});
    map.insert({3,30});

    auto it = map.begin();
    while (true) {
        auto next = it;
        ++next;
        if (next == map.end()) break;
        it = next;
    }

    std::vector<int> keys;
    while (true) {
        keys.push_back(it->first);
        if (it == map.begin()) break;
        --it;
    }

    REQUIRE(keys == std::vector<int>{3,2,1});
}
TEST_CASE("Iterator ++ past last element goes to end()") {
    cside::Map<int,int> map;
    map.insert({1,10}); 
    map.insert({2,20}); 
    map.insert({3,30}); 

    auto it = map.begin();
    ++it; ++it; ++it;  
    REQUIRE(it == map.end());
}
TEST_CASE("Iterator copy construction") {
    cside::Map<int,int> map = {{1,10},{2,20},{3,30}};

    auto it = map.begin();
    auto it2 = it;     
    REQUIRE(it2 == it);
    REQUIRE(it2->second == 10);

    ++it;
    REQUIRE(it2 != it);
}
TEST_CASE("Iterator assignment") {
    cside::Map<int,int> map = {{1,10},{2,20},{3,30}};

    auto it = map.begin();
    auto it2 = map.end();

    it2 = it;
    REQUIRE(it2 == it);
}



TEST_CASE("Equals") {
  cside::Map<int, std::string> map = { {1, "alfred"}, {2, "batman"}, {3, "robin"} };
  
  cside::Map<int, std::string> map2 = { {1, "alfred"}, {2, "batman"}, {3, "robin"} };
  
  REQUIRE(map == map2);
}
TEST_CASE("Not equals") {
  cside::Map<int, std::string> map = { {1, "alfred"}, {2, "batman"}, {3, "robin"} };

  cside::Map<int, std::string> map2 = { {1, "jj"}, {2, "spiderman"}, {3, "peter"} };

  REQUIRE(map != map2);  
}
struct MoveOnly {
  int x;
  MoveOnly(int v) : x(v) {}
  MoveOnly(const MoveOnly&) = delete;
  MoveOnly& operator=(const MoveOnly&) = delete;
  MoveOnly(MoveOnly&& o) noexcept : x(o.x) { o.x = -1; }
  MoveOnly& operator=(MoveOnly&& o) noexcept {
    x = o.x; o.x = -1;
    return *this;
  }
};

TEST_CASE("MoveOnly, with emplace") {
  cside::Map<int, MoveOnly> map;
  map.emplace(1, MoveOnly{10});
  map.emplace(2, MoveOnly{20});

  REQUIRE(map.at(1).x == 10);
  REQUIRE(map.at(2).x == 20);
}

TEST_CASE("MoveOnly, insertion") {
    cside::Map<int, MoveOnly> map;

    map.insert({1, MoveOnly{10}});
    map.insert({2, MoveOnly{20}});

    REQUIRE(map.at(1).x == 10);
    REQUIRE(map.at(2).x == 20);
    REQUIRE(map.size() == 2);
}
TEST_CASE("MoveOnly, overwrite value with move assignment") {
    cside::Map<int, MoveOnly> map;

    map.insert({1, MoveOnly{10}});
    REQUIRE(map.at(1).x == 10);

    map.insert({1, MoveOnly{99}});
    REQUIRE(map.at(1).x == 99);
}
TEST_CASE("MoveOnly, move ctor") {
    cside::Map<int, MoveOnly> map1;
    map1.insert({1, MoveOnly{10}});
    map1.insert({2, MoveOnly{20}});

    cside::Map<int, MoveOnly> map2(std::move(map1));

    REQUIRE(map2.at(1).x == 10);
    REQUIRE(map2.at(2).x == 20);
}


