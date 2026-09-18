#pragma once

#include <functional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "AuxTypes.hpp"
#include "Types.hpp"
#include "visualizer/VisualizationSession.hpp"

class AlgorithmRunner {
public:
    using SessionAlgorithm = std::function<void(std::vector<int>&, VisualizationSession&)>;
    using ClassicAlgorithm = std::function<void(std::vector<int>&, SortCallback)>;
    using DualCallbackAlgorithm = std::function<void(std::vector<int>&, SortCallback, AuxCallback)>;

    AlgorithmRunner() = default;

    static AlgorithmRunner fromSession(SessionAlgorithm algorithm) {
        return AlgorithmRunner(std::move(algorithm));
    }

    static AlgorithmRunner fromClassic(ClassicAlgorithm algorithm) {
        return AlgorithmRunner(
            [algorithm = std::move(algorithm)](
                std::vector<int>& arr,
                VisualizationSession& session)
            {
                algorithm(arr, makeSortCallback(arr, session));
            });
    }

    // Useful for transitional algorithms that emit both event streams directly.
    // Algorithms that need begin/end auxiliary phase boundaries should prefer
    // fromSession so they can call VisualizationSession explicitly.
    static AlgorithmRunner fromCallbacks(DualCallbackAlgorithm algorithm) {
        return AlgorithmRunner(
            [algorithm = std::move(algorithm)](
                std::vector<int>& arr,
                VisualizationSession& session)
            {
                algorithm(
                    arr,
                    makeSortCallback(arr, session),
                    makeAuxCallback(arr, session));
            });
    }

    void operator()(std::vector<int>& arr, VisualizationSession& session) const {
        if (!algorithm) {
            throw std::logic_error("Cannot run an empty AlgorithmRunner.");
        }

        algorithm(arr, session);
    }

    explicit operator bool() const noexcept {
        return static_cast<bool>(algorithm);
    }

private:
    SessionAlgorithm algorithm;

    explicit AlgorithmRunner(SessionAlgorithm algorithm)
        : algorithm(std::move(algorithm))
    {
    }

    static SortCallback makeSortCallback(
        std::vector<int>& arr,
        VisualizationSession& session)
    {
        return [&arr, &session](
            SortEvent event,
            int idx1,
            int idx2,
            const std::string& stepName)
        {
            session.onArrayEvent(arr, event, idx1, idx2, stepName);
        };
    }

    static AuxCallback makeAuxCallback(
        std::vector<int>& arr,
        VisualizationSession& session)
    {
        return [&arr, &session](
            AuxEvent event,
            int srcIdx,
            int row,
            int pos,
            const std::string& stepName)
        {
            session.onAuxEvent(arr, event, srcIdx, row, pos, stepName);
        };
    }
};

using CallbackAlgorithm = AlgorithmRunner::ClassicAlgorithm;

inline AlgorithmRunner makeArrayRunner(CallbackAlgorithm algorithm) {
    return AlgorithmRunner::fromClassic(std::move(algorithm));
}

inline AlgorithmRunner makeSessionRunner(AlgorithmRunner::SessionAlgorithm algorithm) {
    return AlgorithmRunner::fromSession(std::move(algorithm));
}

inline AlgorithmRunner makeDualCallbackRunner(AlgorithmRunner::DualCallbackAlgorithm algorithm) {
    return AlgorithmRunner::fromCallbacks(std::move(algorithm));
}
