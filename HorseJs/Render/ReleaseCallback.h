#pragma once
#include "V8Handler.h"
class ReleaseCallback : public CefV8ArrayBufferReleaseCallback {
public:
    void ReleaseBuffer(void* buffer) override {
        std::free(buffer);
    }
    IMPLEMENT_REFCOUNTING(ReleaseCallback);
};
