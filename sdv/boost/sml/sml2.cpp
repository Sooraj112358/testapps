#include "sml.hpp"
#include <iostream>

struct state_machine {
public:
  // Transition table
  auto operator() () const {
    using namespace boost::sml;
    return make_transition_table(
      *"state_a"_s + event<event_1> = "state_b"_s,
      "state_a"_s + event<event_2> = "state_b"_s,
      "state_a"_s + event<event_3> = "state_b"_s,
      "state_b"_s + on_entry<event_1> / ActionOne{},
      "state_b"_s + on_entry<event_1> / [](){ std::cout << "LamdaTransition due to event_1" << std::endl;},
	  "state_b"_s + on_entry<event_3> / ActionOne{},
      "state_b"_s + on_entry<_> / ActionTwo{}
    );
  }

  // Events
  struct event_1 {};
  struct event_2 {};
  struct event_3 {};

  // Actions
  struct ActionOne {
    void operator()() {
      std::cout << "Transition due to event_1" << std::endl;
    };
  };

  struct ActionTwo {
    void operator()() {
      std::cout << "Transition due to event_2" << std::endl;
    };
  };
};

int main () {
  boost::sml::sm<state_machine> fsm_one, fsm_two;

  // Will invoke ActionOne
  fsm_one.process_event(state_machine::event_1{});
  //fsm_one.process_event(state_machine::event_2{});
  fsm_one.process_event(state_machine::event_3{});
 
  // Will invoke ActionTwo
  //fsm_two.process_event(state_machine::event_1{});
  fsm_two.process_event(state_machine::event_2{});

  return 0;
}