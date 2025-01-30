//
// Created by Roman Maximov on 30.01.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef CONTEXT_H
#define CONTEXT_H

#include "collectiontypes.h"

typedef struct Context {
    void* collection;
    Type type;
} Context;

typedef Context* Ctx;

#endif
