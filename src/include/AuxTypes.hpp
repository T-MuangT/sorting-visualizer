#pragma once
#include <string>
#include <functional>

enum class AuxEvent {
    PlaceInBucket,
    FlushBucket,
    CompareInAux,
    // extend as new algorithms need new verbs
};

using AuxCallback = std::function<void(
    AuxEvent event,
    int srcIdx,
    int row,
    int pos,
    const std::string& stepName)>;