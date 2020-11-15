# Build

FROM gcc:latest as build

RUN apt-get update
RUN apt-get install -y \
        python-pip \
        libsdl2-dev \
        libsdl2-image-dev \
        libsdl2-ttf-dev \
        libsdl2-mixer-dev \
        libglm-dev
        
RUN pip install cmake
RUN pip install golang

#RUN pip install vulcan-api

WORKDIR /vulkan-installation
RUN wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | apt-key add -
RUN wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.2.154-bionic.list https://packages.lunarg.com/vulkan/1.2.154/lunarg-vulkan-1.2.154-bionic.list
RUN apt-get update
RUN apt-get install -y vulkan-sdk

WORKDIR /app

ADD ./src ./src
ADD ./e172 ./e172
ADD ./sdl_implementation ./sdl_implementation
ADD ./vulkan_implementation ./vulkan_implementation
ADD ./tests ./tests
ADD ./CMakeLists.txt /app/CMakeLists.txt

WORKDIR /app/build
RUN cmake .. && make

# Run

FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y libx11-6
RUN apt-get install -y libsdl2-2.0-0
RUN apt-get install -y libsdl2-image-2.0-0
RUN apt-get install -y libsdl2-ttf-2.0-0
RUN apt-get install -y libsdl2-mixer-2.0-0
RUN apt-get install -y vulkan-utils
RUN apt-get install -y libgo16
RUN apt-get install -y gdb

WORKDIR /app

ADD ./assets ./assets
COPY --from=build /app/build/*.so ./bin/
COPY --from=build /app/build/project172 ./bin/
WORKDIR /app/bin

RUN groupadd -r user && useradd -r -g user user
USER user

#ENTRYPOINT ["/bin/gdb", "-ex", "run", "./project172"]
ENTRYPOINT ["./project172"]
