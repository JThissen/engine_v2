#ifndef MAIN_H
#define MAIN_H

#include "headers.hpp"
#include "sandbox.hpp"

int main(int argc, char* argv[]) {
    std::unique_ptr<Sandbox> sandbox = std::make_unique<Sandbox>();
    sandbox->run();
    return EXIT_SUCCESS;
}

#endif
