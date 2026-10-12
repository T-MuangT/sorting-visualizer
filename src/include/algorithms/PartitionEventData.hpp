#pragma once

struct PartitionEventData {
    int srcIdx = -1;
    int startIdx = -1;
    int endIdx = -1;

    int pivotValue = 0;

    int leftRow = -1;
    int middleRow = -1;
    int rightRow = -1;

    int leftPos = -1;
    int middlePos = -1;
    int rightPos = -1;

    int value = 0;
};