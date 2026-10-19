extern "C" {
    void __cxa_pure_virtual() {
        while (1);
    }
}
//I hate this. It reminds me of throat cancer.
void* operator new(unsigned int size) noexcept {
    return 0;
}

void* operator new[](unsigned int size) noexcept {
    return 0;
}

void operator delete(void* ptr) noexcept {
}

void operator delete[](void* ptr) noexcept {
}

void operator delete(void* ptr, unsigned int size) noexcept {
}

void operator delete[](void* ptr, unsigned int size) noexcept {
}