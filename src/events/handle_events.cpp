#include "events.hpp"

#include "context.hpp"

namespace ComputerClub::Events {
  auto HandleClientArrivedEvent(Context& context,
                                const ClientArrivedEvent& event)
      -> void {
    const auto& client_name = event.client_name;

    if (context.client_registry()->HasClient(client_name)) {
      auto error = ErrorEvent{"YouShallNotPass", event.created_at};
      context.consumer()->Consume(error);
      return;
    }
    if (!(context.start_time() <= event.created_at && event.created_at <= context.end_time())) {
      auto error = ErrorEvent{"NotOpenYet", event.created_at};
      context.consumer()->Consume(error);
      return;
    }
    context.client_registry()->AddClient(client_name);
  }

  auto HandleClientTakeTableEvent(Context& context,
                                  const ClientTakeTableEvent& event)
      -> void {
    const auto& client_name = event.client_name;
    auto table_id = event.table_id;

    if (!context.table_registry()->IsTableFree(table_id)) {
      auto error = ErrorEvent{"PlaceIsBusy", event.created_at};
      context.consumer()->Consume(error);
      return;
    }
    if (!context.client_registry()->HasClient(client_name)) {
      auto error = ErrorEvent{"ClientUnknown", event.created_at};
      context.consumer()->Consume(error);
      return;
    }
    context.table_registry()->Pin(client_name, table_id);
    context.accountant()->AccountPinning(table_id, event.created_at);
  }

  auto HandleClientWaitingEvent(Context& context,
                                const ClientWaitingEvent& event)
      -> void {
    const auto& client_name = event.client_name;

    if (context.table_registry()->HasFreeTables()) {
      auto error = ErrorEvent{"ICanWaitNoLonger!", event.created_at};
      context.consumer()->Consume(error);
      return;
    }
    if (context.client_registry()->waiters_count() > context.tables_count()) {
      auto internal = ClientLeftInternalEvent{client_name, event.created_at};
      context.consumer()->Consume(internal);
    }
    context.client_registry()->AddWaiter(event.client_name);
  }

  auto HandleClientLeftEvent(Context& context,
                             const ClientLeftEvent& event)
      -> void {
    const auto& client_name = event.client_name;

    if (!context.client_registry()->HasClient(client_name)) {
      auto error = ErrorEvent{"ClientUnknown", event.created_at};
      context.consumer()->Consume(error);
    }

    context.client_registry()->RemoveClient(client_name);
    if (context.table_registry()->IsClientPinned(client_name)) {
      auto table_id = context.table_registry()->GetPinnedTable(client_name);
      context.table_registry()->Unpin(client_name);
      context.accountant()->AccountUnpinning(table_id, event.created_at);

      if (context.client_registry()->HasAnyWaiter()) {
        auto waiter = context.client_registry()->RemoveFirstWaiter();
        auto internal = ClientTakeTableInternalEvent{waiter, table_id, event.created_at};
        context.consumer()->Consume(internal);
      }
    }
  }

  auto HandleClientTakeTableInternalEvent(Context& context,
                                          const ClientTakeTableInternalEvent& event)
      -> void {
    context.table_registry()->Pin(event.client_name, event.table_id);
    context.accountant()->AccountPinning(event.table_id, event.created_at);
  }

  auto HandleClientLeftInternalEvent(Context& context,
                                     const ClientLeftInternalEvent& event)
      -> void {
    const auto& client_name = event.client_name;

    if (context.table_registry()->IsClientPinned(client_name)) {
      auto table_id = context.table_registry()->GetPinnedTable(client_name);
      context.table_registry()->Unpin(client_name);
      context.accountant()->AccountUnpinning(table_id, event.created_at);
    }

    if (context.client_registry()->HasClient(client_name)) {
      context.client_registry()->RemoveClient(client_name);
    }
  }

  auto HandleErrorEvent(Context& context, const ErrorEvent& event)
      -> void {}
}// namespace ComputerClub::Events