FROM gcc:13 as base

# Restate the variant to use it later on in the llvm and cmake installations
ARG VARIANT

# Install necessary packages available from standard repos
RUN apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
        software-properties-common wget apt-utils file zip \
        openssh-client gpg-agent socat rsync \
        make ninja-build cmake git \
        python3 python3-pip clang 

# Install editors
RUN apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
        vim

# Install optional dependecies
RUN apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
        doxygen graphviz ccache cppcheck

## Cleanup cached apt data we don't need anymore
RUN apt-get autoremove -y && apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Allow the user to set compiler defaults
#ARG USE_CLANG
# if --build-arg USE_CLANG=1, set CC to 'clang' or set to null otherwise.
#ENV CC=${USE_CLANG:+"clang"}
#ENV CXX=${USE_CLANG:+"clang++"}
# if CC is null, set it to 'gcc' (or leave as is otherwise).
#ENV CC=${CC:-"gcc"}
#ENV CXX=${CXX:-"g++"}

# Include project
ADD . /workspaces/cpp_starter_project
WORKDIR /workspaces/cpp_starter_project

RUN mkdir ./dockerBuild
RUN cmake -S . -B ./dockerBuild 
RUN cmake --build ./dockerBuild --target install

CMD ["invoice"]
