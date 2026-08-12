cmake_minimum_required(VERSION 3.10)
project(RARE_Tokenizer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(rare_tokenizer
    BPE.cpp
    Trainer.cpp
    Vocabulary.cpp
    Encoder.cpp
    Decoder.cpp
)

add_executable(train_cartridge train_cartridge.cpp)
target_link_libraries(train_cartridge PRIVATE rare_tokenizer)
