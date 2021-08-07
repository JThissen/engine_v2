#ifndef MAIN_H
#define MAIN_H

#include "headers.hpp"
#include "sandbox/sandbox.hpp"

int main(int argc, char* argv[]) {
    std::unique_ptr<engine::App> sandbox = std::make_unique<Sandbox>(true);
    return EXIT_SUCCESS;
}

#endif
