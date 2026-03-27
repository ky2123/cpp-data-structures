#include "linkedlist.h"
#include "catch.hpp"
#include <sstream>
TEST_CASE("No arg constructor test") {
  cside::LinkedList list;
  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());
  REQUIRE(!list.contains("0"));
  REQUIRE_THROWS(list.at(0));
}
TEST_CASE("Initializer_list constructor") {
  cside::LinkedList list{"monkey", "ape", "gorrilla"};

  REQUIRE(list.size() == 3);
  REQUIRE(!list.empty());
  REQUIRE(list.contains("monkey"));
}
TEST_CASE("push_back with one string") {
  cside::LinkedList list;

  list.push_back("kyd");

  REQUIRE(list[0] == "kyd");
  REQUIRE(list.size() == 1);
  REQUIRE(list.front() == list.back());
  REQUIRE(!list.empty());
  REQUIRE(list.contains("kyd"));
}
TEST_CASE("push_back with two strings") {
  cside::LinkedList list;

  list.push_back("abc");
  list.push_back("def");
 
  REQUIRE(list[0] == "abc");
  REQUIRE(list[1] == "def");
  REQUIRE(list.size() == 2);
  REQUIRE(list.front() == "abc");
  REQUIRE(list.back() == "def");
  REQUIRE(!list.empty());
}
TEST_CASE("push_back with three strings") {
  cside::LinkedList list;

  list.push_back("gum");
  list.push_back("monster");
  list.push_back("bread");

  REQUIRE(list.size() == 3);
  REQUIRE(!list.empty());
  REQUIRE(list[0] == "gum");
  REQUIRE(list[1] == "monster");
  REQUIRE(list[2] == "bread");
  REQUIRE(list.front() == "gum");
  REQUIRE(list.back() == "bread");
}
TEST_CASE("operator[] with a 1 element list") {
  cside::LinkedList list;

  list.push_back("kyd");

  REQUIRE(list[0] == "kyd");
}

TEST_CASE("operator[] with a 2 element list") {
  cside::LinkedList list;

  list.push_back("kyd");
  list.push_back("car");

  REQUIRE(list[0] == "kyd");
  REQUIRE(list[1] == "car");
  REQUIRE(list[1] != "kyd");
  REQUIRE(list[0] != "car");
}

