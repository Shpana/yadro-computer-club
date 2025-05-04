#ifndef YADRO_COMPUTER_CLUB_PROCESSOR_HPP
#define YADRO_COMPUTER_CLUB_PROCESSOR_HPP

#include "events/event_handler.hpp"

#include <iostream>
#include <memory>

class Processor {
public:
  Processor(const Context& context, std::istream& input, std::ostream& output);
  void run();

  template<class TEvent>
  void process_event(const TEvent& event);

private:
  void _process_events();
  void _process_event_line(const std::string& line);

private:
  std::istream& _input;
  std::ostream& _output;

  Context _context;
  std::shared_ptr<Accountant> _accountant;
  std::shared_ptr<ClientRegistry> _client_registry;
  std::shared_ptr<TableRegistry> _table_registry;
  std::shared_ptr<EventHandler> _handler;
};

#endif// YADRO_COMPUTER_CLUB_PROCESSOR_HPP
