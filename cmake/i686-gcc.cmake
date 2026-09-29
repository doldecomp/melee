# Build the native smoke test as 32-bit x86, which the game's pointer-size
# assumptions require. Needs a multilib gcc (e.g. nixpkgs' gcc_multi).
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR i686)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS_INIT -m32)
