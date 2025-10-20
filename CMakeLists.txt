cmake_minimum_required(VERSION 3.25)
project(replace_cli C)

# C-Standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Dein Programm: Quelle(n) hier eintragen
add_executable(replace
        replace.c
)

# (optional, aber sehr hilfreich) Warnungen
target_compile_options(replace PRIVATE -Wall -Wextra -Wpedantic -Wconversion)