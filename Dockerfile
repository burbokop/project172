# Build

FROM gcc:13.1.0-bookworm as build

RUN apt-get update
RUN apt-get install -y \
        python3-pip \
        libsdl2-dev \
        libsdl2-image-dev \
        libsdl2-ttf-dev \
        libsdl2-mixer-dev \
        libglm-dev \
        libvulkan-dev

RUN pip install cmake --break-system-packages
RUN pip install golang --break-system-packages

WORKDIR /app

ADD ./src ./src
ADD ./e172 ./e172
ADD ./sdl_implementation ./sdl_implementation
ADD ./vulkan_implementation ./vulkan_implementation
ADD ./tests ./tests
ADD ./CMakeLists.txt ./CMakeLists.txt
ADD ./assets ./assets

WORKDIR /app/build/default
RUN cmake ../.. && make -j $(nproc)

# Run

FROM debian:bookworm

RUN apt-get update
RUN apt-get install -y libx11-6
RUN apt-get install -y libsdl2-2.0-0
RUN apt-get install -y libsdl2-image-2.0-0
RUN apt-get install -y libsdl2-ttf-2.0-0
RUN apt-get install -y libsdl2-mixer-2.0-0
RUN apt-get install -y vulkan-tools
RUN apt-get install -y libgo21
RUN apt-get install -y gdb

WORKDIR /app

COPY --from=build /app/build/*.so ./bin/
COPY --from=build /app/build/project172 ./bin/
WORKDIR /app/bin

RUN groupadd -r user && useradd -r -g user user
USER user

#ENTRYPOINT ["/bin/gdb", "-ex", "run", "./project172"]
ENTRYPOINT ["./project172"]
