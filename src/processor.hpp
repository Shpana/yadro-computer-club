#ifndef YADRO_COMPUTER_CLUB_PROCESSOR_HPP
#define YADRO_COMPUTER_CLUB_PROCESSOR_HPP

#include "events/event_handler.hpp"

#include <memory>
#include <iostream>

class Processor {
public:
  Processor(const Context& context, std::istream& input, std::ostream& output);
  void run();

private:
  void _process_events();
  void _process_event_line(const std::string& line);
  template<class TEvent>
  void _process_event(const TEvent& event);

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
