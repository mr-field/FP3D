# This Dockerfile builds the app but does not run it.
# Its purpose is to provide a fixed, reproducible build environment
# rather than a runtime environment for the app

FROM ubuntu:18.04

RUN apt-get update; \
    apt-get install -y build-essential cmake libglfw3-dev libwxgtk3.0-gtk3-dev; \
    groupadd -r fp3d && useradd --no-log-init -r -g fp3d fp3d

COPY --chown=fp3d . /app

USER fp3d

WORKDIR /app

RUN mkdir build; \
    cd build; \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=dist ..; \
    cmake --build . --config Release --target install

# The built artifacts will now be in /app/build/dist