TEST_CASE("operator[] with a 3 element list") {
  cside::LinkedList list;

  list.push_back("gum");
  list.push_back("monster");
  list.push_back("bread");

  REQUIRE(list[2] == "bread");
  REQUIRE(list[1] == "monster");
  REQUIRE(list[0] == "gum");
  
}
TEST_CASE("pop_back() with a 1 element list") {
  cside::LinkedList list;

  list.push_back("link");
  list.pop_back();

  REQUIRE(list.size() == 0);
  REQUIRE(list.front_node() == nullptr);
  REQUIRE(list.back_node() == nullptr);
  REQUIRE(list.empty());
  REQUIRE(!list.contains("link"));
}
TEST_CASE("pop_back() with a 2 element list") {
  cside::LinkedList list;

  list.push_back("link");
  list.push_back("zelda");
  list.pop_back();

  REQUIRE(list.size() == 1);
  REQUIRE(list.back() == list.front());
  REQUIRE(!list.empty());
  REQUIRE(list.contains("link"));
  REQUIRE(!list.contains("zelda"));
  REQUIRE(list.front() == "link");
  REQUIRE(list.back() == "link");
}
TEST_CASE("pop_back() with a 3 element list") {
  cside::LinkedList list;

  list.push_back("link");
  list.push_back("zelda");
  list.push_back("mark");
  list.pop_back();

  REQUIRE(list.size() == 2);
  REQUIRE(list.back_node() != nullptr ); 
  REQUIRE(list[0] == "link"); 
  REQUIRE(list[1] == "zelda"); 
  REQUIRE(!list.empty());
  REQUIRE(!list.contains("mark"));
}
TEST_CASE("operator ==") {
  cside::LinkedList list;
  cside::LinkedList list2;
  list.push_back("mark");
  list2.push_back("mark");

  REQUIRE(list == list2);
}
TEST_CASE("operater== with 2 element lists") {
  cside::LinkedList list;
  cside::LinkedList list2;

  list.push_back("link");
  list2.push_back("link");
  list.push_back("zelda");
  list2.push_back("zelda");

  REQUIRE(list == list2);
}
TEST_CASE("operater== with 3 element lists") {
  cside::LinkedList list;
  cside::LinkedList list2;

  list.push_back("link");
  list2.push_back("link");
  list.push_back("zelda");
  list2.push_back("zelda");
  list.push_back("mario");
  list2.push_back("mario");

  REQUIRE(list == list2);
}
TEST_CASE("push_front with one string") {
  cside::LinkedList list;

  list.push_front("kyd");

  REQUIRE(list[0] == "kyd");
  REQUIRE(list.size() == 1);
  REQUIRE(list.front() == list.back());
  REQUIRE(!list.empty());
  REQUIRE(list.contains("kyd"));
}
TEST_CASE("push_front with two strings") {
  cside::LinkedList list;

  list.push_front("abc");
  list.push_front("def");
 
  REQUIRE(list[1] == "abc");
  REQUIRE(list[0] == "def");
  REQUIRE(list.size() == 2);
  REQUIRE(list.back() == "abc");
  REQUIRE(list.front() == "def");
  REQUIRE(!list.empty());
}
TEST_CASE("push_front with three strings") {
  cside::LinkedList list;

  list.push_front("gum");
  list.push_front("monster");
  list.push_front("bread");

  REQUIRE(list.size() == 3);
  REQUIRE(!list.empty());
  REQUIRE(list[2] == "gum");
  REQUIRE(list[1] == "monster");
  REQUIRE(list[0] == "bread");
  REQUIRE(list.back() == "gum");
  REQUIRE(list.front() == "bread");
}
TEST_CASE("pop_front() with a 1 element list") {
  cside::LinkedList list;

  list.push_back("link");
  list.pop_front();

  REQUIRE(list.size() == 0);
  REQUIRE(list.front_node() == nullptr);
  REQUIRE(list.back_node() == nullptr);
  REQUIRE(list.empty());
  REQUIRE(!list.contains("link"));
}
TEST_CASE("pop_front() with a 2 element list") {
  cside::LinkedList list;

  list.push_back("link");
  list.push_back("zelda");
  list.pop_front();

  REQUIRE(list.size() == 1);
  REQUIRE(list.back() == list.front());
  REQUIRE(!list.empty());
  REQUIRE(!list.contains("link"));
  REQUIRE(list.contains("zelda"));
  REQUIRE(list.front() == "zelda");
  REQUIRE(list.back() == "zelda");
}
TEST_CASE("pop_front() with a 3 element list") {
  cside::LinkedList list;

  list.push_back("link");
  list.push_back("zelda");
  list.push_back("mark");
  list.pop_front();

  REQUIRE(list.size() == 2);
  REQUIRE(list.back_node() != nullptr ); 
  REQUIRE(list[0] == "zelda"); 
  REQUIRE(list[1] == "mark"); 
  REQUIRE(!list.empty());
  REQUIRE(!list.contains("link"));
}
TEST_CASE("operator !=") {
  cside::LinkedList list;
  cside::LinkedList list2;
  list.push_back("mark");
  list2.push_back("bark");

  REQUIRE(list != list2);
}
TEST_CASE("operater!= with 2 element lists") {
  cside::LinkedList list;
  cside::LinkedList list2;

  list.push_back("link");
  list2.push_back("drink");
  list.push_back("zelda");
  list2.push_back("zelle");

  REQUIRE(list != list2);
}
TEST_CASE("operater!= with 3 element lists") {
  cside::LinkedList list;
  cside::LinkedList list2;

  list.push_back("link");
  list2.push_back("link");
  list.push_back("zelda");
  list2.push_back("zelda");
  list.push_back("mario");
  list2.push_back("luigi");

  REQUIRE(list != list2);
}
TEST_CASE("copy ctor empty list") {
  cside::LinkedList list;

  cside::LinkedList list2(list);
  
  REQUIRE(list2.empty());
  REQUIRE(list2.size() == 0);
}
TEST_CASE("copy ctor 1 elemet list") {
  cside::LinkedList list;
  list.push_front("hulk");

  cside::LinkedList list2(list);
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 1);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list[0] == list2[0]);
  REQUIRE(list.front_node() != list2.front_node());
}
TEST_CASE("copy ctor 2 elemet list") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");

  cside::LinkedList list2(list);
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 2);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list2.contains("spiderman"));
  REQUIRE(list[0] == list2[0]);
  REQUIRE(list[1] == list2[1]);
  REQUIRE(list.front_node() != list2.front_node());
  REQUIRE(list.back_node() != list2.back_node());
}
TEST_CASE("copy ctor 3 elemet list") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");
  list.push_front("venom");

  cside::LinkedList list2(list);
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 3);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list2.contains("spiderman"));
  REQUIRE(list2.contains("venom"));
  REQUIRE(list[0] == list2[0]);
  REQUIRE(list[1] == list2[1]);
  REQUIRE(list[2] == list2[2]);
  REQUIRE(list.front_node() != list2.front_node());
  REQUIRE(list.back_node() != list2.back_node());
}
TEST_CASE("copy ctor push_back") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");

  cside::LinkedList list2(list);
  list2.push_back("antivenom");
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 3);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list2.contains("spiderman"));
  REQUIRE(list2.contains("antivenom"));
  REQUIRE(list[0] == list2[0]);
  REQUIRE(list[1] == list2[1]);
  REQUIRE(list.front_node() != list2.front_node());
  REQUIRE(list.back_node() != list2.back_node());
}
TEST_CASE("at() with a 1 element list") {
  cside::LinkedList list;

  list.push_back("kyd");

  REQUIRE(list.at(0) == "kyd");
}

