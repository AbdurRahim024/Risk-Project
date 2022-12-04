cmake_minimum_required(VERSION 3.23)
project(Risk_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(Cards)
include_directories(CommandProcessing)
include_directories(Driver)
include_directories(GameEngine)
include_directories(LoggingObserver)
include_directories(Map)
include_directories(Orders)
include_directories(Player)
include_directories(PlayerStrategies)

add_executable(Risk_Project
        Cards/Cards.cpp
        Cards/Cards.h
        Cards/CardsDriver.cpp
        Cards/CardsDriver.h
        CommandProcessing/CommandProcessing.cpp
        CommandProcessing/CommandProcessing.h
        CommandProcessing/CommandProcessingDriver.cpp
        Driver/MainDriver.cpp
        Driver/MainDriver.h
        GameEngine/GameEngine.cpp
        GameEngine/GameEngine.h
        GameEngine/GameEngineDriver.cpp
        GameEngine/GameEngineDriver.h
        LoggingObserver/LoggingObserver.cpp
        LoggingObserver/LoggingObserver.h
        LoggingObserver/LoggingObserverDriver.cpp
        Map/map.cpp
        Map/map.h
        Map/mapDriver.cpp
        Map/mapDriver.h
        Orders/Orders.cpp
        Orders/Orders.h
        Orders/OrdersDriver.cpp
        Orders/OrdersDriver.h
        Player/Player.cpp
        Player/Player.h
        Player/PlayerDriver.cpp
        Player/PlayerDriver.h
        PlayerStrategies/PlayerStrategies.cpp
        PlayerStrategies/PlayerStrategies.h
        PlayerStrategies/PlayerStrategiesDriver.cpp
        helloteam.cpp)
