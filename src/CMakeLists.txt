add_library(yadro_computer_club_lib
        events/events.def
        events/handle_events.cpp
        events/handle_events.hpp
        events/events.hpp
        events/event_consumer.hpp
        events/context.hpp

        io/utils/time_converts.hpp
        io/utils/time_converts.cpp
        io/parsing.cpp
        io/parsing.hpp
        io/serializing.hpp

        registries/client_registry.cpp
        registries/client_registry.hpp
        registries/table_registry.cpp
        registries/table_registry.hpp
        registries/accountant.cpp
        registries/accountant.hpp

        root.cpp
        root.hpp

        validations/validation_pipeline.cpp
        validations/validation_pipeline.hpp

        validations/steps/context_validation.cpp
        validations/steps/context_validation.hpp
        validations/steps/events_validation.cpp
        validations/steps/events_validation.hpp
)
target_include_directories(yadro_computer_club_lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)