TEST_CASE("at() with a 2 element list") {
  cside::LinkedList list;

  list.push_back("kyd");
  list.push_back("car");

  REQUIRE(list.at(0) == "kyd");
  REQUIRE(list.at(1) == "car");
  REQUIRE(list.at(1) != "kyd");
  REQUIRE(list.at(0) != "car");
}

TEST_CASE("at() with a 3 element list") {
  cside::LinkedList list;

  list.push_back("gum");
  list.push_back("monster");
  list.push_back("bread");

  REQUIRE(list.at(2) == "bread");
  REQUIRE(list.at(1) == "monster");
  REQUIRE(list.at(0) == "gum");
  
}
TEST_CASE("at() OOB by 1") {
  cside::LinkedList list;

  list.push_back("today");
  list.push_back("tomorrow");

  REQUIRE_THROWS(list.at(3));
}
TEST_CASE("at() OOB by several elements") {
  cside::LinkedList list;

  list.push_back("today");
  list.push_back("tomorrow");

  REQUIRE_THROWS(list.at(list.size() + 5));
}
TEST_CASE("insert into empty list") { 
  cside::LinkedList list;

  list.insert(0, "kyd");

  REQUIRE(list[0] == "kyd");
  REQUIRE(list.size() == 1);
  REQUIRE(list.front() == list.back());
  REQUIRE(!list.empty());
  REQUIRE(list.contains("kyd"));
}
TEST_CASE("insert into 2 element list") {
  cside::LinkedList list;
  list.push_back("today");
  list.push_back("tomorrow");

  list.insert(0,"abc");
  list.insert(3,"def");
 
  REQUIRE(list[0] == "abc");
  REQUIRE(list[3] == "def");
  REQUIRE(list.size() == 4);
  REQUIRE(list.front() == "abc");
  REQUIRE(list.back() == "def");
  REQUIRE(!list.empty());
}
TEST_CASE("insert into 3 element list") {
  cside::LinkedList list;
  list.push_back("gum");
  list.push_back("monster");
  list.push_back("bread");

  list.insert(0,"abc");
  list.insert(1,"def");

  REQUIRE(list.size() == 5);
  REQUIRE(!list.empty());
  REQUIRE(list[0] == "abc");
  REQUIRE(list[1] == "def");
  REQUIRE(list[2] == "gum");
  REQUIRE(list.front() == "abc");
  REQUIRE(list.back() == "bread");
}
TEST_CASE("copy ctor 3 elemet list with insert") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");
  list.push_front("venom");

  cside::LinkedList list2(list);
  list2.insert(2,"carnage");
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 4);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list2.contains("spiderman"));
  REQUIRE(list2.contains("venom"));
  REQUIRE(list2.contains("carnage"));
  REQUIRE(list[0] == list2[0]);
  REQUIRE(list[1] == list2[1]);
  REQUIRE(list[2] != list2[2]);
  REQUIRE(list.front_node() != list2.front_node());
  REQUIRE(list.back_node() != list2.back_node());
}
TEST_CASE("remove the only element") {
  cside::LinkedList list;
  list.push_front("hulk");

  list.remove(0);

  REQUIRE(list.empty());
  REQUIRE(list.size() == 0);
  REQUIRE(!list.contains("hulk"));
}
TEST_CASE("remove head from two element list") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("ironman");

  list.remove(0);

  REQUIRE(!list.empty());
  REQUIRE(list.size() == 1);
  REQUIRE(!list.contains("ironman"));
  REQUIRE(list.contains("hulk"));
  REQUIRE(list.front() == "hulk");
}
TEST_CASE("remove tail from two element list") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("ironman");

  list.remove(1);

  REQUIRE(!list.empty());
  REQUIRE(list.size() == 1);
  REQUIRE(!list.contains("hulk"));
  REQUIRE(list.contains("ironman"));
  REQUIRE(list.front() == "ironman");
}
TEST_CASE("remove second element from three element list") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("ironman");
  list.push_front("hawkeye");

  list.remove(1);

  REQUIRE(!list.empty());
  REQUIRE(list.size() == 2);
  REQUIRE(!list.contains("ironman"));
  REQUIRE(list.front() == "hawkeye");
  REQUIRE(list.back() == "hulk");
}
TEST_CASE("reverse() with 0") {
  cside::LinkedList list;

  list.reverse();

  REQUIRE(list.empty());
  REQUIRE(list.size() == 0);
}

