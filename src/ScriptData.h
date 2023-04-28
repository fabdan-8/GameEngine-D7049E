#pragma once

struct ScriptData {
    const int entityId;
    const int scriptId;
    void *data; // All data associated with a script
    // bound to a single object

    void Update(); // Run script

    ScriptData(int entityId, int scriptId);
};