TEST_CASE("reverse() with 1") {
  cside::LinkedList list;
  list.push_back("gum");

  list.reverse();

  REQUIRE(list.at(0) == "gum");
  
}

TEST_CASE("reverse() with 2") {
  cside::LinkedList list;
  list.push_back("gum");
  list.push_back("monster");

  list.reverse();

  REQUIRE(list.at(1) == "gum");
  REQUIRE(list.at(0) == "monster");
  
}

TEST_CASE("reverse()") {
  cside::LinkedList list;
  list.push_back("gum");
  list.push_back("monster");
  list.push_back("bread");

  list.reverse();

  REQUIRE(list.at(0) == "bread");
  REQUIRE(list.at(1) == "monster");
  REQUIRE(list.at(2) == "gum");
  
}
TEST_CASE("move ctor with empty list"){
  cside::LinkedList list;

  cside::LinkedList list2 = std::move(list);

  REQUIRE(list2.size() == 0);
  REQUIRE(list2.empty());
}
TEST_CASE("move ctor with a list"){
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");
  list.push_front("venom");


  cside::LinkedList list2 = std::move(list);

  REQUIRE(list2.size() == 3);
  REQUIRE(!list2.empty());
  REQUIRE(list2.front() == "venom");
  REQUIRE(list2.back() == "hulk");
}
TEST_CASE("copy assignment empty list") {
  cside::LinkedList list;

  cside::LinkedList list2;
  list2 = list;
  
  REQUIRE(list2.empty());
  REQUIRE(list2.size() == 0);
}
TEST_CASE("copy assignment 1 element list") {
  cside::LinkedList list;
  list.push_front("hulk");

  cside::LinkedList list2;
  list2 = list;
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 1);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list[0] == list2[0]);
  REQUIRE(list.front_node() != list2.front_node());
}
TEST_CASE("copy assignment 2 element list") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");

  cside::LinkedList list2;
  list2 = list;
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 2);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list2.contains("spiderman"));
  REQUIRE(list[0] == list2[0]);
  REQUIRE(list[1] == list2[1]);
  REQUIRE(list.front_node() != list2.front_node());
  REQUIRE(list.back_node() != list2.back_node());
}
TEST_CASE("copy assignment 3 element list") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");
  list.push_front("venom");

  cside::LinkedList list2;
  list2 = list;
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 3);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list2.contains("spiderman"));
  REQUIRE(list2.contains("venom"));
  REQUIRE(list[0] == list2[0]);
  REQUIRE(list[1] == list2[1]);
  REQUIRE(list[2] == list2[2]);
  REQUIRE(list.front_node() != list2.front_node());
  REQUIRE(list.back_node() != list2.back_node());
}
TEST_CASE("copy assignment push_back") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");

  cside::LinkedList list2;
  list2 = list;
  list2.push_back("antivenom");
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 3);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list2.contains("spiderman"));
  REQUIRE(list2.contains("antivenom"));
  REQUIRE(list[0] == list2[0]);
  REQUIRE(list[1] == list2[1]);
  REQUIRE(list.front_node() != list2.front_node());
  REQUIRE(list.back_node() != list2.back_node());
}
TEST_CASE("move assignment empty list") {
  cside::LinkedList list;

  cside::LinkedList list2;
  list2 = std::move(list);
  
  REQUIRE(list2.empty());
  REQUIRE(list2.size() == 0);
}
TEST_CASE("move assignment 1 element list") {
  cside::LinkedList list;
  list.push_front("hulk");

  cside::LinkedList list2;
  list2 = std::move(list);
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 1);
  REQUIRE(list2[0] == "hulk");
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list.front_node() != list2.front_node());
}
TEST_CASE("move assignment 2 element list") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");

  cside::LinkedList list2;
  list2 = std::move(list);
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 2);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list2.contains("spiderman"));
  REQUIRE(list2[0] == "spiderman");
  REQUIRE(list2[1] == "hulk");
  REQUIRE(list.front_node() != list2.front_node());
  REQUIRE(list.back_node() != list2.back_node());
}
TEST_CASE("move assignment 3 element list") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");
  list.push_front("venom");

  cside::LinkedList list2;
  list2 = std::move(list);
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 3);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list2.contains("spiderman"));
  REQUIRE(list2.contains("venom"));
  REQUIRE(list2[0] == "venom");
  REQUIRE(list2[1] == "spiderman");
  REQUIRE(list2[2] == "hulk");
  REQUIRE(list.front_node() != list2.front_node());
  REQUIRE(list.back_node() != list2.back_node());
}
TEST_CASE("move assignment push_back") {
  cside::LinkedList list;
  list.push_front("hulk");
  list.push_front("spiderman");

  cside::LinkedList list2;
  list2 = std::move(list);
  list2.push_back("antivenom");
  
  REQUIRE(!list2.empty());
  REQUIRE(list2.size() == 3);
  REQUIRE(list2.contains("hulk"));
  REQUIRE(list2.contains("spiderman"));
  REQUIRE(list2.contains("antivenom"));
  REQUIRE(list.front_node() != list2.front_node());
  REQUIRE(list.back_node() != list2.back_node());
}
TEST_CASE("delete 1 element list with iterator") {
  cside::LinkedList list;

  list.push_back("gum");
  list.clear();

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());
}

TEST_CASE("delete 2 element list with iterator") {
  cside::LinkedList list;

  list.push_back("gum");
  list.push_back("monster");
  list.clear();

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());
}

TEST_CASE("delete 3 element list with iterator") {
  cside::LinkedList list;

  list.push_back("gum");
  list.push_back("monster");
  list.push_back("bread");
  list.clear();

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());
}

